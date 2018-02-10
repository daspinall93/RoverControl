all:main

main: main.o Utils.o MotorClass.o LocomClass.o 
	g++ main.o LocomClass.o MotorClass.o Utils.o -o main
	
clean: 
	rm *.o main 