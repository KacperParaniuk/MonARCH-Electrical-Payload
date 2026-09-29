import numpy as np
import tkinter as tk 
from tkinter import ttk
import matplotlib

# root = tk.Tk() // Tk() is a class 

# root.mainloop()

from tabs.home import _build_home_tab # link the two .py files together
from tabs.commanding import _build_cmd_tab
from tabs.experiment import _build_exp_tab
from tabs.telemetry import _build_telem_tab


class DeviceApp(tk.Tk): # automatically places the root into the DeviceApp Class
    def __init__(self): # we are inheriting all of tk into a new class. 
        super().__init__() # inits the tk.Tk() like root = tk.Tk() << 
        self.title("Payload Ground Control")
        self.geometry("1920x1080")
        self.selected_device = None 
        self.windows = [] 

        # Graphing stuff
        self.input_file = None # wonder what this will be for. 
        self.canvas = None


        self.create_widgets()

    def create_widgets(self): 
        # Menu Bar
        self.notebook = ttk.Notebook(self)
        self.notebook.pack(fill="both", expand=True, padx=5, pady=5) # Device 


        home_tab = ttk.Frame(self.notebook)
        telem_tab = ttk.Frame(self.notebook)
        exp_tab = ttk.Frame(self.notebook)
        cmd_tab = ttk.Frame(self.notebook)

        self.notebook.add(home_tab, text="HOME")
        self.notebook.add(telem_tab, text="TELEMETRY")
        self.notebook.add(exp_tab, text="EXPERIMENT")
        self.notebook.add(cmd_tab, text="COMMANDING")


        # default menu. 
        self.notebook.select(home_tab)

        _build_home_tab(self, home_tab)
        _build_telem_tab(self, telem_tab)
        _build_exp_tab(self, exp_tab)
        _build_cmd_tab(self, cmd_tab)

 

def main():
    print("Hello from gss!")


if __name__ == "__main__":
    app = DeviceApp()
    
    app.mainloop()


