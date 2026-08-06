Created By Kacper Paraniuk 07-09-26 


This markdown file discusses the structure of the payload interface shell (command line interface) and how to set it up 

uv — project + dependency management (replaces pip/venv juggling)
pyserial — external dependency for the serial side
cmd (Python stdlib, no install needed) — gives nice terminal commanding functionality  


HOW TO SET UP:


cd pib-cli
uv run python main.py
OR
uv run python main.py --port {Input COMX} --baud {Input Baud Rate}

Allows the user to specify the serial port and baud rate for the Arduino connection.






UV 

cmd module || read more here: https://docs.python.org/3/library/cmd.html







