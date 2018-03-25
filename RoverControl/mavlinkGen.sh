#!/bin/bash

MAVGEN_HOME=/home/dan/Documents/mavlink
ROVER_HOME=/home/dan/Documents/workspace/git/SoteriaRover

rm -r $ROVER_HOME/mavlink
cd $MAVGEN_HOME
python pymavlink/tools/mavgen.py --lang=C --wire-protocol=2.0 --output=$ROVER_HOME/RoverControl/include/mavlink $ROVER_HOME/SoteriaRover.xml
