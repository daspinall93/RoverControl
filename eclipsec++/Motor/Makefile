all:MotorTest

MotorTest: MotorTest.cpp MotorModule.o ../Utils/Utils.o
	g++ $(^) -lbcm2835 -o MotorTest
	
MotorModule.o: MotorModule.cpp
	g++ -c MotorModule.cpp