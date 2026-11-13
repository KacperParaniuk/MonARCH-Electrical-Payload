# import numpy as np
# import tkinter as tk 
# from tkinter import ttk
# import matplotlib

# root = tk.Tk() // Tk() is a class 

# root.mainloop()

# from tabs.home import _build_home_tab # link the two .py files together
# from tabs.commanding import _build_cmd_tab
# from tabs.experiment import _build_exp_tab
# from tabs.telemetry import _build_telem_tab


# class DeviceApp(tk.Tk): # automatically places the root into the DeviceApp Class
#     def __init__(self): # we are inheriting all of tk into a new class. 
#         super().__init__() # inits the tk.Tk() like root = tk.Tk() << 
#         self.title("Payload Ground Control")
#         self.geometry("1920x1080")
#         self.selected_device = None 
#         self.windows = [] 

#         # Graphing stuff
#         self.input_file = None # wonder what this will be for. 
#         self.canvas = None


#         self.create_widgets()

#     def create_widgets(self): 
#         # Menu Bar
#         self.notebook = ttk.Notebook(self)
#         self.notebook.pack(fill="both", expand=True, padx=5, pady=5) # Device 


#         home_tab = ttk.Frame(self.notebook)
#         telem_tab = ttk.Frame(self.notebook)
#         exp_tab = ttk.Frame(self.notebook)
#         cmd_tab = ttk.Frame(self.notebook)

#         self.notebook.add(home_tab, text="HOME")
#         self.notebook.add(telem_tab, text="TELEMETRY")
#         self.notebook.add(exp_tab, text="EXPERIMENT")
#         self.notebook.add(cmd_tab, text="COMMANDING")


#         # default menu. 
#         self.notebook.select(home_tab)

#         _build_home_tab(self, home_tab)
#         _build_telem_tab(self, telem_tab)
#         _build_exp_tab(self, exp_tab)
#         _build_cmd_tab(self, cmd_tab)

 

# def main():
#     print("Hello from gss!")


# if __name__ == "__main__":
#     app = DeviceApp()
    
#     app.mainloop()




import tkinter as tk
import customtkinter as ctk

import serial
import serial.tools.list_ports

from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.animation import FuncAnimation

from reader import SerialReader


class GyroGui(ctk.CTk):
    def __init__(self):
        super().__init__()

        ctk.set_appearance_mode("System")
        ctk.set_default_color_theme("blue")

        self.title("Gyroscope Data - Live Capture & Plot")
        self.geometry("1100x700")
        self.minsize(1000, 650)

        # Core components
        self.serial_reader = SerialReader()

        # Plot throttling during resize/drag
        self.is_animation_paused_for_resize = False
        self.resize_resume_after_id = None

        # UI variables
        self.selected_port_name = tk.StringVar(value="")
        self.selected_baud_rate = tk.IntVar(value=115200)

        self.live_window_seconds = tk.DoubleVar(value=10.0) # Last N seconds

        # Dps per LSB: for ±500 dps typical is ~0.0175 dps/LSB
        self.gyro_scale_dps_per_lsb = tk.DoubleVar(value=0.0175)

        # Plot decimation (display only)
        self.maximum_points_per_curve = 2000

        # Cached UI texts (avoid reconfigure spam)
        self._last_window_label_text = ""
        self._last_status_text = ""
        self._last_line_text = ""

        self._build_user_interface()
        self._build_plots()
        self._install_resize_throttle()

        # ~30 FPS animation with blit; no frame caching
        self.animation = FuncAnimation(self.figure, self._update_plots,
                                       init_func=self._initialize_plot_artists,
                                       interval=33, blit=True, cache_frame_data=False,)

        # Periodic GUI refresh (labels only; low-frequency)
        self.after(250, self._refresh_status_labels)

        self._refresh_serial_ports()
        self.protocol("WM_DELETE_WINDOW", self._handle_close)

    # UI layout
    def _build_user_interface(self):
        self.grid_columnconfigure(1, weight=1)
        self.grid_rowconfigure(0, weight=1)

        self.control_panel = ctk.CTkFrame(self, corner_radius=12)
        self.control_panel.grid(row=0, column=0, padx=12, pady=12, sticky="nsw")
        self.control_panel.grid_rowconfigure(99, weight=1)

        ctk.CTkLabel(self.control_panel, text="Controls",
                     font=ctk.CTkFont(size=18, weight="bold"),).grid(row=0, column=0, padx=12, pady=(12, 8), sticky="w")

        # Serial port selection
        ctk.CTkLabel(self.control_panel, text="Serial Port").grid(row=1, column=0, padx=12, pady=(6, 0), sticky="w")
        self.port_option_menu = ctk.CTkOptionMenu(self.control_panel,
                                                  variable=self.selected_port_name, values=[""], width=220,)
        self.port_option_menu.grid(row=2, column=0, padx=12, pady=(4, 8), sticky="w")

        button_row = ctk.CTkFrame(self.control_panel, fg_color="transparent")
        button_row.grid(row=3, column=0, padx=12, pady=(0, 10), sticky="w")
        ctk.CTkButton(button_row, text="Refresh Ports",
                      command=self._refresh_serial_ports, width=110).grid(row=0, column=0, padx=(0, 8))
        ctk.CTkButton(button_row, text="Connect", command=self._connect_serial, width=80).grid(
            row=0, column=1, padx=(0, 8))
        ctk.CTkButton(button_row, text="Disconnect", command=self._disconnect_serial, width=100).grid(row=0, column=2)

        # Baud rate
        ctk.CTkLabel(self.control_panel, text="Baud Rate").grid(row=4, column=0, padx=12, pady=(6, 0), sticky="w")
        self.baud_rate_entry = ctk.CTkEntry(self.control_panel, textvariable=self.selected_baud_rate, width=120)
        self.baud_rate_entry.grid(row=5, column=0, padx=12, pady=(4, 12), sticky="w")

        # Live window length
        ctk.CTkLabel(self.control_panel, text="Live display window (seconds)").grid(
            row=6, column=0, padx=12, pady=(6, 0), sticky="w")
        self.live_window_slider = ctk.CTkSlider(self.control_panel, from_=1, to=120,
                                                number_of_steps=119, variable=self.live_window_seconds, width=220,)
        self.live_window_slider.grid(row=7, column=0, padx=12, pady=(6, 2), sticky="w")
        self.live_window_label = ctk.CTkLabel(self.control_panel, text="N = 10 s")
        self.live_window_label.grid(row=8, column=0, padx=12, pady=(0, 10), sticky="w")

        # Gyro scale
        ctk.CTkLabel(self.control_panel, text="Gyro scale (dps per LSB)").grid(
            row=12, column=0, padx=12, pady=(6, 0), sticky="w")
        self.gyro_scale_entry = ctk.CTkEntry(self.control_panel, textvariable=self.gyro_scale_dps_per_lsb, width=120)
        self.gyro_scale_entry.grid(row=13, column=0, padx=12, pady=(4, 12), sticky="w")
        ctk.CTkLabel(self.control_panel, text="Tip: ±500 dps typical ≈ 0.0175 dps/LSB").grid(
            row=14, column=0, padx=12, pady=(0, 10), sticky="w")

        ctk.CTkButton(self.control_panel, text="Clear Buffers",
                      command=self.serial_reader.clear_buffers,
                      width=220).grid(row=15, column=0, padx=12, pady=(6, 10), sticky="w")

        self.status_label = ctk.CTkLabel(self.control_panel, text="Status: Disconnected", justify="left", wraplength=240)
        self.status_label.grid(row=16, column=0, padx=12, pady=(6, 2), sticky="w")

        self.last_line_label = ctk.CTkLabel(self.control_panel, text="Last: (none)", justify="left", wraplength=240)
        self.last_line_label.grid(row=17, column=0, padx=12, pady=(2, 12), sticky="w")

        # Plot area
        self.plot_container = ctk.CTkFrame(self, corner_radius=12)
        self.plot_container.grid(row=0, column=1, padx=(0, 12), pady=12, sticky="nsew")
        self.plot_container.grid_rowconfigure(0, weight=1)
        self.plot_container.grid_columnconfigure(0, weight=1)

    # Plot building
    def _build_plots(self):
        self.figure = Figure(figsize=(7.5, 5.5), dpi=100)
        self.gyroscope_axis = self.figure.add_subplot(2, 1, 1)
        self.temperature_axis = self.figure.add_subplot(2, 1, 2)

        (self.gyro_x_line,) = self.gyroscope_axis.plot([], [], label="X", alpha=0.6, linewidth=1.5)
        (self.gyro_y_line,) = self.gyroscope_axis.plot([], [], label="Y", alpha=0.6, linewidth=1.5)
        (self.gyro_z_line,) = self.gyroscope_axis.plot([], [], label="Z", alpha=0.6, linewidth=1.5)
        (self.temperature_line,) = self.temperature_axis.plot([], [], label="Temperature")

        self.gyroscope_axis.set_title("Angular Velocity")
        self.gyroscope_axis.set_ylabel("deg/s (dps)")
        self.gyroscope_axis.set_xlabel("Time (s)")
        self.gyroscope_axis.legend(loc="upper right")
        self.gyroscope_axis.grid(True, alpha=0.2)
        self.gyroscope_axis.set_ylim(-500, 500)

        self.temperature_axis.set_title("Temperature")
        self.temperature_axis.set_ylabel("°C")
        self.temperature_axis.set_xlabel("Time (s)")
        self.temperature_axis.legend(loc="upper right")
        self.temperature_axis.grid(True, alpha=0.2)
        self.temperature_axis.set_ylim(0, 60)

        self.figure.subplots_adjust(top=0.93, bottom=0.08, hspace=0.35)

        self.canvas = FigureCanvasTkAgg(self.figure, master=self.plot_container)
        self.canvas.get_tk_widget().grid(row=0, column=0, sticky="nsew", padx=10, pady=10)

        self._apply_dark_plot_theme()

    def _initialize_plot_artists(self):
        self.gyro_x_line.set_data([], [])
        self.gyro_y_line.set_data([], [])
        self.gyro_z_line.set_data([], [])
        self.temperature_line.set_data([], [])
        return self.gyro_x_line, self.gyro_y_line, self.gyro_z_line, self.temperature_line

    def _apply_dark_plot_theme(self) -> None:
        figure_background = "#121212"
        axes_background = "#1e1e1e"
        foreground = "#e6e6e6"
        grid_color = "#3a3a3a"

        self.figure.patch.set_facecolor(figure_background)

        for axis in (self.gyroscope_axis, self.temperature_axis):
            axis.set_facecolor(axes_background)
            axis.tick_params(colors=foreground)
            axis.xaxis.label.set_color(foreground)
            axis.yaxis.label.set_color(foreground)
            axis.title.set_color(foreground)

            for spine in axis.spines.values():
                spine.set_color(foreground)

            axis.grid(True, alpha=0.25, color=grid_color)

            legend = axis.get_legend()
            if legend is not None:
                legend.get_frame().set_facecolor(axes_background)
                legend.get_frame().set_edgecolor(foreground)
                for text in legend.get_texts():
                    text.set_color(foreground)

    # Performance helpers
    def _install_resize_throttle(self):
        def handle_configure(_event):
            self.is_animation_paused_for_resize = True
            if self.resize_resume_after_id is not None:
                self.after_cancel(self.resize_resume_after_id)
            self.resize_resume_after_id = self.after(150, self._resume_after_resize)

        self.bind("<Configure>", handle_configure)

    def _resume_after_resize(self):
        self.resize_resume_after_id = None
        self.is_animation_paused_for_resize = False

    @staticmethod
    def _decimate_for_display(time_values, *signal_values, maximum_points: int):
        length = len(time_values)
        if length <= maximum_points or maximum_points <= 0:
            return time_values, *signal_values

        step = max(1, length // maximum_points)
        decimated_time = time_values[::step]
        decimated_signals = [values[::step] for values in signal_values]
        return decimated_time, *decimated_signals

    # Serial controls
    def _refresh_serial_ports(self):
        port_names = [port.device for port in serial.tools.list_ports.comports()]
        if not port_names:
            port_names = ["(no ports found)"]

        self.port_option_menu.configure(values=port_names)
        if self.selected_port_name.get() not in port_names:
            self.selected_port_name.set(port_names[0])

    def _connect_serial(self):
        port_name = self.selected_port_name.get()
        if not port_name or port_name == "(no ports found)":
            self._set_status_text("No valid COM port selected.")
            return

        try:
            baud_rate = int(self.selected_baud_rate.get())
        except (TypeError, ValueError):
            self._set_status_text("Invalid baud rate.")
            return

        try:
            self.serial_reader.connect(port_name, baud_rate)
            self._set_status_text(self.serial_reader.connection_status)
        except serial.SerialException as exc:
            self._set_status_text(f"Connect failed: {exc}")

    def _disconnect_serial(self):
        self.serial_reader.disconnect()
        self._set_status_text("Disconnected")

    # Status labels
    def _set_status_text(self, message: str):
        text = f"Status: {message}"
        if text != self._last_status_text:
            self._last_status_text = text
            self.status_label.configure(text=text)

    def _refresh_status_labels(self):
        window_label_text = f"N = {self.live_window_seconds.get():.0f} s"
        if window_label_text != self._last_window_label_text:
            self._last_window_label_text = window_label_text
            self.live_window_label.configure(text=window_label_text)

        last_line_text = f"Last: {getattr(self.serial_reader, 'last_received_line', '') or '(none)'}"
        if last_line_text != self._last_line_text:
            self._last_line_text = last_line_text
            self.last_line_label.configure(text=last_line_text)

        self.after(250, self._refresh_status_labels)    # Do not spam status; reader updates connection_status on errors

    # Plot updating (~30 FPS)
    def _update_plots(self, _frame_index):
        # Pause drawing during resize/drag for responsiveness
        if self.is_animation_paused_for_resize:
            return self.gyro_x_line, self.gyro_y_line, self.gyro_z_line, self.temperature_line

        # Read window length and gyro scale
        try:
            window_seconds = float(self.live_window_seconds.get())
            if window_seconds <= 0:
                window_seconds = 10.0
        except (TypeError, ValueError):
            window_seconds = 10.0

        try:
            scale_dps_per_lsb = float(self.gyro_scale_dps_per_lsb.get())
        except (TypeError, ValueError):
            scale_dps_per_lsb = 0.0175

        # Pull only the last N seconds from ring buffers (fast path)
        with self.serial_reader.data_lock:
            gyroscope_time_s, gyro_x, gyro_y, gyro_z = self.serial_reader.gyroscope_buffer.window(window_seconds)
            temperature_time_s, temperature_c, _, _ = self.serial_reader.temperature_buffer.window(window_seconds)

        # Decimate for display speed
        gyroscope_time_s, gyro_x, gyro_y, gyro_z = (
            self._decimate_for_display(gyroscope_time_s,
                                       gyro_x, gyro_y, gyro_z,
                                       maximum_points=self.maximum_points_per_curve))
        temperature_time_s, temperature_c = (
            self._decimate_for_display(temperature_time_s,
                                       temperature_c,
                                       maximum_points=self.maximum_points_per_curve))[:2]

        # Update plot lines
        if len(gyroscope_time_s) > 0:
            self.gyro_x_line.set_data(gyroscope_time_s, gyro_x * scale_dps_per_lsb)
            self.gyro_y_line.set_data(gyroscope_time_s, gyro_y * scale_dps_per_lsb)
            self.gyro_z_line.set_data(gyroscope_time_s, gyro_z * scale_dps_per_lsb)
            self.gyroscope_axis.set_xlim(0, window_seconds)
        else:
            self.gyro_x_line.set_data([], [])
            self.gyro_y_line.set_data([], [])
            self.gyro_z_line.set_data([], [])
            self.gyroscope_axis.set_xlim(0, window_seconds)

        if len(temperature_time_s) > 0:
            self.temperature_line.set_data(temperature_time_s, temperature_c)
            self.temperature_axis.set_xlim(0, window_seconds)
        else:
            self.temperature_line.set_data([], [])
            self.temperature_axis.set_xlim(0, window_seconds)

        return self.gyro_x_line, self.gyro_y_line, self.gyro_z_line, self.temperature_line

    def _handle_close(self):
        try:
            self.serial_reader.disconnect()
        finally:
            self.destroy()


if __name__ == "__main__":
    application = GyroGui()
    application.mainloop()