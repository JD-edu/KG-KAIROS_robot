import tkinter as tk
from tkinter import ttk
from tkinter import messagebox 
import serial

def robot_move():
    cmd = '2a'+str(int(base_bar.get()))+'b'+str(int(shoulder_bar.get()))+'c'+str(int(upperarm_bar.get()))+'d'+str(int(forearm_bar.get()))+'e\n'
    seq.write(cmd.encode())
    print(cmd.encode())

def robot_origin():
    cmd = '2a90b90c90d90e\n'
    seq.write(cmd.encode())
    base_bar.set(90)
    shoulder_bar.set(90)
    upperarm_bar.set(90)
    forearm_bar.set(90)
    print(cmd.encode())

def read_robot_angle():
    cmd = '111\n'
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
        
button = tk.Button(root, text='robot move', command=robot_move)
button.pack()

# 슬라이드 버튼 생성
base_bar = ttk.Scale(root, from_=0, to=180, orient=tk.HORIZONTAL, command=base_bar_changed)
base_bar.set(90)
base_bar.pack()

# 슬라이드 버튼 생성
shoulder_bar = ttk.Scale(root, from_=0, to=180, orient=tk.HORIZONTAL, command=shoulder_bar_changed)
shoulder_bar.set(90)
shoulder_bar.pack()

# 슬라이드 버튼 생성
upperarm_bar = ttk.Scale(root, from_=0, to=180, orient=tk.HORIZONTAL, command=upperarm_bar_changed)
upperarm_bar.set(90)
upperarm_bar.pack()

# 슬라이드 버튼 생성
forearm_bar = ttk.Scale(root, from_=0, to=180, orient=tk.HORIZONTAL, command=forearm_bar_changed)
forearm_bar.set(90)
forearm_bar.pack()

button = tk.Button(root, text='로봇 원점 이동', command=robot_origin)
button.pack()

button = tk.Button(root, text='로봇 각도 읽기', command=read_robot_angle)
button.pack()

# Serial port 
seq = serial.Serial(
            baudrate=115200,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            timeout=1
        )
        
seq.port = "COM8"
seq.open()

root.mainloop()
        


