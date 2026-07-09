import cmd 


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

    def do_pib(self, arg):
        """Send a command to the payload interface board."""
        print(f"Sending command to PIB: {arg}")
        # Here add the code to send the command to the PIB

    def do_help(self, arg):
        """List available commands with "help" or detailed help with "help cmd"."""
        super().do_help(arg) 



if __name__ == '__main__': # entry point for the script
    PIBShell().cmdloop()



