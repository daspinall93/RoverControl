all:TelecTest

TelecTest: TelecTest.cpp TelecModule.o
	g++ TelecTest.cpp TelecModule.o -o TelecTest
	
TelecModule.o: TelecModule.cpp
	g++ -c TelecModule.cpp