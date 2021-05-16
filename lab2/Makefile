# Makefile for demo programs for Lecture 1 
# Showing different sorting strategies and the
# connection between algorithms and data structures

ifeq ($(OSTYPE),WINDOWS) 
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else	
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= bubble$(EXECEXT)  stringBubble$(EXECEXT) treeSort$(EXECEXT) 

all : $(EXECUTABLES)

debug : binaryTree$(EXECEXT)


# compile with DEBUG defined to test with internal 'main'
binaryTree$(EXECEXT) : binaryTree.c
	gcc -DDEBUG -o binaryTree$(EXECEXT) binaryTree.c
		    

timeFunctions.o : timeFunctions.c timeFunctions.h
	gcc -c timeFunctions.c

binaryTree.o : binaryTree.c binaryTree.h
	gcc -c binaryTree.c

stringBubble.o : stringBubble.c timeFunctions.h
	gcc -c stringBubble.c

treeSort.o : treeSort.c binaryTree.h timeFunctions.h
	gcc -c treeSort.c

stringBubble$(EXECEXT) : stringBubble.o timeFunctions.o
	gcc -o stringBubble$(EXECEXT) stringBubble.o timeFunctions.o

treeSort$(EXECEXT) : treeSort.o binaryTree.o timeFunctions.o
	gcc -o treeSort$(EXECEXT) treeSort.o binaryTree.o timeFunctions.o


clean : 
	-rm *.o
	-rm bubble$(EXECEXT) 
	-rm stringBubble$(EXECEXT) 
	-rm treeSort$(EXECEXT)
	-rm binaryTree$(EXECEXT) 
