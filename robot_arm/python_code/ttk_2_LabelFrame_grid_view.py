import tkinter as tk
from tkinter import ttk

root = tk.Tk()
root.title('KG-KAIROS Robot Control')
root.geometry('800x600')


# Robot angle label frame  
base = ttk.Frame()
shoulder = ttk.Frame()
upperarm = ttk.Frame()
forearm = ttk.Frame()

# base angle 
base_label = ttk.Label(base,text='base angle: ',font='Helvetica 10 bold')
base_label.pack(side='left')
base_angle = ttk.Entry(base,width=6)
base_angle.insert('end','80')
base_angle.pack(side='left',padx=0,pady=5)
base.grid(column=0,row=0,padx=10,pady=5,sticky='w')

# shoulder angle 
shoulder_label = ttk.Label(shoulder,text='shoulder angle: ',font='Helvetica 10 bold')
shoulder_label.pack(side='left')
shoulder_angle = ttk.Entry(shoulder,width=6)
shoulder_angle.insert('end','80')
shoulder_angle.pack(side='left',padx=0,pady=5)
shoulder.grid(column=1,row=0,padx=10,pady=5,sticky='w')

# upperarm angle 
upperarm_label = ttk.Label(upperarm,text='upperarm angle: ',font='Helvetica 10 bold')
upperarm_label.pack(side='left')
upperarm_angle = ttk.Entry(upperarm,width=6)
upperarm_angle.insert('end','80')
upperarm_angle.pack(side='left',padx=0,pady=5)
upperarm.grid(column=2,row=0,padx=10,pady=5,sticky='w')

# forearm angle
forearm_label = ttk.Label(forearm,text='forearm angle: ',font='Helvetica 10 bold')
forearm_label.pack(side='left')
forearm_angle = ttk.Entry(forearm,width=6)
forearm_angle.insert('end','80')
forearm_angle.pack(side='left',padx=0,pady=5)
forearm.grid(column=3,row=0,padx=10,pady=5,sticky='w')


root.mainloop()



