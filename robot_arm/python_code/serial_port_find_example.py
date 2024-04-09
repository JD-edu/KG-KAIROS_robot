import sys
import serial
import glob
import tkinter as tk
from tkinter import ttk
import threading
import time  

class Fake(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.seq = serial.Serial(
            baudrate=115200,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            timeout=1
        )
        #self.seq.port = port
        self.daemon = True

    def run(self):
        while True:
            if self.seq.isOpen() == True:  
                try:
                    if self.seq.inWaiting():
                        try: 
                            self.command = self.seq.readline()
                            baseAngle = self.command.decode()
                            print(baseAngle)
                        except ValueError:
                            print("value error")         
                except IOError:
                    print("IO error")

    def set_port(self, port):
        self.seq.port = port 


def select_serial(event):
    print("uga")

def serial_on():
    t.start()
def serial_off():
    pass # seq.close()

def serial_changed(varname, index, mode):
    print("serial changed")
    p = var.get()
    t.set_port(p)

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

serial_list = serial_ports()

t = Fake()

'''seq = serial.Serial(
        baudrate=115200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
    )'''

# 농막 지을 땅에 공구리 치기 
root = tk.Tk()
root.title('KG-KAIROS Robot Control')
root.geometry('600x480')

# dropdown menu code 1 
#serial_list = ['COM1', 'COM2', 'COM3']
m_serial_select = ttk.Frame(root)
var = tk.StringVar()
dropdown = ttk.OptionMenu(m_serial_select, var, serial_list[0], *serial_list, command = select_serial)
dropdown.pack()
dropdown.configure(state='normal')
var.trace_add('write', serial_changed)

m_serial_on = ttk.Frame(root)
m_serial_off = ttk.Frame(root)

serial_on_btn = ttk.Button(m_serial_on, text="serial_on", command=serial_on)
serial_on_btn.pack(side='left',padx=10) 
        
serial_off_btn = ttk.Button(m_serial_off, text="serial_off", command=serial_off)
serial_off_btn.pack(side='left',padx=10)

m_serial_select.grid(column=0,row=0,columnspan=3,padx=10,pady=10,sticky='w')
m_serial_on.grid(column=0, row=2,columnspan=3,padx=10,pady=10,sticky='w')
m_serial_off.grid(column=0,row=3,padx=10,pady=5,sticky='w')

root.mainloop()

