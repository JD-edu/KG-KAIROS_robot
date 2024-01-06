import tkinter as tk
from tkinter import ttk

def select_serial():
    pass

def start_serial():
    pass

def stop_serial():
    pass

serial_list = ['시리얼 포트를 선택하세요.']

root = tk.Tk()
root.title('KG-KAIROS Robot Control')
root.geometry('600x480')

m_serial_select = ttk.Frame(root)
var = tk.StringVar()
m_serial_select.pack()

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
m_serial_start_btn = ttk.Frame(root)
m_serial_stop_btn = ttk.Frame(root)

start_serial_btn = ttk.Button(m_serial_start_btn, text="Start serial", command=start_serial)
start_serial_btn.pack(side='left',padx=10) 
        
stop_serial_btn = ttk.Button(m_serial_stop_btn, text="Stop serial", command=stop_serial)
stop_serial_btn.pack(side='left',padx=10)

start_serial_btn.configure(state='disable')
stop_serial_btn.configure(state='disable')

# grid layout 
m_serial_select.grid(column=1,row=0,columnspan=3,padx=10,pady=10,sticky='w')
m_serial_start_btn.grid(column=1,row=1,padx=10,pady=5,sticky='w')
m_serial_stop_btn.grid(column=2,row=1,padx=10,pady=5,sticky='w')
       
root.mainloop()


