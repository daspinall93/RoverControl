import socket
from mavCode import mavlink 
import tkinter as tk

class SendError(Exception):
    pass

class GroundStation(object):
    def __init__(self, ip, port, fileName):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.ip = ip
        self.port = port
        self.logFile = open(fileName, 'w')
        self.mav = mavlink.MAVLink(self.logFile)
        self.command = tk.Tk()
        self.lastKey = ''
        
        # Set up bindings
        self.command.bind('<Escape>', self.CloseStation) #bind the escape key 
        self.command.bind('<KeyPress>', self.KeyInput) #bind the keyinput function
#         self.command.bind('<KeyRelease-Return')
            
    def StartStation(self):
        self.command.mainloop()
        
    def KeyInput(self, event):
#         print('Key: ' + event.char)
        keyPress = event.char
        
        buf = ''
        
        #if key is held down or pressed multiple times don't send multiple commands
        if keyPress.lower() != self.lastKey:
            # Determine what message is to be sent
            if keyPress.lower() == 'w':
                message = self.mav.motor_command_encode(
                    mavlink.MOTOR_COMMAND_STRAIGHT_FORWARD, 100, 50, 1)
                buf = message.pack(self.mav)
        
            elif keyPress.lower() == 's':
                message = self.mav.motor_command_encode(
                    mavlink.MOTOR_COMMAND_STRAIGHT_BACKWARD, 100, 50, 1)
                buf = message.pack(self.mav)
                
            elif keyPress.lower() == 'd':
                message = self.mav.motor_command_encode(
                    mavlink.MOTOR_COMMAND_TURN_RIGHT, 100, 50, 1)
                buf = message.pack(self.mav)
            
            elif keyPress.lower() == 'a':
                message = self.mav.motor_command_encode(
                    mavlink.MOTOR_COMMAND_TURN_LEFT, 100, 50, 1)
                buf = message.pack(self.mav)
                
            elif keyPress.lower() == 'e':
                message = self.mav.motor_command_encode(
                    mavlink.MOTOR_COMMAND_TURN_LEFT, 100, 50, 1)
                buf = message.pack(self.mav)
                
            self.lastKey = keyPress.lower()

            
    #     else if key_press.lower() == 'w'
        # Send the message if buffer is filled
        if buf:
            try:
                
                sent = self.sock.sendto(buf, (self.ip, self.port))
                if sent == 0:
                    raise SendError
                else:
                    self.logFile.write(buf + '\n')
            except SendError:
                print ('Data not sent')

    def CloseStation(self, event):
        self.command.quit() #Close the tkinter window
        self.sock.close() #Close the socket
        self.logFile.close() #Close the log file
