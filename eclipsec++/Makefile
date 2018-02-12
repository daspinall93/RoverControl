all:main
OBJS=main.o Utils.o MotorClass.o LocomClass.o CommsContainer.o
LIBS=-lbcm2835

main: $(OBJS)
	g++ -std=c++11 $(OBJS) $(LIBS) -o  main
	
clean: 
	rm *.o main 