import cmd 
import serial 
import argparse
import struct
import time 
# UART Commands for ADC7124 PT Readings
CMD_READ_PT1 = 1   # 0x01
CMD_READ_PT2 = 2   # 0x02
CMD_READ_PT3 = 3   # 0x03
CMD_READ_PT4 = 4   # 0x04
CMD_READ_PT5 = 5   # 0x05
CMD_READ_PT6 = 6   # 0x06
CMD_READ_PT7 = 7   # 0x07
CMD_READ_PT8 = 8   # 0x08

# UART Commands for ADC7124 PC104 Stack Readings
CMD_READ_12VA_VB = 51   # 0x33
CMD_READ_12VA_VA = 52   # 0x34 (Valves)
CMD_READ_3V3_VB  = 53   # 0x35
CMD_READ_3V3_VA  = 54   # 0x36
CMD_READ_VBAT_VA = 66   # 0x42
CMD_READ_VBAT_VB = 67   # 0x43
CMD_READ_12VB_VA = 68   # 0x44
CMD_READ_12VB_VB = 69   # 0x45

CMD_READ_12VA_VB_CURRENT = 70   # 0x46
CMD_READ_12VA_VA_CURRENT = 71   # 0x47 (Valves)
CMD_READ_3V3_VB_CURRENT  = 72   # 0x48
CMD_READ_3V3_VA_CURRENT  = 73   # 0x49
CMD_READ_VBAT_VA_CURRENT = 74   # 0x4A
CMD_READ_VBAT_VB_CURRENT = 75   # 0x4B
CMD_READ_12VB_VA_CURRENT = 76   # 0x4C
CMD_READ_12VB_VB_CURRENT = 77   # 0x4D

# UART Commands for MAX31856 TC Readings
CMD_READ_TC1 = 9    # 0x09
CMD_READ_TC2 = 10   # 0x0A
CMD_READ_TC3 = 11   # 0x0B
CMD_READ_TC4 = 12   # 0x0C
CMD_READ_TC5 = 13   # 0x0D

# UART Commands for MAX31856 Cold-Junction Readings
CMD_READ_TC1_CJ = 84   # 0x54
CMD_READ_TC2_CJ = 85   # 0x55
CMD_READ_TC3_CJ = 86   # 0x56
CMD_READ_TC4_CJ = 87   # 0x57
CMD_READ_TC5_CJ = 88   # 0x58

# READ DEVICE IDs
CMD_READ_ID_PT  = 81   # 0x51
CMD_READ_ID_V   = 82   # 0x52
CMD_READ_ID_FDC = 83   # 0x53

# UART Commands for Solenoid Valves
CMD_OPEN_SOL1  = 14   # 0x0E
CMD_OPEN_SOL2  = 15   # 0x0F
CMD_OPEN_SOL3  = 17   # 0x11
CMD_OPEN_SOL4  = 18   # 0x12
CMD_OPEN_SOL5  = 19   # 0x13
CMD_OPEN_SOL6  = 20   # 0x14
CMD_OPEN_SOL7  = 21   # 0x15
CMD_OPEN_SOL8  = 22   # 0x16
CMD_OPEN_SOL9  = 23   # 0x17
CMD_OPEN_SOL10 = 24   # 0x18
CMD_OPEN_SOL11 = 25   # 0x19
CMD_OPEN_SOL12 = 26   # 0x1A
CMD_OPEN_SOL13 = 27   # 0x1B
CMD_OPEN_SOL14 = 28   # 0x1C
CMD_OPEN_SOL15 = 29   # 0x1D
CMD_OPEN_SOL16 = 30   # 0x1E
CMD_OPEN_SOL17 = 31   # 0x1F
CMD_OPEN_SOL18 = 32   # 0x20

CMD_CLOSE_SOL1  = 33   # 0x21
CMD_CLOSE_SOL2  = 34   # 0x22
CMD_CLOSE_SOL3  = 35   # 0x23
CMD_CLOSE_SOL4  = 36   # 0x24
CMD_CLOSE_SOL5  = 37   # 0x25
CMD_CLOSE_SOL6  = 38   # 0x26
CMD_CLOSE_SOL7  = 39   # 0x27
CMD_CLOSE_SOL8  = 40   # 0x28
CMD_CLOSE_SOL9  = 41   # 0x29
CMD_CLOSE_SOL10 = 42   # 0x2A
CMD_CLOSE_SOL11 = 43   # 0x2B
CMD_CLOSE_SOL12 = 44   # 0x2C
CMD_CLOSE_SOL13 = 45   # 0x2D
CMD_CLOSE_SOL14 = 46   # 0x2E
CMD_CLOSE_SOL15 = 47   # 0x2F
CMD_CLOSE_SOL16 = 48   # 0x30
CMD_CLOSE_SOL17 = 49   # 0x31
CMD_CLOSE_SOL18 = 50   # 0x32

CMD_READ_VALVE_STATE_1  = 91    # 0x5B
CMD_READ_VALVE_STATE_2  = 92    # 0x5C
CMD_READ_VALVE_STATE_3  = 93    # 0x5D
CMD_READ_VALVE_STATE_4  = 94    # 0x5E
CMD_READ_VALVE_STATE_5  = 95    # 0x5F
CMD_READ_VALVE_STATE_6  = 96    # 0x60
CMD_READ_VALVE_STATE_7  = 97    # 0x61
CMD_READ_VALVE_STATE_8  = 98    # 0x62
CMD_READ_VALVE_STATE_9  = 99    # 0x63
CMD_READ_VALVE_STATE_10 = 100   # 0x64
CMD_READ_VALVE_STATE_11 = 101   # 0x65
CMD_READ_VALVE_STATE_12 = 102   # 0x66
CMD_READ_VALVE_STATE_13 = 103   # 0x67
CMD_READ_VALVE_STATE_14 = 104   # 0x68
CMD_READ_VALVE_STATE_15 = 105   # 0x69
CMD_READ_VALVE_STATE_16 = 106   # 0x6A
CMD_READ_VALVE_STATE_17 = 107   # 0x6B
CMD_READ_VALVE_STATE_18 = 108   # 0x6C

# UART Commands for FDC2214
READ_CAPACITANCE_A1      = 55   # 0x37
READ_CAPACITANCE_A2      = 56   # 0x38
READ_PROPELLANT_LEVEL_A1 = 57   # 0x39
READ_PROPELLANT_LEVEL_A2 = 58   # 0x3A

# UART Command for heater
CMD_HEAT_CATALYST          = 59   # 0x3B
CMD_MANUAL_HEATER_TURN_ON  = 89   # 0x59
CMD_MANUAL_HEATER_TURN_OFF = 90   # 0x5A

# UART Commands for Pressure Regulation (PWM / PID)
REGULATE_PRESSURE_F_INPUT_VALUE     = 112   # 0x70
REGULATE_PRESSURE_TWO_F_INPUT_VALUE = 113   # 0x71

REGULATE_DC_PRESSURE_INPUT_VALUE         = 60   # 0x3C
CMD_REGULATE_DC_PRESSURE_TWO_INPUT_VALUE = 61   # 0x3D

REGULATE_PRESSURE_1_STOP = 109   # 0x6D
REGULATE_PRESSURE_2_STOP = 110   # 0x6E

# UART Commands for PPU Control (OBC -> PIB)
PPU_CURRENT_READ_1 = 62   # 0x3E
PPU_CURRENT_READ_2 = 63   # 0x3F
PPU_ON             = 64   # 0x40
PPU_OFF            = 65   # 0x41

CMD_READ_DATA = 111   # 0x6F

# CMDS (PIB -> PPU)
PIB_PPU_ON             = 0   # 0x00
PIB_PPU_OFF            = 1   # 0x01
PIB_PPU_CURRENT_READ_1 = 2   # 0x02
PIB_PPU_CURRENT_READ_2 = 3   # 0x03

# Miscellaneous
CMD_TOGGLE_RED_LED   = 78   # 0x4E
CMD_TOGGLE_GREEN_LED = 79   # 0x4F
CMD_TOGGLE_AMBER_LED = 80   # 0x50

# Safety Commands
CMD_SAFETY_BEGIN          = 114   # 0x72
CMD_SAFETY_STOP_HEAT_TEST = 114   # 0x72
CMD_SAFETY_STOP_READ_DATA = 115   # 0x73

class SerialLink: # https://docs.python.org/3/tutorial/classes.html 

# "When a class defines an __init__() method, class instantiation automatically invokes __init__() for the newly created class instance. So in this example, a new, initialized instance can be obtained by"

    """Computer to Arduino Link """
 
    def __init__(self, port: str, baud: int = 115200, timeout: float = 4.0):
        self.port = port
        self.baud = baud
        self.timeout = timeout
        self.conn: serial.Serial | None = None # written like this so that the type checker knows that self.conn is either a serial.Serial object or None.
 
    def open(self):
        self.conn = serial.Serial(self.port, self.baud, timeout=self.timeout) # https://pyserial.readthedocs.io/en/latest/pyserial_api.html << creating the serial connection and assigining it to the self.conn variable.
  
 
    def close(self):
        if self.conn:
            self.conn.close()
 
    def send_command(self, code: int, arg: int = 0x00):
        if not 0 <= code <= 255:
            raise ValueError(f"Command code out of range for 1 byte: {code}")
        if not 0 <= arg <= 255:
            raise ValueError(f"Argument out of range: {arg}")
        payload = struct.pack("BB", code, arg)  # always 2 bytes // 
        self.conn.write(payload) # sends the bit value // 

    def read_response(self, terminator: bytes = b'\n') -> str:
        """Read a line of text response from the device."""
        self.conn.reset_input_buffer()  # discard any stale responses
        time.sleep(0.05)          # let STM32 start responding
        
        if not self.conn:
            return ""

        line = self.conn.readline()  # blocks until terminator or timeout
        return line.decode('utf-8', errors='replace').strip()

 

class PIBShell(cmd.Cmd): # https://realpython.com/ref/stdlib/cmd/ 
    intro = "Welcome to the PIB shell. Use with an arduino to command the payload interface board of MonARCH. Type help or ? to list commands.\n"
    prompt = "(pib) "

    def __init__(self, pib: SerialLink):
        super().__init__()
        self.pib = pib

    def do_greet(self, arg):
        """Greet the user."""
        print(f"Hello, {arg}!")

    def do_exit(self, arg):
        """Exit the shell."""
        print("Exiting the PIB shell.")
        return True

    def do_toggle_red_led(self, arg):
        """Toggling the RED LED on the payload interface board."""
        print("Toggling LED...")
        self.pib.send_command(CMD_TOGGLE_RED_LED)  

    def do_read_data(self, arg):
        print("Reading JSON Data")
        self.pib.send_command(CMD_READ_DATA)
        
    def do_stop_read(self, arg):
        print("Reading JSON Data")
        self.pib.send_command(CMD_SAFETY_STOP_READ_DATA)

    

    def do_stop_heat_e(self, arg):
            """Toggling the RED LED on the payload interface board."""
            print("Toggling OFF Heat Experiment...")
            self.pib.send_command(CMD_SAFETY_STOP_HEAT_TEST)  

    def do_stop_pwm_1(self,arg):
        self.pib.send_command(REGULATE_PRESSURE_1_STOP)

    def do_stop_pwm_1(self,arg):
        self.pib.send_command(REGULATE_PRESSURE_2_STOP)

    def do_run_sequence(self, args):
        """Run a predefined sequence on the payload interface board."""
        
        print(args)

        if(args == "fill_accum1"):
            print("Running fill accumulator sequence 1...")
            # Here add the code to run sequence 1 on the PIB

        if(args == "run_espray"):
            print("Running e-spray sequence...")

        if(args=="run_heat_test"):
            print("Running Heat Test")
            self.pib.send_command(CMD_HEAT_CATALYST)



    def do_toggle_green_led(self, arg):
        """Toggling the GREEN LED on the payload interface board."""
        print("Toggling LED...")
        self.pib.send_command(CMD_TOGGLE_GREEN_LED)

    def do_toggle_amber_led(self, arg):
        """Toggling the GREEN LED on the payload interface board."""
        print("Toggling LED...")
        self.pib.send_command(CMD_TOGGLE_AMBER_LED)

    def do_open_valve(self, arg):
        """Open the valve on the payload interface board."""
        try: 
            valve = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 18.")
            return

        if(valve < 1 or valve > 18):
            print("Invalid valve number. Please enter a number between 1 and 18.")
            return
        else:
            print("Opening valve " + arg + "...")
            self.pib.send_command(CMD_OPEN_SOL1 + (valve-1)) # takes valve 1 and adds the valve number to obtain the correct command.
            
      
    def do_close_valve(self, arg):
        """Close the valve on the payload interface board."""
        try: 
            valve = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 18.")
            return

        if(valve < 1 or valve > 18):
            print("Invalid valve number. Please enter a number between 1 and 18.")
            return
        else:
            print("Closing valve " + arg + "...")
            self.pib.send_command(CMD_CLOSE_SOL1 + (valve-1)) # takes valve 1 and adds the valve number to obtain the correct command.
    def do_read_cj_temp(self,arg):
        """Read the cold junction temperature from the payload interface board."""
        try: 
            sensor = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 5.")
            return

        if(sensor < 1 or sensor > 5):
            print("Invalid sensor number. Please enter a number between 1 and 5.")
            return
        else:
            print("Reading cold junction temperature from sensor " + arg + "...")
            self.pib.send_command(CMD_READ_TC1_CJ + (sensor - 1)) # takes sensor 1 and adds the sensor number - 1 to obtain the correct command.
            response = self.pib.read_response()
            if response:
                print(f"PIB says: {response}")

    def do_read_temp(self, arg):
        """Read the temperature from the payload interface board."""
        try: 
            sensor = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 5.")
            return

        if(sensor < 1 or sensor > 5):
            print("Invalid sensor number. Please enter a number between 1 and 5.")
            return
        else:
            print("Reading temperature from sensor " + arg + "...")
            self.pib.send_command(CMD_READ_TC1 + (sensor - 1)) # takes sensor 1 and adds the sensor number - 1 to obtain the correct command.
            response = self.pib.read_response()
            if response:
                print(f"PIB says: {response}" + " Celcius degrees")

    def do_read_pressure(self, arg):
        """Read the pressure from the payload interface board."""
        try: 
            sensor = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 8.")
            return

        if(sensor < 1 or sensor > 8):
            print("Invalid sensor number. Please enter a number between 1 and 8.")
            return
        else:
            print("Reading pressure from sensor " + arg + "...")
            self.pib.send_command(CMD_READ_PT1 + (sensor - 1)) # takes sensor 1 and adds the sensor number - 1 to obtain the correct command.
            response = self.pib.read_response()
            if response:
                print(f"PIB says: {response}" + " Pa") 

    def do_read_capacitancez(self, arg):
        """Read the capacitance chip from the payload interface board."""
        print("Reading pressure from sensor " + arg + "...")

        try: 
            sensor = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 2.")
            return 
        
        self.pib.send_command(CMD_READ_PT1 + (sensor - 1)) # takes sensor 1 and adds the sensor number - 1 to obtain the correct command.
        response = self.pib.read_response()
        if response:
            print(f"PIB says: {response}" + " Pa") 

    def do_read_level(self, arg):
        """Read the level of the FAM142 propellant from the payload interface board."""
        print("Reading propellant level from sensor " + arg + "...")


    def do_read_valve_state(self, arg):
        """Read the valve state on the payload interface board."""
        try: 
            valve = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 18.")
            return

        if(valve < 1 or valve > 18):
            print("Invalid valve number. Please enter a number between 1 and 18.")
            return
        else:
            print("Reading valve " + arg + "...")
            self.pib.send_command(CMD_READ_VALVE_STATE_1 + (valve - 1)) # takes valve 1 and adds the valve number - 1 to obtain the correct command.
            response = self.pib.read_response()
            if response:
                print(f"PIB says: {response}")

    def do_read_3v3(self, arg):
        """Read 3v3 Bus of the PIB"""
        try: 
            value = int(arg)

        except ValueError:
            print("Invalid input. Please enter a number between 1 and 2.")
            return

        if(value <1 or value > 2):
            print("Invalid voltage divider number. Please enter either 1 or 2.")
            return
        else:
            print("Reading voltage divider " + arg + "...")
            self.pib.send_command(CMD_READ_3V3_VB + (value - 1)) 
            response = self.pib.read_response()
            if response:
                print(f"PIB says: {response}" + " Volts") 

    def do_read_VBAT(self,arg):
        """Read VBAT Bus of the PIB"""
        try: 
            value = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 2.")
            return
        if(value <1 or value > 2):
            print("Invalid voltage divider number. Please enter either 1 or 2.")
            return
        else:
            print("Reading voltage divider " + arg + "...")
            self.pib.send_command(CMD_READ_VBAT_VA + (value - 1)) 
            response = self.pib.read_response()
            if response:
                print(f"PIB says: {response}" + " Volts") 

    def do_read_12VB(self, arg):
        """Read 12V Bus of the PIB"""
        try: 
            value = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 2.")
            return
        if(value <1 or value > 2):
            print("Invalid voltage divider number. Please enter either 1 or 2.")
            return
        else:
            print("Reading voltage divider " + arg + "...")
            self.pib.send_command(CMD_READ_12VB_VA + (value - 1)) 
            response = self.pib.read_response()
            if response:
                print(f"PIB says: {response}" + " Volts") 
    def do_read_12VA(self, arg):
        """Read 12V Bus of the PIB"""
        try: 
            value = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 2.")
            return
        if(value <1 or value > 2):
            print("Invalid voltage divider number. Please enter either 1 or 2.")
            return
        else:
            print("Reading voltage divider " + arg + "...")
            self.pib.send_command(CMD_READ_12VA_VB + (value - 1)) 
            response = self.pib.read_response()
            if response:
                print(f"PIB says: {response}" + " Volts") 


    def do_read_3v3_current(self, arg):
        """Read 3v3 current of the PIB"""
        try: 
            value = int(arg)

        except ValueError:
            print("Invalid input. Please enter a number between 1 and 2.")
            return

        if(value <1 or value > 2):
            print("Invalid voltage divider number. Please enter either 1 or 2.")
            return
        else:
            print("Reading voltage divider current" + arg + "...")
            self.pib.send_command(CMD_READ_3V3_VB_CURRENT + (value - 1)) 
            response = self.pib.read_response()
            if response:
                print(f"PIB says: {response}" + " Milli-Amps") 

    def do_read_VBAT_current(self,arg):
        """Read VBAT Currnet of the PIB"""
        try: 
            value = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 2.")
            return
        if(value <1 or value > 2):
            print("Invalid voltage divider number. Please enter either 1 or 2.")
            return
        else:
            print("Reading voltage divider current " + arg + "...")
            self.pib.send_command(CMD_READ_VBAT_VA_CURRENT + (value - 1)) 
            response = self.pib.read_response()
            if response:
                print(f"PIB says: {response}" + " Milli-Amps") 

    def do_read_12VB(self, arg):
        """Read 12V Current of the PIB"""
        try: 
            value = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 2.")
            return
        if(value <1 or value > 2):
            print("Invalid voltage divider number. Please enter either 1 or 2.")
            return
        else:
            print("Reading voltage divider current" + arg + "...")
            self.pib.send_command(CMD_READ_12VB_VA_CURRENT + (value - 1)) 
            response = self.pib.read_response()
            if response:
                print(f"PIB says: {response}" + " Milli-Amps") 
    def do_read_12VA(self, arg):
        """Read 12V Current of the PIB"""
        try: 
            value = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 2.")
            return
        if(value <1 or value > 2):
            print("Invalid voltage divider number. Please enter either 1 or 2.")
            return
        else:
            print("Reading voltage divider current" + arg + "...")
            self.pib.send_command(CMD_READ_12VA_VB_CURRENT + (value - 1)) 
            response = self.pib.read_response()
            if response:
                print(f"PIB says: {response}" + " Milli-Amps") 


    def do_read_id(self, arg):
        """Read Device ID"""
        if(arg == "PT"):
            print("Reading Pressure AD7124 Device ID")

            self.pib.send_command(CMD_READ_ID_PT)
            response = self.pib.read_response()
            if response:
                print(f"PIB Says: {response}")
        
        elif(arg == "V"):
            print("Reading Voltage AD7124 Device ID")

            self.pib.send_command(CMD_READ_ID_V)
            response = self.pib.read_response()
            if response:
                print(f"PIB Says: {response}")

        elif(arg == "FDC"):
            print("Reading Capacitance Chip Device ID")

            self.pib.send_command(CMD_READ_ID_FDC)
            response = self.pib.read_response()
            if response:
                print(f"PIB Says: {response}")




        # parameterized command
    def do_set_duty_1(self, args):
        '''Set the duty cycle for the pressure regulation on the payload interface board.'''

        try: 
            duty = int(args)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 2.")
            return 

        if(duty < 0 or duty > 100):
            print("Invalid duty cycle. Please enter a number between 0 and 100.")
            return

        self.pib.send_command(REGULATE_DC_PRESSURE_INPUT_VALUE, duty)


    def do_set_duty_2(self, args):
        '''Set the duty cycle for the pressure regulation on the payload interface board.'''

        try: 
            duty = int(args)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 2.")
            return 

        if(duty < 0 or duty > 100):
            print("Invalid duty cycle. Please enter a number between 0 and 100.")
            return

        self.pib.send_command(CMD_REGULATE_DC_PRESSURE_TWO_INPUT_VALUE, duty)

    def do_set_f_1(self, args):
        '''Set the duty cycle for the pressure regulation on the payload interface board.'''

        try: 
            f = int(args)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 2.")
            return 

        if(f < 0 or f > 100):
            print("Invalid frequency. Please enter a number between 0 and 100.")
            return

        self.pib.send_command(REGULATE_PRESSURE_F_INPUT_VALUE, f)


    def do_set_f_2(self, args):
        '''Set the frequency for the pressure regulation on the payload interface board.'''

        try: 
            f = int(args)
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 2.")
            return 

        if(f < 0 or f > 100):
            print("Invalid frequency. Please enter a number between 0 and 100.")
            return

        self.pib.send_command(REGULATE_PRESSURE_TWO_F_INPUT_VALUE, f)



    def do_help(self, arg):
        """List available commands with "help" or detailed help with "help cmd"."""
        super().do_help(arg) 


def parse_args(): # Parse command-line arguments when running the script directly. This allows the user to specify the serial port and baud rate for the Arduino connection.
    parser = argparse.ArgumentParser(description="PIB command-line interface")
    parser.add_argument(
        "--port",
        default="COM12",
        help="Serial port the Arduino is connected to (default: %(default)s)",
    )
    parser.add_argument(
        "--baud",
        type=int,
        default=115200,
        help="Baud rate for the serial link (default: %(default)s)",
    )
    return parser.parse_args()


if __name__ == "__main__": # https://realpython.com/ref/stdlib/cmd/ 
    args = parse_args()
    link = SerialLink(port=args.port, baud=args.baud) # instantiate the class. 
    link.open()
    try:
        PIBShell(link).cmdloop() # https://docs.python.org/3/library/cmd.html cmd loop 
    finally:
        link.close()