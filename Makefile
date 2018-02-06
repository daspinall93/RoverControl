LIBS=-lbcm2835 -lm
#OBJS=rvLocal/rvLocal.o rvLocal/rvIMU.o  rvLocom/rvLocom.o rvLocom/rvMot.o  rvCam/rvCam.o rvCom/rvCom.o
OBJS = rvLocom.o rvUtils.o
all: rvMain
#
rvMain: rvMain.c librv.a
	gcc -Wall -Werror $^ $(LIBS) -o rvMain

librv.a: $(OBJS)
	ar -rcv $@ $(OBJS) 
	
clean:
	rm -f rvMain *.o *.a
