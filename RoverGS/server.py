import socket
import mavlink
import datetime
import argparse
import sys
from _socket import INADDR_ANY
import time
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
    serverSocket.bind(("0.0.0.0", args.port + 2))

#     while True:
    # Receive data and store in log
    while True:
#         data = serverSocket.recv(1024)
#         print(sys.getsizeof(data))
#         logFile.write(str(data))
        message = mav.heartbeat_encode(1, 1, 1.0, 1.0, 1.0, 1, 1, 1.1, 1)
        buf = message.pack(mav)
        serverSocket.sendto(buf, (args.ip, args.port))
        # Decode the data
#         mavmsg = mav.decode(buf)
#         print(mavmsg.motor_mode)
        
        time.sleep(1)

    logFile.close()
    serverSocket.close()
    
if __name__ == "__main__":
    main()
