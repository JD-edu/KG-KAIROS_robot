
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

def move_robot():
    global angle_0, angle_1, angle_2, angle_3
    print("robot move")
    cmd = "2a"+str(angle_0)+"b"+str(angle_1)+"c"+str(angle_2)+"d"+str(angle_3)+"e\n"
    seq.write(cmd.encode())
   
def reset_robot():
    global angle_0, angle_1, angle_2, angle_3
    print("reset robot")
    seq.write("3\n".encode())
    port1.delete(0, 'end')
    port1.insert(0, '90')
    angle_0 = 90
    m_slide_0_track.set(angle_0)
    port2.delete(0, 'end')
    port2.insert(0, '90')
    angle_1 = 90
    m_slide_1_track.set(angle_1)
    port3.delete(0, 'end')
    port3.insert(0, '90')
    angle_2 = 90
    m_slide_2_track.set(angle_2)
    port4.delete(0, 'end')
    port4.insert(0, '90')
    angle_3 = 90
    m_slide_3_track.set(angle_3)

def slide_handler_base(event):
    global angle_0
    angle_0 = m_slide_0_track.get()
    print(angle_0)
    port1.delete(0, 'end')
    port1.insert(0, str(int(angle_0)))

def slide_handler_shoulder(event):
    global angle_1
    angle_1 = m_slide_1_track.get()
    print(angle_1)
    port2.delete(0, 'end')
    port2.insert(0, str(int(angle_1)))

def slide_handler_forearm(event):
    global angle_2
    angle_2 = m_slide_2_track.get()
    print(angle_2)
    port3.delete(0, 'end')
    port3.insert(0, str(int(angle_2)))

def slide_handler_upperarm(event):
    global angle_3
    angle_3 = m_slide_3_track.get()
    print(angle_3)
    port4.delete(0, 'end')
    port4.insert(0, str(int(angle_3)))

record_action = []
def record_action():
    print("record")
    record_action.append("uga")
    action_listbox.insert(tk.END, "uga")

seq = serial.Serial(
        baudrate=115200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
    )

seq.port = "COM6"
seq.open()

# Angle values for 4 robot arm joints 
angle_0 = 90
angle_1 = 90
angle_2 = 90
angle_3 = 90

root = tk.Tk()
root.title('KG-KAIROS Robot Control')
root.geometry('600x600')

# add button using frame 
m_robot_move_btn = ttk.Frame(root)
m_robot_reset_btn = ttk.Frame(root)

robot_move_btn = ttk.Button(m_robot_move_btn, text="move robot", command=move_robot)
robot_move_btn.pack(side='left',padx=10) 
        
robot_reset_btn = ttk.Button(m_robot_reset_btn, text="reset robot", command=reset_robot)
robot_reset_btn.pack(side='left',padx=10)

# add servo value  frame
m_link0 = ttk.Frame(root)       # link 0  
link0 = tk.StringVar()
ttk.Label(m_link0,text='base  ',font='Helvetica 10 bold').pack(side='left')
port1 = ttk.Entry(m_link0,width=6, textvariable = link0)
port1.insert('end','90')
port1.pack(side='left',padx=0,pady=5)

m_link1 = ttk.Frame(root)       # link 1
link1 = tk.StringVar()
ttk.Label(m_link1,text='shoulder',font='Helvetica 10 bold').pack(side='left')
port2 = ttk.Entry(m_link1,width=6, textvariable = link1)
port2.insert('end','90')
port2.pack(side='left',padx=0,pady=5)

m_link2 = ttk.Frame(root)       # link 2
link2 = tk.StringVar()
ttk.Label(m_link2,text='fore arm',font='Helvetica 10 bold').pack(side='left')
port3 = ttk.Entry(m_link2,width=6, textvariable = link2)
port3.insert('end','90')
port3.pack(side='left',padx=0,pady=5)

m_link3 = ttk.Frame(root)       # link 3
link3 = tk.StringVar()
ttk.Label(m_link3,text='upper arm',font='Helvetica 10 bold').pack(side='left')
port4 = ttk.Entry(m_link3,width=6, textvariable = link3)
port4.insert('end','90')
port4.pack(side='left',padx=0,pady=5)

# add slider using 
m_slide_0 = ttk.Frame(root)  
m_slide_0_track = ttk.Scale(m_slide_0, length = 200,  from_= 0, to = 180, orient ="vertical", command=slide_handler_base)
m_slide_0_track.set(angle_0)
m_slide_0_track.pack(side='left',padx=0,pady=5)

m_slide_1 = ttk.Frame(root)  
m_slide_1_track = ttk.Scale(m_slide_1, length = 200,  from_= 0, to = 180, orient ="vertical", command=slide_handler_shoulder)
m_slide_1_track.set(angle_1)
m_slide_1_track.pack(side='left',padx=0,pady=5)

m_slide_2 = ttk.Frame(root)  
m_slide_2_track = ttk.Scale(m_slide_2, length = 200,  from_= 0, to = 180, orient ="vertical", command=slide_handler_forearm)
m_slide_2_track.set(angle_2)
m_slide_2_track.pack(side='left',padx=0,pady=5)

m_slide_3 = ttk.Frame(root)  
m_slide_3_track = ttk.Scale(m_slide_3, length = 200,  from_= 0, to = 180, orient ="vertical", command=slide_handler_upperarm)
m_slide_3_track.set(angle_3)
m_slide_3_track.pack(side='left',padx=0,pady=5)

action_listbox = tk.Listbox(root)
action_listbox.configure(yscrollcommand=True)

m_record = ttk.Frame(root)  
record_btn = ttk.Button(m_record, text="record action", command=record_action)
record_btn.pack(side='left',padx=10) 


# grid layout 
m_robot_move_btn.grid(column=1,row=0,columnspan=3,padx=10,pady=10,sticky='w')
m_robot_reset_btn.grid(column=2,row=0,padx=10,pady=5,sticky='w')
m_link0.grid(column=1,row=1,padx=10,pady=5,sticky='w')
m_link1.grid(column=2,row=1,padx=10,pady=5,sticky='w')
m_link2.grid(column=3,row=1,padx=10,pady=5,sticky='w')
m_link3.grid(column=4,row=1,padx=10,pady=5,sticky='w')
m_slide_0.grid(column=1,row=6,padx=15,pady=5,sticky='w')
m_slide_1.grid(column=2,row=6,padx=15,pady=5,sticky='w')
m_slide_2.grid(column=3,row=6,padx=15,pady=5,sticky='w')
m_slide_3.grid(column=4,row=6,padx=15,pady=5,sticky='w')
action_listbox.grid(row=7, columnspan=2, padx=5, pady=5)
m_record.grid(row=8, columnspan=2, padx=5, pady=5)

root.mainloop()