import tkinter as tk
from tkinter import ttk

# Sample list of options
serial_list = ["COM1", "COM2", "COM3"]

# Function to be called when the selection changes
def handle_selection(selection):
  print("Selected:", selection)

# Create the main window
root = tk.Tk()
root.title("OptionMenu Example")

# String variable to hold the selected value
selected_var = tk.StringVar()
selected_var.set(serial_list[0])  # Set initial selection

# Create the dropdown menu
dropdown = ttk.OptionMenu(root, selected_var, *serial_list, command=handle_selection)
dropdown.pack()

# Run the main event loop
root.mainloop()