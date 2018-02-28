LIBS=/opt/vc/lib/

all: CameraTest

CameraTest: CameraStillTest.cpp CamerModule.o
	g++ CameraStillTest.cpp CameraModule.o -L$(LIBS) -I/usr/local/include -lraspicam -lmmal -lmmal_core -lmmal_util -o CameraStillTest
	
CamerModule.o: CameraModule.cpp
	g++ -c CameraModule.cpp