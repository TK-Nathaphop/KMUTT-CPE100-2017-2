# Makefile for demo programs for Lecture 11
# Hash tables
# Created by Nathaphop Sundarabhogin
# ID 60070503420
# 3 APRIL 2018

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= hashDictionary$(EXECEXT) 

all : $(EXECUTABLES)

chainedHashTable.o :	chainedHashTable.c abstractHashTable.h
	gcc -c chainedHashTable.c

timeFunctions.o: timeFunctions.c timeFunctions.h
	gcc -c timeFunctions.c

hashDictionary.o: hashDictionary.c abstractHashTable.h timeFunctions.h
	gcc -c hashDictionary.c

hashDictionary$(EXECEXT) : hashDictionary.o chainedHashTable.o timeFunctions.o
	gcc -o hashDictionary hashDictionary.o chainedHashTable.o timeFunctions.o

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
