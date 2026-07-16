import cmd 

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
        """Pack a single command byte (0-255) and write it to the Arduino,
        which relays it straight through to the PIB."""
        if not 0 <= code <= 255:
            raise ValueError(f"Command code out of range for 1 byte: {code}")
        payload = struct.pack("B", code)
        self.conn.write(payload)
 
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





if __name__ == '__main__': # entry point for the script
    PIBShell().cmdloop()



