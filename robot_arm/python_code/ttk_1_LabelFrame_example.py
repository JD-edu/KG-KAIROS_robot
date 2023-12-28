import tkinter as tk
from tkinter import ttk

root = tk.Tk()
root.title('KG-KAIROS Robot Control')
root.geometry('600x480')

base = ttk.LabelFrame(root, text="로봇관절각도")

base_label = ttk.Label(base,text='base angle: ',font='Helvetica 10 bold')
base_label.pack(side='left')

base_angle = ttk.Entry(base,width=6)
base_angle.insert('end','80')
base_angle.pack(side='left',padx=0,pady=5)

base.grid(column=1,row=3,padx=10,pady=5,sticky='w')

root.mainloop()



