import tkinter as tk
from tkinter import ttk
from tkinter import messagebox 

def button_click():
    messagebox.showinfo('알림','버튼이 클릭되었습니다.')

def base_bar_changed(event):
    print(base_bar.get())

def shoulder_bar_changed(event):
    print(shoulder_bar.get())

def upperarm_bar_changed(event):
    print(upperarm_bar.get())

root = tk.Tk()
root.title('KG-KAIROS Robot Control')
root.geometry('600x480')
        
button = tk.Button(root, text='클릭하세요', command=button_click)
button.pack()

# 슬라이드 버튼 생성
base_bar = ttk.Scale(root, from_=0, to=100, orient=tk.HORIZONTAL, command=base_bar_changed)
base_bar.pack()

# 슬라이드 버튼 생성
shoulder_bar = ttk.Scale(root, from_=0, to=100, orient=tk.HORIZONTAL, command=shoulder_bar_changed)
shoulder_bar.pack()

# 슬라이드 버튼 생성
upperarm_bar = ttk.Scale(root, from_=0, to=100, orient=tk.HORIZONTAL, command=upperarm_bar_changed)
upperarm_bar.pack()




root.mainloop()
        


