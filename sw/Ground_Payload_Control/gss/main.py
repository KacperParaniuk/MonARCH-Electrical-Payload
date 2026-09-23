import numpy as np
import tkinter as tk 
import matplotlib

# root = tk.Tk() // Tk() is a class 

root.mainloop()


class DeviceApp(tk.Tk): # automatically places the root into the DeviceApp Class
    def __init__(self):
        super().__init__() # inits the tk.Tk()
        self.title("Payload Ground Control")
        self.geometry("1920x1080")
        self.selected_device = None 
        self.windows = [] 

        # Graphing stuff
        self.input_file = None
        self.canvas = None


        self.create_widgets()

    def create_widgets(self): 

        


def main():
    print("Hello from gss!")


if __name__ == "__main__":
    app = D
    main()
