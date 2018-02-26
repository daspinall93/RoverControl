all: InertTest

InertTest: InertTest.cpp InertModule.o ../Utils/Utils.o I2Cdev.o
	g++ $(^) -lbcm2835 -o InertTest

InertModule.o: InertModule.cpp
	g++ -c $(^)
	
I2Cdev.o: I2Cdev.cpp
	g++ -c $(^)
	
../Utils/Utils.o: ../Utils/Utils.cpp
	g++ -c $(^)
