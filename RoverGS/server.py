import socket
from mavCode import mavlink
import datetime
import argparse
import tkinter as tk
import sys

# def send_command(event):
#     print("Key pressed: " + event.char)
#     key_press = event.char
#     
#     if key_press.lower() == "w":
#         mav.

def main():
    # Create the parser object
    parser = argparse.ArgumentParser()

    # Parse the arguments
    parser.add_argument("ip", help="IP address to transmit to")
    parser.add_argument("port", help="Port number to transmit to", type=int)
    args = parser.parse_args()

    # Setup logging file
    now = datetime.datetime.now()
    logFileName = "mavLog/server_" + \
        str(now.month) + "_" + str(now.day) + "_" + \
        str(now.hour) + "_" + str(now.minute) + "_" + str(now.second) + ".log"
    logFile = open(logFileName, "w")

    # Setup the mavlink object
    mav = mavlink.MAVLink(logFile)
    
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    serverSocket.bind((args.ip, args.port))

#     while True:
    # Receive data and store in log
    while True:
        data = serverSocket.recv(1024)
        logFile.write(str(data))
    
        # Decode the data
        mavmsg = mav.decode(data)
        print(mavmsg.commandid)

    logFile.close()
    serverSocket.close()
    
if __name__ == "__main__":
    main()
