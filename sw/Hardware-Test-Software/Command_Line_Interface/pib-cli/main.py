import cmd 
import serial 
import argparse



''' INTERNAL COMMANDS '''
CMD_READ_PT1  =  1
CMD_READ_PT2    =  2
CMD_READ_PT3    =  3
CMD_READ_PT4    =  4
CMD_READ_PT5    =  5
CMD_READ_PT6    =  6
CMD_READ_PT7    =  7
CMD_READ_PT8    =  8


# UART Commands for MAX31856 TC Readings

CMD_READ_TC1    =  9
CMD_READ_TC2	= 10
CMD_READ_TC3	= 11
CMD_READ_TC4	= 12
CMD_READ_TC5	= 13


# UART Commands for Solenoid Valves

CMD_OPEN_SOL1  = 14
CMD_OPEN_SOL2  =  15
CMD_OPEN_SOL3  =  17
CMD_OPEN_SOL4  =  18
CMD_OPEN_SOL5  =  19
CMD_OPEN_SOL6  = 20
CMD_OPEN_SOL7  = 21
CMD_OPEN_SOL8  = 22
CMD_OPEN_SOL9  = 23
CMD_OPEN_SOL10  = 24
CMD_OPEN_SOL11  = 25
CMD_OPEN_SOL12  = 26
CMD_OPEN_SOL13  = 27
CMD_OPEN_SOL14  = 28
CMD_OPEN_SOL15  = 29
CMD_OPEN_SOL16  = 30
CMD_OPEN_SOL17  = 31
CMD_OPEN_SOL18  = 32

CMD_CLOSE_SOL1  = 33
CMD_CLOSE_SOL2  = 34
CMD_CLOSE_SOL3   = 35
CMD_CLOSE_SOL4  = 36
CMD_CLOSE_SOL5  = 37
CMD_CLOSE_SOL6  = 38
CMD_CLOSE_SOL7  = 39
CMD_CLOSE_SOL8  = 40
CMD_CLOSE_SOL9  = 41
CMD_CLOSE_SOL10  = 42
CMD_CLOSE_SOL11  = 43
CMD_CLOSE_SOL12  = 44
CMD_CLOSE_SOL13  = 45
CMD_CLOSE_SOL14  = 46
CMD_CLOSE_SOL15  = 47
CMD_CLOSE_SOL16  = 48
CMD_CLOSE_SOL17  = 49
CMD_CLOSE_SOL18  = 50


# UART Commands for ADC7124 PC104 Stack Readings

CMD_READ_12VA_VB  = 51
CMD_READ_12VA_VA  = 52 # powers all Valves except for 4,6 (which are pwm)
CMD_READ_3V3_VB  = 53
CMD_READ_3V3_VA  = 54
CMD_READ_VBAT_VA  = 66
CMD_READ_VBAT_VB  = 67
CMD_READ_12VB_VA  = 68
CMD_READ_12VB_VB  = 69

CMD_READ_12VA_VB_CURRENT  = 70
CMD_READ_12VA_VA_CURRENT  = 71 
CMD_READ_3V3_VB_CURRENT  = 72
CMD_READ_3V3_VA_CURRENT  = 73
CMD_READ_VBAT_VA_CURRENT  = 74
CMD_READ_VBAT_VB_CURRENT  = 75
CMD_READ_12VB_VA_CURRENT  = 76
CMD_READ_12VB_VB_CURRENT  = 77

# UART Commands for FDC2214

READ_CAPACITANCE_A1  = 55
READ_CAPACITANCE_A2  = 56
READ_CATALYST_LEVEL_A1  = 57
READ_CATALYST_LEVEL_A2  = 58


# UART Command for heater

HEAT_CATALYST  = 59


# UART Commands for Pressure Regulation (PWM / PID)

REGULATE_PRESSURE_INPUT_VALUE  = 60
REGULATE_PRESSURE_2_INPUT_VALUE  = 61


# UART Commands for PPU Control (OBC -> PIB)

PPU_CURRENT_READ_1  = 62
PPU_CURRENT_READ_2  = 63
PPU_ON  = 64
PPU_OFF  = 65





class SerialLink:
    """Computer to Arduino Link """
 
    def __init__(self, port: str, baud: int = 115200, timeout: float = 1.0):
        self.port = port
        self.baud = baud
        self.timeout = timeout
        self.conn: serial.Serial | None = None
 
    def open(self):
        self.conn = serial.Serial(self.port, self.baud, timeout=self.timeout)
        # TODO: any handshake/reset-wait logic your Arduino sketch needs
        # (e.g. Arduinos often reset on serial connect - you may need a
        # short sleep or a "ready" byte handshake here)
 
    def close(self):
        if self.conn:
            self.conn.close()
 
    def send_command(self, code: int):
        if not 0 <= code <= 255:
            raise ValueError(f"Command code out of range for 1 byte: {code}")
        payload = struct.pack("B", code)
        self.conn.write(payload) # sends the bit value
 
    # TODO: read_response() - once you know what the PIB sends back for a
    # "read" command (a single byte? multiple bytes? ASCII?), define the
    # real parsing here. Likely needs its own struct format depending on
    # sensor value width/type.
 

class PIBShell(cmd.Cmd):
    intro = "Welcome to the PIB shell. Use with an arduino to command the payload interface board of MonARCH. Type help or ? to list commands.\n"
    prompt = "(pib) "

    def do_greet(self, arg):
        """Greet the user."""
        print(f"Hello, {arg}!")

    def do_exit(self, arg):
        """Exit the shell."""
        print("Exiting the PIB shell.")
        return True

    # def do_pib(self, arg): // probably not needed 
    #     """Send a command g the payload interface board."""
    #     print(f"Sending command to PIB: {arg}")
    #     # Here add the code to send the command to the PIB
    def do_open_valve(self, arg):
        """Open the valve on the payload interface board."""
        try: 
            valve = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 0 and 18.")
            return

        if(valve < 0 or valve > 18):
            print("Invalid valve number. Please enter a number between 0 and 18.")
            return
        else:
            print("Opening valve " + arg + "...")
            self.pib.send_command(CMD_OPEN_SOL1 + valve) # takes valve 1 and adds the valve number to obtain the correct command.
            
      
    def do_close_valve(self, arg):
        """Close the valve on the payload interface board."""
        try: 
            valve = int(arg)
        except ValueError:
            print("Invalid input. Please enter a number between 0 and 18.")
            return

        if(valve < 0 or valve > 18):
            print("Invalid valve number. Please enter a number between 0 and 18.")
            return
        else:
            print("Closing valve " + arg + "...")
            self.pib.send_command(CMD_CLOSE_SOL1 + valve) # takes valve 1 and adds the valve number to obtain the correct command.

    def do_run_sequence(self, arg):
        """Run a predefined sequence on the payload interface board."""
        
        print(arg)

        if(arg == "fill_accum1"):
            print("Running fill accumulator sequence 1...")
            # Here add the code to run sequence 1 on the PIB

        if(arg == "run_espray"):
            print("Running e-spray sequence...")

        # Here add the code to open the valve on the PIB

    def do_help(self, arg):
        """List available commands with "help" or detailed help with "help cmd"."""
        super().do_help(arg) 



if __name__ == "__main__":
    # TODO: argparse for --port / --baud instead of hardcoding
    link = SerialLink(port="COM3", baud=115200)
    link.open()
    try:
        PIBShell(link).cmdloop()
    finally:
        link.close()

