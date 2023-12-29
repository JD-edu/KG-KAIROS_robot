import tkinter as tk
from tkinter import ttk
from tkinter import messagebox 
import serial

def robot_move():
    cmd = 'a'+str(int(base_bar.get()))+'b'+str(int(shoulder_bar.get()))+'c'+str(int(upperarm_bar.get()))+'d'+str(int(forearm_bar.get()))+'e\n'
    seq.write(cmd.encode())
    print(cmd.encode())

def robot_origin():
    cmd = 'a90b90c90d\n'
    seq.write(cmd.encode())
    print(cmd.encode())
    

def base_bar_changed(event):
    print(base_bar.get())
    
def shoulder_bar_changed(event):
    print(shoulder_bar.get())
    

def upperarm_bar_changed(event):
    print(upperarm_bar.get())
    
def forearm_bar_changed(event):
    print(forearm_bar.get())

root = tk.Tk()
root.title('KG-KAIROS Robot Control')
root.geometry('600x480')
        
button = tk.Button(root, text='로봇 이동하기', command=robot_move)
button.pack()

# 슬라이드 버튼 생성
base_bar = ttk.Scale(root, from_=30, to=120, orient=tk.HORIZONTAL, command=base_bar_changed)
base_bar.pack()

# 슬라이드 버튼 생성
shoulder_bar = ttk.Scale(root, from_=30, to=120, orient=tk.HORIZONTAL, command=shoulder_bar_changed)
shoulder_bar.pack()

# 슬라이드 버튼 생성
upperarm_bar = ttk.Scale(root, from_=30, to=120, orient=tk.HORIZONTAL, command=upperarm_bar_changed)
upperarm_bar.pack()

# 슬라이드 버튼 생성
forearm_bar = ttk.Scale(root, from_=30, to=120, orient=tk.HORIZONTAL, command=forearm_bar_changed)
forearm_bar.pack()

button = tk.Button(root, text='로봇 원점 이동', command=robot_origin)
button.pack()

# Serial port 
seq = serial.Serial(
            baudrate=115200,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            timeout=1
        )
        
seq.port = "COM7"
seq.open()

root.mainloop()
        


