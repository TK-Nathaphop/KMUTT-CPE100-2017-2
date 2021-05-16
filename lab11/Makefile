# Makefile for emegereny program
# Created by Nathaphop Sundarabhogin
# ID 600708503420 28 April 2018
# Heaps & priority queues

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= emergency$(EXECEXT) 

all : $(EXECUTABLES)

emergency.o :	emergency.c abstractHeap.h
	gcc -c emergency.c

arrayHeap.o :	arrayHeap.c abstractHeap.h
	gcc -c arrayHeap.c

emergency$(EXECEXT) : emergency.o arrayHeap.o 
	gcc -o emergency$(EXECEXT) emergency.o arrayHeap.o 

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
