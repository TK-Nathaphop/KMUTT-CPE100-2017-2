#    This 'Makefile' is intended to build program Simple Facebook.
#
#    Created by Nathaphop Sundarabhogin(KLA) ID : 3420
#        20 April 2017
#

EXECUTABLES=readData

all : $(EXECUTABLES)

readData.o : readData.c simpleFacebook.h manageData.h validate.h userInterface.h
	gcc -c readData.c

controlHashTable.o : controlHashTable.c simpleFacebook.h abstractTree.h
	gcc -c controlHashTable.c

controlBinaryTree.o : controlBinaryTree.c simpleFacebook.h abstractStatus.h abstractGraph.h
	gcc -c controlBinaryTree.c

controlStatus.o : controlStatus.c simpleFacebook.h
	gcc -c controlStatus.c

controlFriend.o : controlFriend.c simpleFacebook.h
	gcc -c controlFriend.c

validate.o : validate.c simpleFacebook.h
	gcc -c validate.c

manageData.o : manageData.c simpleFacebook.h abstractGraph.h abstractStatus.h abstractTree.h abstractHash.h validate.h
	gcc -c manageData.c

userInterface.o : userInterface.c simpleFacebook.h validate.h
	gcc -c userInterface.c

dumpFile.o : dumpFile.c simpleFacebook.h manageData.h validate.h userInterface.h
	gcc -c dumpFile.c

readData : readData.o controlHashTable.o controlBinaryTree.o controlFriend.o controlStatus.o validate.o manageData.o userInterface.o dumpFile.o
	gcc -o readData readData.o controlHashTable.o controlBinaryTree.o controlStatus.o controlFriend.o validate.o manageData.o userInterface.o dumpFile.o

clean : 
	-rm *.o
	-rm simpleFacebook