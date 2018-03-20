#!/bin/bash

MAVGEN_HOME=/home/dan/Documents/mavlink
ROVER_HOME=/home/dan/git/SoteriaRover/

rm -r $ROVER_HOME/RoverGS/mavlink.py
cd $MAVGEN_HOME
python -m pymavlink.tools.mavgen --output=$ROVER_HOME/RoverGS/mavlink.py $ROVER_HOME/SoteriaRover.xml
