import socket
import sys

class MySocket:
    
    def __init__(self, sock=None):
        if (sock=None):
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        else:
            self.sock = sock
            
    def MySend(self, msg):
        bytesSent = 0
        while bytesSent < sys.getsizeof(msg):
            sent = self.sock.send(msg[bytesSent:])
            if bytesSent = 0:
                raise RuntimeError("Socket connection broken")
            bytesSent = bytesSent + sent