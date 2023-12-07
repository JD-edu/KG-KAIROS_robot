import tkinter as tk

def on_button_clicked(event):
    print("Button 1 clicked!")

def on_button_2_clicked(event):
    print("Button 2 clicked!")

root = tk.Tk()

# 드롭다운 메뉴 생성
menu = tk.Menu(root)
item1 = tk.MenuItem(menu, text="항목 1")
item2 = tk.MenuItem(menu, text="항목 2")
item3 = tk.MenuItem(menu, text="항목 3")
menu.add_cascade(label="메뉴", menu=menu)

# 슬라이드 버튼 생성
for i in range(6):
    button = tk.Scale(root, from_=0, to=100, orient=tk.HORIZONTAL)
    button.pack()

# 클릭 버튼 생성
button1 = tk.Button(root, text="버튼 1", command=on_button_clicked)
button2 = tk.Button(root, text="버튼 2", command=on_button_2_clicked)
button1.pack()
button2.pack()

root.mainloop()
