import tkinter as tk
from tkinter import ttk

def uga():
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
dropdown = ttk.OptionMenu(m_serial_select, var, serial_list[0], *serial_list, command = uga)
dropdown.pack()
dropdown.configure(state='normal')


root.mainloop()


