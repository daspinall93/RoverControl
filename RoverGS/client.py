import socket
from mavCode import mavlink 
import argparse
import datetime
import tkinter as tk
 
def key_input(event):
    print("Key: " + event.char)
    key_press = event.char
     
    if key_press.lower() == "w":
         mav.motor_command_send(mavlink.MOTOR_COMMAND_STRAIGHT_BACKWARD, 100, 50, 1)
         
def main():


    
    # Create the parser object
    parser = argparse.ArgumentParser()

    # Parse the arguments
    parser.add_argument("ip", help="IP address to transmit to")
    parser.add_argument("port", help="Port number to transmit to", type=int)
    args = parser.parse_args()
    
    # Open the file for logging 
        # Setup logging file
    now = datetime.datetime.now()
    logFileName = "mavLog/client_" + \
        str(now.month) + "_" + str(now.day) + "_" + \
        str(now.hour) + "_" + str(now.minute) + "_" + str(now.second) + ".log"
    logFile = open(logFileName, "w")
    
    mavFile = open("tmp/" + str(args.port) + ".log", "w")
    
    # Create the mavlink object 
    global clientSocket 
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    mavFile = clientSocket.makefile(mode='w')
    global mav 
    mav = mavlink.MAVLink(mavFile)  # create a mavlink object

    # Socket setup

    

    command = tk.Tk()
    command.bind('<KeyPress>', key_input)
    command.mainloop()
    
#     message = mav.motor_command_encode(
#         mavlink.MOTOR_COMMAND_STRAIGHT_BACKWARD, 100, 50, 1)
#     global buf = message.pack(mav)
      
#     # Write to the log
#     logFile.write(str(buf))

    # Send using UDP

#     clientSocket.connect("/tmp/" + str(args.port))
#     mav.motor_command_send(mavlink.MOTOR_COMMAND_STRAIGHT_BACKWARD, 100, 50, 1)
#     sent = clientSocket.sendto(buf, (args.ip, args.ip))
    
    #clientSocket.close()

if __name__ == "__main__":
    main()
