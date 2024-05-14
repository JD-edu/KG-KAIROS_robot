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
