all: SonarTest

SonarTest: SonarTest.cpp SonarModule.o ../Utils/Utils.o
	g++ $(^) -lbcm2835 -o SonarTest
	
SonarModule.o: SonarModule.cpp
	g++ -c $(^) 
	
