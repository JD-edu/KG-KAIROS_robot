'''
MIT License

Copyright (c) 2024 JD edu. http://jdedu.kr author: conner.jeong@gmail.com
     
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
     
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
     
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN TH
SOFTWARE.
'''
import tkinter as tk
from tkinter import ttk

def on_select(value):
  print("You selected:", value)

# Create the main window
root = tk.Tk()
root.title("Dropdown Menu Example")
root.geometry('600x480')

# Define variable to store the selected fruit
selected_fruit = tk.StringVar()
selected_fruit.set("Choose a fruit...")  # Set default option

# Create the dropdown menu
fruit_options = ("Apple", "Banana", "Orange", "Grape")
dropdown = ttk.Combobox(root, textvariable=selected_fruit, values=fruit_options)
dropdown.pack(padx=10, pady=10)

# Create a function to be called when a fruit is selected
dropdown.bind("<<ComboboxSelected>>", on_select)

# Start the main event loop
root.mainloop()
