import socket
import mavlink 
import tkinter as tk
import Queue
import threading 
import time
import sys
from _socket import inet_aton

class SendError(Exception):
    pass

class GStation(object):
    def __init__(self, port, ip, fileName):
        self.tcQueue = Queue.Queue()
        self.tmQueue = Queue.Queue()
        # Create the queues for Gui to interact with I/O
        self.logFile = open(fileName, 'w')
        self.mav =  mavlink.MAVLink(self.logFile)
        
        # Create the GUI and IO handler
        self.gui = Gui(self.tcQueue, self.tmQueue, self.mav)
        self.io = IOHandle(port, ip, self.mav, self.tcQueue, self.tmQueue)

        
    def startGS(self):
        # Start the IO handler and gui
        self.io.IOStart()
        self.gui.startGui()
        self.io.running = 0 # Set to stop thread
        

class Gui(object):
    def __init__(self, tcQueue, tmQueue, mav):
        self.tcQueue = tcQueue # Queue for send tc messages to the I/O thread
        self.tmQueue = tmQueue # Queue for received tm messages from I/O thread
        
        self.mav = mav # mav object for interriting messages 
        # Set up mavlink
        # Set up bindings
        self.tkMaster = tk.Tk()
        self.tkMaster.bind('<Escape>', self.endGui) #bind the escape key 
        self.tkMaster.bind('<KeyPress>', self.keyInput) #bind the keyinput function 
        self.lastKey = ''
        self.running = 0
        
    # Called to start the Gui and monitoring for events
    def startGui(self):
        self.running = 1
        self.periodicCall()
        self.tkMaster.mainloop()
        
    # take the event and pass to the tcQueue for the i/O thread to handle
    def keyInput(self, event):
#         print('Key: ' + event.char)
        keyPress = event.char
        
        buf = ''
        
        #Pass the buffer to be sent to tcQueue
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
                    mavlink.MOTOR_COMMAND_STOP, 100, 50, 1)
                buf = message.pack(self.mav)
            
            self.lastKey = keyPress.lower()

            # Pass the event to the I/O thread to interprit and produce TC
            self.tcQueue.put(buf)
            
    
    # Close the GUI
    def endGui(self, event):
        self.running = 0
#         self.tcQueue.put()
        self.tkMaster.quit() #Close the tkinter window
    
    def periodicCall(self):
        self.processIncoming()
        # Check if program shoudl still be running
#         if not self.running:
#             print('end')
#             sys.exit(1)
        self.tkMaster.after(200, self.periodicCall)         
    
    # Process any telemtry and display 
    def processIncoming(self):
        # Check if anything is in the queue
        while self.tmQueue.qsize():
            try:
                tmMsg = (self.tmQueue.get(0)).pop()
                
                # TM has been received so process
                if (tmMsg.id == mavlink.MAVLINK_MSG_ID_HEARTBEAT):
                    print('Motor mode = ' + str(tmMsg.motor_mode))
                    print('Mode_dur = ' + str(tmMsg.modeDur_ms))
#                     
            except Queue.Empty:
                print('Queue is empty')

class IOHandle(object):
    def __init__(self, port, ip, mav, tcQueue, tmQueue):
        # Create the queues for Gui to interact with I/O
        self.mav =  mav
        self.tcQueue = tcQueue
        self.tmQueue = tmQueue
        
        # Set up the I/O part  
        self.ip = ip
        self.inPort = port + 1 
        self.outPort = port
        self.outSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.inSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.outSock.bind(('', self.outPort))
        self.inSock.bind(('0.0.0.0', self.inPort))
        self.outSock.setblocking(0) # Set to non blocking so both input and output monitored
        self.inSock.setblocking(0) # Set to non blocking so both input and output monitored

        # Set up the asynchronous I/O thread
        self.running = 1 # Used to see if I/O thread is still running
        self.ioThread = threading.Thread(target=self.IOHandler)

    def IOStart(self):
        self.ioThread.daemon = True # Set as daemon mode to allow ending
        self.ioThread.start()
         
    # The thread that will handle the I/O received from rover
    def IOHandler(self):
        # Check for any commands to be sent to the rover
        
        while self.running:
            #print('IO')
            if self.tcQueue.qsize():
                # Convert message to appropriate form and send
                try:
                    msg = self.tcQueue.get_nowait()
#                     print(msg.encode('hex'))
                    sent = self.outSock.sendto(msg, (self.ip, self.outPort))
                    if sent == 0:
                        raise SendError

                except Queue.Empty:
                    pass
                except SendError:
                    print("Data not sent")                    
                    
                   
            # Check for any telemtry that has been received
            try:
                # Will produce a socket.error object if no data
                buf = str(self.inSock.recv(1024))
#                 print(buf.encode('hex'))
                # If data has been received then pass into queue
#                 mavmsg = self.mav.decode(buf)
                mavmsg = self.mav.parse_buffer(buf)
#                 print(mavmsg)
                self.tmQueue.put(mavmsg)
                  
            except socket.error:
                # print("No data received")
                pass 
             
        
            # Delay thread for 100ms
            time.sleep(0.1)

        # Close the socket once told to stop running
        self.outSock.close()
        self.inSock.close()
        
