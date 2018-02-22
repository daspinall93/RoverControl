#!/bin/bash

MAVGEN_HOME=/home/dan/Documents/mavlink
ROVER_HOME=/home/dan/git/SoteriaRover/eclipsec++/

rm -r ../mavlink
cd $MAVGEN_HOME
python -m pymavlink.tools.mavgen --lang=C++11 --wire-protocol=2.0 --output=$ROVER_HOME/mavlink $ROVER_HOME/SoteriaRover.xml
