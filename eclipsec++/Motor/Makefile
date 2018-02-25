all:MotorTest

MotorTest: MotorTest.cpp MotorModule.o 
	g++ $(^) -o MotorTest
MotorModule.o: MotorModule.cpp
	g++ -c MotorModule.cpp