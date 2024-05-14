import tkinter as tk
from tkinter import ttk
import threading 
import sys
import glob
import serial
import time 

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

def serial_on():
    print("serial on")
    seq.open()

def serial_off():
    print("serial off")
    seq.close()

def select_serial(event):
    print("select serial")

def serial_changed(varname, index, mode):
    global var, seq
    print(var.get())
    seq.port = var.get()

# serial finder function 
def startTimer(iTimeSec,isRepeated):
    print("startTimer")
    timer_thread1 = threading.Timer(iTimeSec, timerCallBack,[iTimeSec,isRepeated])
    timer_thread1.daemon = True
    timer_thread1.start() 

def timerCallBack(iTimeSec,isRepeated):
    global serial_list  # It shoud be here.
    print("TimerCallback")
    result = serial_ports() # it takes 3~4 seconds. 
    serial_list = result
    print(serial_list)
    update_option_menu()
    dropdown.configure(state='enable')

def update_option_menu():
    global dropdown
    global serial_list
    menu = dropdown["menu"]
    menu.delete(0, "end")
    for string in serial_list:
        menu.add_command(label=string, command=lambda value=string: var.set(value))

# to check execution time of serial_ports(). It takes 3~4 seconds.
#print("=====")
#print(serial_ports())
#print("=====")
        
seq = serial.Serial(
        baudrate=115200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
    )

startTimer(1, False)

root = tk.Tk()
root.title('KG-KAIROS Robot Control')
root.geometry('600x480')

# dropdown menu code 1 
serial_list = ['COM1', 'COM2', 'COM3']
m_serial_select = ttk.Frame(root)
var = tk.StringVar()

# add option menu
dropdown = ttk.OptionMenu(m_serial_select, var, serial_list[0], *serial_list, command = select_serial)
dropdown.pack()
dropdown.configure(state='disable')
var.trace_add('write',serial_changed)

# add button using frame 
m_serial_on = ttk.Frame(root)
m_serial_off = ttk.Frame(root)

serial_on_btn = ttk.Button(m_serial_on, text="serial_on", command=serial_on)
serial_on_btn.pack(side='left',padx=10) 
        
robot_reset_btn = ttk.Button(m_serial_off, text="serial_off", command=serial_off)
robot_reset_btn.pack(side='left',padx=10)

m_serial_select.grid(column=0,row=0,columnspan=3,padx=10,pady=10,sticky='w')
m_serial_on.grid(column=0, row=2,columnspan=3,padx=10,pady=10,sticky='w')
m_serial_off.grid(column=0,row=3,padx=10,pady=5,sticky='w')

root.mainloop()