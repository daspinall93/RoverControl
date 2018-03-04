all:LocomTest

LocomTest: LocomTest.cpp LocomModule.o ../Utils/Utils.o
	g++ -std=c++11 LocomTest.cpp LocomModule.o ../Utils/Utils.o 
	
LocomModule.o: LocomModule.cpp 
	g++ -c LocomModule.cpp
	
../Utils/Utils.o:
	g++ ../Utils/Utils.o