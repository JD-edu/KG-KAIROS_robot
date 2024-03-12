
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
    print("robot move")
    seq.write("2a120b120c120d120e120\n".encode())
   
def reset_robot():
    print("reset robot")
    seq.write("3\n".encode())
  

seq = serial.Serial(
        baudrate=115200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
    )


seq.port = "COM17"
seq.open()


root = tk.Tk()
root.title('KG-KAIROS Robot Control')
root.geometry('600x480')

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
port1.insert('end','80')
port1.pack(side='left',padx=0,pady=5)

# grid layout 
m_robot_move_btn.grid(column=1,row=0,columnspan=3,padx=10,pady=10,sticky='w')
m_robot_reset_btn.grid(column=2,row=0,padx=10,pady=5,sticky='w')
m_link0.grid(column=1,row=1,padx=10,pady=5,sticky='w')
       
root.mainloop()