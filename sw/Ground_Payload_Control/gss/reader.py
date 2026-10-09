# the serial port stuff 

# built from https://github.com/8Altair/Gyroscope-data-streaming/blob/main/GUI/reader.py

import threading
import time
import serial

#from re import compile as re_compile, IGNORECASE

#from buffer import RingBuffer


#GYROSCOPE_REGEX = re_compile(r"^\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*$")    # Matches a gyroscope sample line in the format: X,Y,Z
#TEMPERATURE_REGEX = re_compile(r"^\s*T\s*=\s*([-+]?\d+(?:\.\d+)?)\s*C\s*$", IGNORECASE) # Matches a temperature line in the format: T=xx.xC (case-insensitive)

class SerialReader:
    """
        Background serial reader that continuously reads data from PIB,
        parses gyroscope and temperature samples, and stores them
        in preallocated ring buffers for real-time visualization.
    """

    def __init__(self):
        self.serial_port = None # Holds the active serial (COM) port object
        self.reader_thread = None   # Background thread that reads incoming serial data
        self.stop_event = threading.Event() # Thread-safe flag used to request reader thread shutdown
        self.data_lock = threading.Lock()   # Mutex protecting shared data buffers from concurrent access

        # Preallocated ring buffers
        # I think just having one buffer for the JSON packet that then get's decoded into smaller values 
        #self.gyroscope_buffer = RingBuffer(capacity=30000)   # 50 Hz currently → 30000 samples ≈ 10 minutes of continuous data
        #self.temperature_buffer = RingBuffer(capacity=3000)    # Temperature updates much more slowly, so a smaller buffer is sufficient

        self.last_received_line = ""
        self.connection_status = "Disconnected"

    # Connection management
    def connect(self, port_name: str, baud_rate: int):
        """
            Open a serial connection to the device and start the background reader thread.

            Any existing connection is closed first. After opening the serial port,
            a dedicated daemon thread is started to continuously read incoming data
            without blocking the GUI.
        """
        self.disconnect()

        self.stop_event.clear()
        self.serial_port = serial.Serial(port=port_name, baudrate=baud_rate, timeout=0.2)

        self.connection_status = f"Connected: {port_name} @ {baud_rate}"
        self.reader_thread = threading.Thread(target=self._reader_loop, daemon=True) # initing the thread 
        self.reader_thread.start() # beginning the thread 

    def disconnect(self):
        """
            Safely stop the background serial reader thread and close the serial port.

            This method signals the reader thread to terminate, waits briefly for it
            to exit, closes the active serial connection if present, and resets all
            connection-related state to a disconnected state.
        """
        self.stop_event.set()

        if self.reader_thread and self.reader_thread.is_alive():
            self.reader_thread.join(timeout=1.0)

        self.reader_thread = None

        if self.serial_port:
            try:
                self.serial_port.close()
            except serial.SerialException:
                pass

        self.serial_port = None
        self.connection_status = "Disconnected"

    # Buffer management
    def clear_buffers(self):
        """
            Empty both buffers.
        """
        #with self.data_lock:
         #   self.gyroscope_buffer.clear()
         #   self.temperature_buffer.clear()

    # Background reader
    def _reader_loop(self):
        """
            Background thread loop that continuously reads and parses incoming serial data.

            This member function runs in a dedicated thread and repeatedly reads lines from the
            serial port while the connection is active. Each received line is timestamped
            and parsed to detect either gyroscope data (X, Y, Z samples) or temperature
            data. Parsed samples are appended to thread-safe ring buffers for later
            visualization.

            Malformed, incomplete, or unrelated lines are safely ignored. The loop exits
            cleanly when a stop request is signaled or when a serial communication error
            occurs.
        """

        while not self.stop_event.is_set():
            if not self.serial_port:
                time.sleep(0.05)
                continue

            try:
                raw_line = self.serial_port.readline()
                if not raw_line:
                    continue

                decoded_line = raw_line.decode(errors="ignore").strip()
                if not decoded_line:
                    continue

                self.last_received_line = decoded_line
                timestamp = time.monotonic()

                gyro_match = GYROSCOPE_REGEX.match(decoded_line)
                if gyro_match:
                    gyro_x = int(gyro_match.group(1))
                    gyro_y = int(gyro_match.group(2))
                    gyro_z = int(gyro_match.group(3))

                    with self.data_lock:
                        self.gyroscope_buffer.append(timestamp, gyro_x, gyro_y, gyro_z)
                    continue

                temperature_match = TEMPERATURE_REGEX.match(decoded_line)
                if temperature_match:
                    temperature_c = float(temperature_match.group(1))

                    with self.data_lock:
                        self.temperature_buffer.append(timestamp, temperature_c, 0.0, 0.0)
                    continue

            except serial.SerialException as e:
                self.connection_status = f"Serial error: {e}"
                break
            except (UnicodeDecodeError, ValueError):
                # Malformed or partial line; ignore
                continue