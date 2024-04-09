
'''
MIT License

Copyright (c) 2024 JD edu. http://jdedu.kr author: conner.jeong@gmail.com
     
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
     
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
     
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN TH
SOFTWARE.
'''
import tkinter as tk
from tkinter import ttk
import serial
import threading 
import glob
import sys 

def select_serial(event):
    print("serial drop down")
    
def serial_changed(varname, index, mode):
    global var, seq
    print(var.get())
    seq.port = var.get()

def move_robot():
    print("robot test")
    seq.write("2a120b120c120d120e120\n".encode())
   
def reset_robot():
    global angle_0, angle_1, angle_2, angle_3
    angle_0, angle_1, angle_2, angle_3 = 90,90,90,90
    print("reset robot")
    seq.write("3\n".encode())
    port0.delete(0, 'end')
    port0.insert(0, str(int(angle_0)))
    port1.delete(0, 'end')
    port1.insert(0, str(int(angle_1)))
    port2.delete(0, 'end')
    port2.insert(0, str(int(angle_2)))
    port3.delete(0, 'end')
    port3.insert(0, str(int(angle_3)))
    m_slide_0_track.set(90)
    m_slide_1_track.set(90)
    m_slide_2_track.set(90)
    m_slide_3_track.set(90)

def slide_handler_base(event):
    global angle_0
    angle_0 = m_slide_0_track.get()
    print(angle_0)
    port0.delete(0, 'end')
    port0.insert(0, str(int(angle_0)))

def slide_handler_shoulder(event):
    global angle_1
    angle_1 = m_slide_1_track.get()
    print(angle_1)
    port1.delete(0, 'end')
    port1.insert(0, str(int(angle_1)))

def slide_handler_forearm(event):
    global angle_2
    angle_2 = m_slide_2_track.get()
    print(angle_2)
    port2.delete(0, 'end')
    port2.insert(0, str(int(angle_2)))

def slide_handler_upperarm(event):
    global angle_3
    angle_3 = m_slide_3_track.get()
    print(angle_3)
    port3.delete(0, 'end')
    port3.insert(0, str(int(angle_3)))

def run_robot():
    global angle_0
    global angle_1
    global angle_2
    global angle_3
    cmd = '2a'+str(int(angle_0))+'b'+str(int(angle_1))+'c'+str(int(angle_2))+'d'+str(int(angle_3))+'e\n'
    print(cmd)
    seq.write(cmd.encode())
    print(cmd.encode())

def stop_robot():
    pass

def enable_serial():
    seq.open()
    
def disable_serial():
    seq.close()

def record_sequence():
    pass
    
def sequence_run():
    pass



# serial finder function 
def startTimer(iTimeSec,isRepeated):
    timer_thread1 = threading.Timer(iTimeSec, timerCallBack,[iTimeSec,isRepeated])
    timer_thread1.daemon = True
    timer_thread1.start()
# serial finder function 
def timerCallBack(iTimeSec,isRepeated):
    global serial_list
    print("start timer")
    result = serial_ports()
    serial_list = result
    print(serial_list)
    update_option_menu()
    dropdown.configure(state='enable')
    if isRepeated == True :
        timer_thread1 = threading.Timer(iTimeSec,timerCallBack,[iTimeSec,isRepeated])
        timer_thread1.daemon = True
        timer_thread1.start()
def update_option_menu():
    global dropdown
    global serial_list
    menu = dropdown["menu"]
    print(menu)
    menu.delete(0, "end")
    for string in serial_list:
        menu.add_command(label=string, command=lambda value=string: var.set(value))


def serial_ports():   
    if sys.platform.startswith('win'):   
        ports = ['COM%s' % (i + 1) for i in range(256)]   
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):   
        # this excludes your current terminal "/dev/tty"   
        ports = glob.glob('/dev/tty[A-Za-z]*')   
    elif sys.platform.startswith('darwin'):   
        ports = glob.glob('/dev/tty.*')   
    else:   
        raise EnvironmentError('Unsupported platform')   
    
    result = []   
    for port in ports:   
        try:   
            s = serial.Serial(port)   
            s.close()   
            result.append(port)
        except (OSError, serial.SerialException):   
            pass   
    return result  

seq = serial.Serial(
        baudrate=115200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
    )

angle_0 = 90
angle_1 = 90
angle_2 = 90
angle_3 = 90

# serial finder code 
startTimer(1, False)

root = tk.Tk()
root.title('KG-KAIROS Robot Control')
root.geometry('600x480')

# dropdown menu code 1 
serial_list = ['시리얼 포트를 선택하세요']
m_serial_select = ttk.Frame(root)
var = tk.StringVar()
'''
list1 = [1, 2, 3]
이 리스트를 '*'를 사용하여 펼치면 다음과 같은 튜플이 반환됩니다.
print(*list1)
(1, 2, 3)
'''
# add option menu
dropdown = ttk.OptionMenu(m_serial_select, var, serial_list[0], *serial_list, command = select_serial)
dropdown.pack()
dropdown.configure(state='disable')
var.trace_add('write', serial_changed)

# add button using frame 
m_robot_move_btn = ttk.Frame(root)
m_robot_reset_btn = ttk.Frame(root)

robot_move_btn = ttk.Button(m_robot_move_btn, text="move robot", command=move_robot)
robot_move_btn.pack(side='left',padx=10) 
        
robot_reset_btn = ttk.Button(m_robot_reset_btn, text="reset robot", command=reset_robot)
robot_reset_btn.pack(side='left',padx=10)

# add button using frame 
m_serial_on = ttk.Frame(root)
m_serial_off = ttk.Frame(root)

serial_on_btn = ttk.Button(m_serial_on, text="enable serial", command=enable_serial)
serial_on_btn.pack(side='left',padx=10) 
        
serial_off_btn = ttk.Button(m_serial_off, text="disabe serial", command=disable_serial)
serial_off_btn.pack(side='left',padx=10)

# link 0 - base 
m_link0 = ttk.Frame(root)         
link0 = tk.StringVar()
ttk.Label(m_link0,text='base  ',font='Helvetica 10 bold').pack(side='left')
port0 = ttk.Entry(m_link0,width=6, textvariable = link0)
port0.insert('end','90')
port0.pack(side='left',padx=0,pady=5)
m_slide_0 = ttk.Frame(root)  
m_slide_0_track = ttk.Scale(m_slide_0, length = 200,  from_= 0, to = 180, orient ="vertical", command=slide_handler_base)
m_slide_0_track.set(angle_0)
m_slide_0_track.pack(side='left',padx=0,pady=5)

# link 1 - shoulder
m_link1 = ttk.Frame(root)         
link1 = tk.StringVar()
ttk.Label(m_link1,text='shoulder',font='Helvetica 10 bold').pack(side='left')
port1 = ttk.Entry(m_link1,width=6, textvariable = link1)
port1.insert('end','90')
port1.pack(side='left',padx=0,pady=5)
m_slide_1 = ttk.Frame(root)  
m_slide_1_track = ttk.Scale(m_slide_1, length = 200,  from_= 0, to = 180, orient ="vertical", command=slide_handler_shoulder)
m_slide_1_track.set(angle_1)
m_slide_1_track.pack(side='left',padx=0,pady=5)

# link 2 - forearm
m_link2 = ttk.Frame(root)         
link2 = tk.StringVar()
ttk.Label(m_link2,text='forearm',font='Helvetica 10 bold').pack(side='left')
port2 = ttk.Entry(m_link2,width=6, textvariable = link2)
port2.insert('end','90')
port2.pack(side='left',padx=0,pady=5)
m_slide_2 = ttk.Frame(root)  
m_slide_2_track = ttk.Scale(m_slide_2, length = 200,  from_= 0, to = 180, orient ="vertical", command=slide_handler_forearm)
m_slide_2_track.set(angle_2)
m_slide_2_track.pack(side='left',padx=0,pady=5)

# link 3 - upperarm
m_link3 = ttk.Frame(root)      
link3 = tk.StringVar()
ttk.Label(m_link3,text='upperarm',font='Helvetica 10 bold').pack(side='left')
port3 = ttk.Entry(m_link3,width=6, textvariable = link3)
port3.insert('end','90')
port3.pack(side='left',padx=0,pady=5)
m_slide_3 = ttk.Frame(root)  
m_slide_3_track = ttk.Scale(m_slide_3, length = 200,  from_= 0, to = 180, orient ="vertical", command=slide_handler_upperarm)
m_slide_3_track.set(angle_3)
m_slide_3_track.pack(side='left',padx=0,pady=5)

# add robot run stop button
m_robot_run_btn = ttk.Frame(root)
m_robot_stop_btn = ttk.Frame(root)
robot_run_btn = ttk.Button(m_robot_run_btn, text="run robot", command=run_robot)
robot_run_btn.pack(side='left', padx=10)
robot_stop_btn = ttk.Button(m_robot_stop_btn, text="stop robot", command=stop_robot)
robot_stop_btn.pack(side='left', padx=10)

# sequence robot run stop button
m_record = ttk.Frame(root)
m_sequence = ttk.Frame(root)
record_btn = ttk.Button(m_record, text="record pose", command=record_sequence)
record_btn.pack(side='left', padx=10)
sequence_btn = ttk.Button(m_sequence, text="start sequence", command=sequence_run)
sequence_btn.pack(side='left', padx=10)

# sequnce robot move list box 
m_action_listbox = tk.Listbox(root)

# grid layout 
m_robot_move_btn.grid(column=1,row=0,columnspan=3,padx=10,pady=10,sticky='w')
m_robot_reset_btn.grid(column=2,row=0,padx=10,pady=5,sticky='w')
m_link0.grid(column=1,row=1,padx=10,pady=5,sticky='w')
m_slide_0.grid(column=1,row=6,padx=15,pady=5,sticky='w')
m_link1.grid(column=2,row=1,padx=10,pady=5,sticky='w')
m_slide_1.grid(column=2,row=6,padx=15,pady=5,sticky='w')
m_link2.grid(column=3,row=1,padx=10,pady=5,sticky='w')
m_slide_2.grid(column=3,row=6,padx=15,pady=5,sticky='w')
m_link3.grid(column=4,row=1,padx=10,pady=5,sticky='w')
m_slide_3.grid(column=4,row=6,padx=15,pady=5,sticky='w')
m_robot_run_btn.grid(column=1, row=8,padx=10,pady=5,sticky='w')
m_robot_stop_btn.grid(column=2, row=8,padx=10,pady=5,sticky='w')
m_serial_select.grid(column=1,row=9,columnspan=3,padx=10,pady=10,sticky='w')
m_serial_on.grid(column=1, row=10,padx=10,pady=5,sticky='w')
m_serial_off.grid(column=2, row=10,padx=10,pady=5,sticky='w')
m_record.grid(column=1, row=11,padx=10,pady=5,sticky='w')
m_sequence.grid(column=2, row=11,padx=10,pady=5,sticky='w')
m_action_listbox.grid(column=1, row=12,padx=10,pady=5,sticky='w')
       
root.mainloop()