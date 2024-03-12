
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

def select_serial(event):
    print("serial drop down")

def move_robot():
    print("robot move")
    seq.write("2a120b120c120d120e120\n".encode())
   
def reset_robot():
    print("reset robot")
    seq.write("3\n".encode())

def slide_handler_base(event):
    global angle_0
    angle_0 = m_slide_0_track.get()
    print(angle_0)
    port1.delete(0, 'end')
    port1.insert(0, str(int(angle_0)))

def run_robot():
    global angle_0
    cmd = '2a'+str(int(angle_0))+'b90c90d90e\n'
    print(cmd)
    seq.write(cmd.encode())
    print(cmd.encode())

def stop_robot():
    pass

seq = serial.Serial(
        baudrate=115200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
    )

seq.port = "COM17"
seq.open()



angle_0 = 90

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
dropdown.configure(state='normal')

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

# add slider using 
m_slide_0 = ttk.Frame(root)  
m_slide_0_track = ttk.Scale(m_slide_0, length = 200,  from_= 0, to = 180, orient ="vertical", command=slide_handler_base)
m_slide_0_track.set(angle_0)
m_slide_0_track.pack(side='left',padx=0,pady=5)

# add robot run stop button
m_robot_run_btn = ttk.Frame(root)
m_robot_stop_btn = ttk.Frame(root)
robot_run_btn = ttk.Button(m_robot_run_btn, text="run robot", command=run_robot)
robot_run_btn.pack(side='left', padx=10)
robot_stop_btn = ttk.Button(m_robot_stop_btn, text="stop robot", command=stop_robot)
robot_stop_btn.pack(side='left', padx=10)

# grid layout 
m_robot_move_btn.grid(column=1,row=0,columnspan=3,padx=10,pady=10,sticky='w')
m_robot_reset_btn.grid(column=2,row=0,padx=10,pady=5,sticky='w')
m_link0.grid(column=1,row=1,padx=10,pady=5,sticky='w')
m_slide_0.grid(column=1,row=6,padx=15,pady=5,sticky='w')
m_robot_run_btn.grid(column=1, row=8,padx=10,pady=5,sticky='w')
m_robot_stop_btn.grid(column=2, row=8,padx=10,pady=5,sticky='w')
m_serial_select.grid(column=1,row=9,columnspan=3,padx=10,pady=10,sticky='w')
       
root.mainloop()