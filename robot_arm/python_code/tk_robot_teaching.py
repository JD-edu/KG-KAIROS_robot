#!/usr/bin/env python
#-*- coding:utf-8 -*-
import os
#import socket
from threading import Thread, Event
import serial
import glob
import time
import sys 
import threading
import tempfile
import subprocess

#Python 2.7 imports
try:
    import Tkinter as tk
    from Tkinter import StringVar
    import ttk
    import tkMessageBox as messagebox
    import tkFileDialog as filedialog
    import SimpleHTTPServer
    from BaseHTTPServer import HTTPServer
    import Queue
    import commands
#Python 3.x imports
except ImportError:
    import tkinter as tk
    from tkinter import ttk
    from tkinter import messagebox
    from tkinter import filedialog
    from http.server import SimpleHTTPRequestHandler
    from http.server import HTTPServer
    import queue as Queue
    import subprocess as commands

angle_0 = 0
angle_1 = 0
angle_2 = -90
angle_3 = -60
angle_4 = 0
angle_5 = 90

# Command code for Arduino
CMD_RUN_ROBOT = '1'
CMD_SAVE_POS = '2'
CMD_RESET_ROBOT = '3'
CMD_MOVE_ROBOT_JOY = '4'
CMD_CLEAR_POS = '5'
CMD_MOVE_ROBOT_SERIAL = '6'
CMD_MOVE_ROBOT_6LINK = '7'
CMD_STOP_ROBOT = '8'

SERVO_IDX = 'z'
SERVO_0 = 'a'
SERVO_1 = 'b'
SERVO_2 = 'c'
SERVO_3 = 'd'
SERVO_4 = 'e'
SERVO_5 = 'f'
SERVO_END = 'g'

UP = 'u'
DOWN = 'd'

LINK_SAVE_LIMIT = 20
link_save_count = 0

m_slide_0_track = None
m_slide_1_track = None
m_slide_2_track = None
m_slide_3_track = None
m_slide_4_track = None
m_slide_5_track = None

save_position = [[0]*6 for i in range(20)]

SAVE_LIMIT = 20
save_index = 0

class ServerThread(Thread):

    def __init__(self):
        Thread.__init__(self)
        self.queue = server_queue
        self.is_server_running = False 
        self.daemon = True
        self.server = HTTPServer(("127.0.0.1", 8081), Handler)
        self.serv_info = self.server.socket.getsockname()
        print(self.serv_info)

    def run(self):
        self.server.serve_forever()

class Handler(SimpleHTTPServer.SimpleHTTPRequestHandler):
    def do_HEAD(self):
        """Send response headers"""
        if self.path != "/":
            return SimpleHTTPServer.SimpleHTTPRequestHandler.do_HEAD(self)
        self.send_response(200)
        self.send_header("content-type", "text/html;charset=utf-8")
        self.send_header('Access-Control-Allow-Origin', '*')
        self.end_headers()

    def do_GET(self):
        """Send page text"""
        if self.path != "/":
            return SimpleHTTPServer.SimpleHTTPRequestHandler.do_GET(self)
        else:
            self.send_response(302)
            #self.send_header("Location", "/blockly/demos/code/index.html")
            self.send_header("Location", "/blockly/apps/cobit_blockly/index.html")
            self.end_headers()

    def do_POST(self):
        """Save new page text and display it"""
        if self.path != "/":
            return SimpleHTTPServer.SimpleHTTPRequestHandler.do_POST(self)

        #options, args = parser.parse_args()

        length = int(self.headers.getheader('content-length'))
        if length:
            text = self.rfile.read(length)
                        
            print "sketch to upload: " + text

            dirname = tempfile.mkdtemp()
            sketchname = os.path.join(dirname, os.path.basename(dirname)) + ".py"
            f = open(sketchname, "wb")
            f.write(text + "\n")
            f.close()
            # get serial port name for subprocess 
            serial_port_args = "--serial="+serial_thread.set_serial_port()

            print "created sketch at %s" % (sketchname,)
            # invoke arduino to build/upload
            compile_args = [
                'python',
                sketchname,
                serial_port_args
            ]

            #compile_args.append(sketchname)

            print "Uploading with %s" % (" ".join(compile_args))
            rc = subprocess.call(compile_args)
           
            if not rc == 0:
                print "python returned " + `rc`                            
                self.send_response(400)
            else:
                self.send_response(200)
                self.send_header('Access-Control-Allow-Origin', '*')
                self.end_headers()
        else:
            self.send_response(400)


class SerialThread(Thread):

    def __init__(self):
        Thread.__init__(self)

        self.seq = serial.Serial(
            baudrate=9600,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            timeout=1
        )
        
        self.seq.port = "None"
       
        self.queue = serial_queue
        self.is_serial_running = False
        self.daemon = True

    def run(self):

        global angle_0
        global angle_1
        global angle_2
        global angle_3
        global angle_4
        global angle_5

        while True:
            time.sleep(0.05)
            if self.seq.isOpen() == True:  
                try:
                    if self.seq.inWaiting():
                        # If using readline(), print speed is very low. 
                        #cmd = self.seq.readline(self.seq.inWaiting())
                        #cmd = self.seq.read(self.seq.inWaiting())
                        try:
                            cmd = self.seq.readline()
                            print(cmd)
                            # cmd is incoming command from arduino robor controller
                            # cmd[0] == 'a' -> robot servo angle report 
                            if cmd[0] == 'a':
                                a = cmd.index('a')
                                b = cmd.index('b')
                                c = cmd.index('c')
                                d = cmd.index('d')
                                e = cmd.index('e')
                                f = cmd.index('f')
                                g = cmd.index('g')
                                angle_0 = int(cmd[a+1:b])
                                angle_1 = int(cmd[b+1:c])
                                angle_2 = int(cmd[c+1:d])
                                angle_3 = int(cmd[d+1:e])
                                angle_4 = int(cmd[e+1:f])
                                angle_5 = int(cmd[f+1:g])
                                root.set_slider_value()
                            # cmd[0] == '8' --> stop robot 
                            elif cmd[0] == '8':
                                print("Stop robot")
                                
                            elif cmd[0] == '2':
                                print("save pos")
                                root.save_link()
                        except AttributeError:
                            print("attr error")
                except IOError:
                    print("IO error")
                    
                    
    def open_port(self):
        if self.seq.isOpen() == False:
            self.seq.open()

    def close_port(self):
        if self.seq.isOpen() == True:
            self.seq.close()

    def is_seq_open(self):
        if self.seq.isOpen() == True:
            return True
        else:
            return False

    def get_serial_port(self, port_name):
        self.seq.port = port_name

    def set_serial_port(self):
        return self.seq.port

    def send_robot_cmd(self, msg):
        try:   
            self.seq.write(msg)
        except (OSError, serial.SerialException):   
            pass   

    
        

    def serial_ports(self):   
        if sys.platform.startswith('win'):   
            self.ports = ['COM%s' % (i + 1) for i in range(256)]   
        elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):   
            # this excludes your current terminal "/dev/tty"   
            self.ports = glob.glob('/dev/tty[A-Za-z]*')   
        elif sys.platform.startswith('darwin'):   
            self.ports = glob.glob('/dev/tty.*')   
        else:   
            raise EnvironmentError('Unsupported platform')   
        
        self.result = []   
        for self.port in self.ports:   
            try:   
                self.s = serial.Serial(self.port)   
                self.s.close()   
                self.result.append(self.port)   
            except (OSError, serial.SerialException):   
                pass   
        return self.result   
            
        
class Gui(tk.Tk):

    def __init__(self):

        global m_slide_0_track
        global m_slide_1_track
        global m_slide_2_track
        global m_slide_3_track
        global m_slide_4_track
        global m_slide_5_track


        serial_list = ['시리얼 포트를 선택하세요.']

        self.startTimer(1,False)
        self.startAngleUpTimer(3,True)

        tk.Tk.__init__(self)
        self.serial_running = False

        m_serial_select = ttk.Frame(self)
        self.var = StringVar()
        m_serial_select.pack()
        self.dropdown = ttk.OptionMenu(m_serial_select, self.var, serial_list[0], *serial_list, command = self.OptionMenu_Selected(self.var))
        self.dropdown.pack()
        self.dropdown.configure(state='normal')

        self.var.trace('w', self.OptionMenu_Changed)
        
        m_serial_start_btn = ttk.Frame(self)
        m_serial_stop_btn = ttk.Frame(self)
        m_home_btn = ttk.Frame(self)
        m_link0 = ttk.Frame(self)       # link 0  
        m_link1 = ttk.Frame(self)       # link 1
        m_link2 = ttk.Frame(self)       # link 2
        m_link3 = ttk.Frame(self)       # link 3
        m_link4 = ttk.Frame(self)       # link 4
        m_link5 = ttk.Frame(self)       # link 5
        m_save_btn = ttk.Frame(self)    # button: save
        m_clear_btn = ttk.Frame(self)   # button: clear
        m_logout_text = tk.Frame(self)  # text widget
        m_slide_0 = ttk.Frame(self)     # slider 0
        m_slide_1 = ttk.Frame(self)     # slider 0
        m_slide_2 = ttk.Frame(self)     # slider 0
        m_slide_3 = ttk.Frame(self)     # slider 0
        m_slide_4 = ttk.Frame(self)     # slider 0
        m_slide_5 = ttk.Frame(self)     # slider 0
        m_robot_run_btn = ttk.Frame(self)
        m_robot_stop_btn = ttk.Frame(self)

        # serial start button
        self.start_serial_btn = ttk.Button(m_serial_start_btn, text="Start serial", command=self.start_serial)
        self.start_serial_btn.pack(side='left',padx=10) 
        # serial stop button
        self.stop_serial_btn = ttk.Button(m_serial_stop_btn, text="Stop serial", command=self.stop_serial)
        self.stop_serial_btn.pack(side='left',padx=10) 
        # robot retrun to home button 
        self.robot_home_btn = ttk.Button(m_home_btn, text="Robot Home", command=self.robot_home)
        self.robot_home_btn.pack(side='left',padx=10) 

        self.start_serial_btn.configure(state='disable')
        self.stop_serial_btn.configure(state='disable')
        self.robot_home_btn.configure(state='disable')
        #Link 0 
        self.link0 = StringVar()
        ttk.Label(m_link0,text='Link 0: ',font='Helvetica 10 bold').pack(side='left')
        self.port1 = ttk.Entry(m_link0,width=6, textvariable = self.link0)
        self.port1.insert('end','80')
        self.port1.pack(side='left',padx=0,pady=5)
        #Link 1 
        ttk.Label(m_link1,text='Link 1: ',font='Helvetica 10 bold').pack(side='left')
        self.port2 = ttk.Entry(m_link1,width=6)
        self.port2.insert('end','80')
        self.port2.pack(side='left',padx=0,pady=5)
        #link 2
        ttk.Label(m_link2,text='Link 2: ',font='Helvetica 10 bold').pack(side='left')
        self.port3 = ttk.Entry(m_link2,width=6)
        self.port3.insert('end','140')
        self.port3.pack(side='left',padx=0,pady=5)
        #Link 3 
        ttk.Label(m_link3,text='Link 3: ',font='Helvetica 10 bold').pack(side='left')
        self.port4 = ttk.Entry(m_link3,width=6)
        self.port4.insert('end','80')
        self.port4.pack(side='left',padx=0,pady=5)
        #Link 4 
        ttk.Label(m_link4,text='Link 4: ',font='Helvetica 10 bold').pack(side='left')
        self.port5 = ttk.Entry(m_link4,width=6)
        self.port5.insert('end','30')
        self.port5.pack(side='left',padx=0,pady=5)
        #link 5
        ttk.Label(m_link5,text='Link 5: ',font='Helvetica 10 bold').pack(side='left')
        self.port6 = ttk.Entry(m_link5,width=6)
        self.port6.insert('end','160')
        self.port6.pack(side='left',padx=0,pady=5)
        # save btn
        self.save_link_btn = ttk.Button(m_save_btn, text="save link", command=self.save_link)
        self.save_link_btn.pack(side='left',padx=10) 
         # clear btn
        self.clear_link_btn = ttk.Button(m_clear_btn, text="clear link", command=self.clear_link)
        self.clear_link_btn.pack(side='left',padx=10) 
        # text widget 
        self.text_widget = tk.Text(m_logout_text, width=60, height=10)
        self.text_widget.pack(side = "top", fill="both", expand = "true")
        # slide 0
        m_slide_0_track = ttk.Scale(m_slide_0, length = 200,  from_= -90, to = 90, orient ="vertical")
        m_slide_0_track.bind("<ButtonRelease-1>", self.slide_handler_0)
        m_slide_0_track.set(angle_0)
        m_slide_0_track.pack(side='left',padx=0,pady=5)
        # slide 1
        m_slide_1_track = ttk.Scale(m_slide_1, length = 200, from_= -90, to = 90, orient ="vertical")
        m_slide_1_track.bind("<ButtonRelease-1>", self.slide_handler_1)
        m_slide_1_track.set(angle_1)
        m_slide_1_track.pack(side='left',padx=0,pady=5)
        # slide 2
        m_slide_2_track = ttk.Scale(m_slide_2, length = 200, from_= -90, to = 90, orient ="vertical")
        m_slide_2_track.bind("<ButtonRelease-1>", self.slide_handler_2)
        m_slide_2_track.set(angle_2)
        m_slide_2_track.pack(side='left',padx=0,pady=5)
        # slide 3
        m_slide_3_track = ttk.Scale(m_slide_3, length = 200, from_= -90, to = 90, orient ="vertical")
        m_slide_3_track.bind("<ButtonRelease-1>", self.slide_handler_3)
        m_slide_3_track.set(angle_3)
        m_slide_3_track.pack(side='left',padx=0,pady=5)
        # slide 4
        m_slide_4_track = ttk.Scale(m_slide_4, length = 200, from_= -90, to = 90, orient ="vertical")
        m_slide_4_track.bind("<ButtonRelease-1>", self.slide_handler_4)
        m_slide_4_track.set(angle_4)
        m_slide_4_track.pack(side='left',padx=0,pady=5)
        # slide 5
        m_slide_5_track = ttk.Scale(m_slide_5, length = 200, from_= -90, to = 90, orient ="vertical")
        m_slide_5_track.bind("<ButtonRelease-1>", self.slide_handler_5)
        m_slide_5_track.set(angle_5)
        m_slide_5_track.pack(side='left',padx=0,pady=5)
        # robot run button 
        self.robot_run_btn = ttk.Button(m_robot_run_btn, text="run robot", command=self.run_robot)
        self.robot_run_btn.pack(side='left', padx=10)
        # robot stop button 
        self.robot_stop_btn = ttk.Button(m_robot_stop_btn, text="stop robot", command=self.stop_robot)
        self.robot_stop_btn.pack(side='left', padx=10)


        m_serial_select.grid(column=1,row=0,columnspan=3,padx=10,pady=10,sticky='w')
        m_serial_start_btn.grid(column=1,row=1,padx=10,pady=5,sticky='w')
        m_serial_stop_btn.grid(column=2,row=1,padx=10,pady=5,sticky='w')
        m_home_btn.grid(column=3,row=1,padx=10,pady=5,sticky='w')
        m_link0.grid(column=1,row=2,padx=10,pady=5,sticky='w')
        m_link1.grid(column=2,row=2,padx=10,pady=5,sticky='w')
        m_link2.grid(column=3,row=2,padx=10,pady=5,sticky='w')
        m_link3.grid(column=4,row=2,padx=10,pady=5,sticky='w')
        m_link4.grid(column=5,row=2,padx=10,pady=5,sticky='w')
        m_link5.grid(column=6,row=2,padx=10,pady=5,sticky='w')
        
        m_slide_0.grid(column=1,row=6,padx=15,pady=5,sticky='w')
        m_slide_1.grid(column=2,row=6,padx=15,pady=5,sticky='w')
        m_slide_2.grid(column=3,row=6,padx=15,pady=5,sticky='w')
        m_slide_3.grid(column=4,row=6,padx=15,pady=5,sticky='w')
        m_slide_4.grid(column=5,row=6,padx=15,pady=5,sticky='w')
        m_slide_5.grid(column=6,row=6,padx=15,pady=5,sticky='w')
        m_save_btn.grid(column=5,row=7,padx=10,pady=5,sticky='w')
        m_clear_btn.grid(column=6,row=7,padx=10,pady=5,sticky='w')
        m_logout_text.grid(column=1, columnspan = 4,row=7,padx=10,pady=5,sticky= 'w')
        m_robot_run_btn.grid(column=1, row=8,padx=10,pady=5,sticky='w')
        m_robot_stop_btn.grid(column=2, row=8,padx=10,pady=5,sticky='w')
       
    def OptionMenu_Selected(self, value): 
        print(value)

    def OptionMenu_Changed(self, *args): 
        print(self.var.get())
        serial_thread.get_serial_port(self.var.get())
        self.start_serial_btn.configure(state='enable')
        
    def save_link(self):
        global angle_0
        global angle_1
        global angle_2
        global angle_3
        global angle_4
        global angle_5

        global save_position
        global save_index

        if save_index < 20:
            # Save position on PC and display it on UI.
            save_position[save_index][0] = angle_0
            save_position[save_index][1] = angle_1
            save_position[save_index][2] = angle_2
            save_position[save_index][3] = angle_3
            save_position[save_index][4] = angle_4
            save_position[save_index][5] = angle_5
            # Send save postion data to arduino 
            self.msg = CMD_SAVE_POS+SERVO_IDX+str(save_index)+SERVO_0+str(angle_0)+SERVO_1+str(angle_1)+SERVO_2+str(angle_2)+SERVO_3+str(angle_3)+SERVO_4+str(angle_4)+SERVO_5+str(angle_5)+SERVO_END+'\n'
            serial_thread.send_robot_cmd(self.msg)
            # Increase save position index
            save_index += 1
            # Update UI
            self.text_widget.insert('end', str(angle_0)+" "+str(angle_1)+" "+str(angle_2)+" "+str(angle_3)+" "+str(angle_4)+" "+str(angle_5)+"\n")                                 
        
        else:
            print("Max position saving number is 20.")

          
    # Delete all saved position and erase UI  
    def clear_link(self):
        global save_index 
        global save_position

        save_position = [[0]*6 for i in range(20)]
        save_index = 0
        print(save_position)  
        self.text_widget.delete('1.0', tk.END)
        self.msg = CMD_CLEAR_POS
        serial_thread.send_robot_cmd(self.msg)
   
    def start_serial(self):
        print("start serial")
        self.start_serial_btn.configure(state='disable')
        self.stop_serial_btn.configure(state='normal')
        self.robot_home_btn.configure(state='normal')

        if self.serial_running == False:
            self.serial_running = True
            serial_thread.start()   
        serial_thread.open_port()

    def setAngle(self):
        
        global angle_0
        global angle_1
        global angle_2
        global angle_3
        global angle_4
        global angle_5
        global angle_6

        self.port1.delete(0, 'end')
        self.port1.insert(0, str(angle_0))
        self.port2.delete(0, 'end')
        self.port2.insert(0, str(angle_1))
        self.port3.delete(0, 'end')
        self.port3.insert(0, str(angle_2))
        self.port4.delete(0, 'end')
        self.port4.insert(0, str(angle_3))
        self.port5.delete(0, 'end')
        self.port5.insert(0, str(angle_4))
        self.port6.delete(0, 'end')
        self.port6.insert(0, str(angle_5))

        
    def stop_serial(self):
        print("stop serial")
        self.start_serial_btn.configure(state='normal')
        self.stop_serial_btn.configure(state='disable')
        self.robot_home_btn.configure(state='disable')
        serial_thread.close_port()

    def timerCallBack(self, iTimeSec,isRepeated):
        self.result = serial_thread.serial_ports()
        self.serial_list = self.result
        print(self.serial_list)
        self.update_option_menu()
        self.dropdown.configure(state='enable')
        if isRepeated == True :
            self.timer_thread1 = threading.Timer(iTimeSec,self.timerCallBack,[iTimeSec,isRepeated])
            self.timer_thread1.daemon = True
            self.timer_thread1.start()

    def timerAngleUpCallBack(self, iTimeSec,isRepeated):
        self.setAngle()
        if isRepeated == True :
            self.timer_thread2 = threading.Timer(0.1,self.timerAngleUpCallBack,[iTimeSec,isRepeated])
            self.timer_thread2.daemon = True
            self.timer_thread2.start()

    def startTimer(self, iTimeSec,isRepeated):
        self.timer_thread1 = threading.Timer(iTimeSec,self.timerCallBack,[iTimeSec,isRepeated])
        self.timer_thread1.daemon = True
        self.timer_thread1.start()

    def startAngleUpTimer(self, iTimeSec, isRepeated):
        self.timer_thread2 = threading.Timer(iTimeSec,self.timerAngleUpCallBack,[iTimeSec,isRepeated])
        self.timer_thread2.daemon = True
        self.timer_thread2.start()

    def update_option_menu(self):
        self.menu = self.dropdown["menu"]
        self.menu.delete(0, "end")
        for string in self.serial_list:
            self.menu.add_command(label=string, command=lambda value=string: self.var.set(value))

    # Run robot through saved postions
    def run_robot(self):
        self.msg = CMD_RUN_ROBOT
        serial_thread.send_robot_cmd(self.msg)

    # Stop robot move
    def stop_robot(self):
        self.msg = CMD_STOP_ROBOT
        serial_thread.send_robot_cmd(self.msg)

    def set_slider_value(self):
        m_slide_0_track.set(angle_0)
        m_slide_1_track.set(angle_1)
        m_slide_2_track.set(angle_2)
        m_slide_3_track.set(angle_3)
        m_slide_4_track.set(angle_4)
        m_slide_5_track.set(angle_5)


    # Robot reset - go to home position        
    def robot_home(self):
        global angle_0
        global angle_1
        global angle_2
        global angle_3
        global angle_4
        global angle_5
        global angle_6
        print("robot home")
        angle_0 = 0
        angle_1 = 0
        angle_2 = -90
        angle_3 = -60
        angle_4 = 0
        angle_5 = 90
        self.setAngle()

        self.set_slider_value()

        #m_slide_0_track.set(angle_0)
        #m_slide_1_track.set(angle_1)
        #m_slide_2_track.set(angle_2)
        #m_slide_3_track.set(angle_3)
        #m_slide_4_track.set(angle_4)
        #m_slide_5_track.set(angle_5)

        self.msg = CMD_RESET_ROBOT
        serial_thread.send_robot_cmd(self.msg)

    def slide_handler_0(self, event):
        self.msg = CMD_MOVE_ROBOT_SERIAL+SERVO_0+str(int(m_slide_0_track.get()))+'\n'
        serial_thread.send_robot_cmd(self.msg)

    def slide_handler_1(self, event):
        self.msg = CMD_MOVE_ROBOT_SERIAL+SERVO_1+str(int(m_slide_1_track.get()))+'\n'
        serial_thread.send_robot_cmd(self.msg)
    
    def slide_handler_2(self, event):
        self.msg = CMD_MOVE_ROBOT_SERIAL+SERVO_2+str(int(m_slide_2_track.get()))+'\n'
        serial_thread.send_robot_cmd(self.msg)

    def slide_handler_3(self, event):
        self.msg = CMD_MOVE_ROBOT_SERIAL+SERVO_3+str(int(m_slide_3_track.get()))+'\n'
        serial_thread.send_robot_cmd(self.msg)

    def slide_handler_4(self, event):
        self.msg = CMD_MOVE_ROBOT_SERIAL+SERVO_4+str(int(m_slide_4_track.get()))+'\n'
        serial_thread.send_robot_cmd(self.msg)

    def slide_handler_5(self, event):
        self.msg = CMD_MOVE_ROBOT_SERIAL+SERVO_5+str(int(m_slide_5_track.get()))+'\n'
        serial_thread.send_robot_cmd(self.msg)
      
if __name__ == '__main__':
    root = Gui()
    serial_queue = Queue.Queue()
    server_queue = Queue.Queue()
    serial_thread = SerialThread()
    server_thread = ServerThread()
    server_thread.start()
    root.mainloop()