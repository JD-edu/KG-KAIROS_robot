import tkinter as tk
from tkinter import ttk

root = tk.Tk()
root.title('KG-KAIROS Robot Control')
root.geometry('800x600')

# Robot angle label frame  
robot_angle = ttk.LabelFrame(root, text="로봇관절각도")
robot_angle.grid(column=0, row=0, padx=10, pady=10, ipadx=10, ipady=10)



# base angle 
base_label = ttk.Label(robot_angle,text='base angle: ',font='Helvetica 10 bold')
base_label.pack(side='left')
base_angle = ttk.Entry(robot_angle,width=6)
base_angle.insert('end','80')
base_angle.pack(side='left',padx=0,pady=5)
robot_angle.grid(column=0,row=0,padx=10,pady=5,sticky='w')

# shoulder angle 
shoulder_label = ttk.Label(robot_angle,text='shoulder angle: ',font='Helvetica 10 bold')
shoulder_label.pack(side='left')
shoulder_angle = ttk.Entry(robot_angle,width=6)
shoulder_angle.insert('end','80')
shoulder_angle.pack(side='left',padx=0,pady=5)
robot_angle.grid(column=0,row=1,padx=10,pady=5,sticky='w')

# upperarm angle 
upperarm_label = ttk.Label(robot_angle,text='upperarm angle: ',font='Helvetica 10 bold')
upperarm_label.pack(side='left')
upperarm_angle = ttk.Entry(robot_angle,width=6)
upperarm_angle.insert('end','80')
upperarm_angle.pack(side='left',padx=0,pady=5)
robot_angle.grid(column=0,row=2,padx=10,pady=5,sticky='w')

# forearm angle
forearm_label = ttk.Label(robot_angle,text='forearm angle: ',font='Helvetica 10 bold')
forearm_label.pack(side='left')
forearm_angle = ttk.Entry(robot_angle,width=6)
forearm_angle.insert('end','80')
forearm_angle.pack(side='left',padx=0,pady=5)
robot_angle.grid(column=0,row=2,padx=10,pady=5,sticky='w')

# button label frame 
robot_control = ttk.LabelFrame(root, text="로봇 동작제어 ")
robot_control.grid(column=0, row=1, padx=10, pady=10, ipadx=10, ipady=10)

# robot origin button
robot_origin = ttk.Label(robot_control,text='로봇 원점: ',font='Helvetica 10 bold')
robot_origin.pack(side='left')
robot_control.grid(column=1,row=1,padx=10,pady=5,sticky='w')

root.mainloop()



