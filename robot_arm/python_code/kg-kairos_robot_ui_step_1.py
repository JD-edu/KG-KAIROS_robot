import tkinter as tk
from tkinter import ttk
from tkinter import messagebox 

def button_click():
    messagebox.showinfo('알림','버튼이 클릭되었습니다.')

def slide_bar_changed(event):
    if slide_bar.get() == 50:
        messagebox.showinfo('알림', '슬라이드 버튼의 값이 50입니다.')

root = tk.Tk()
root.title('KG-KAIROS Robot Control')
root.geometry('600x480')
        
button = tk.Button(root, text='클릭하세요', command=button_click)
button.pack()

# 슬라이드 버튼 생성
slide_bar = ttk.Scale(root, from_=0, to=100, orient=tk.HORIZONTAL, command=slide_bar_changed)
slide_bar.pack()

root.mainloop()
        


