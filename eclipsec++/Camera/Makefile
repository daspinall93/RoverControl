LIBS=/opt/vc/lib/

all: CameraTest

CameraTest: CameraStillTest.cpp CamerModule.o pngEncoder/lodepng.o
	g++ CameraStillTest.cpp CameraModule.o pngEncoder/lodepng.o -L$(LIBS) -I/usr/local/include -lbcm2835 -lraspicam -lmmal -lmmal_core -lmmal_util -o CameraStillTest
	
CamerModule.o: CameraModule.cpp
	g++ -c CameraModule.cpp

pngEncoder/lodepng.o: pngEncoder/lodepng.cpp
	g++ -c pngEncoder/lodepng.cpp