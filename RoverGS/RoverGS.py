import argparse
import datetime
import GroundStation as gs
import time
from GroundStation import RoverSettings

def Main():

    # Parse the arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("ip", help="IP address to transmit to")
    parser.add_argument("port", help="Port number to transmit to", type=int)
    args = parser.parse_args()
    
    now = datetime.datetime.now()
    fileName = "mavLog/client_" + \
        str(now.month) + "_" + str(now.day) + "_" + \
        str(now.hour) + "_" + str(now.minute) + "_" + str(now.second) + ".log"
        
    roverSet = RoverSettings(power_per=90, duration_ms=100)

    Ground = gs.GStation(args.port, args.ip, fileName, roverSet)
    Ground.startGS()
    
    time.sleep(1) # Allow thread to close
    
#     station = gs.GroundStation(args.ip, args.port, logFileName)
#     station.StartStation()


if __name__ == "__main__":
    Main()
