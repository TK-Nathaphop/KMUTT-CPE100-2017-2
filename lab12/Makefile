# Makefile for demo programs (Java) for Lecture 12 
# Builds three Java applications, TriangleTester, SimpleVectorApp, and NetworkApp, plus a C program analogous to TriangleTester

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif


EXECUTABLES= RectangleTester$(EXECEXT) RectangleTester.class triangleTester$(EXECEXT) TriangleTester.class SimpleVectorApp.class NetworkApp.class TriangleTesterGraphics.class RectangleTesterGraphics.class


all : $(EXECUTABLES)

lab : triangleTester$(EXECEXT) TriangleTester.class TriangleTesterGraphics.class

labnaja : RectangleTester$(EXECEXT) RectangleTester.class RectangleTesterGraphics.class

RectangleTester$(EXECEXT) : RectangleTester.java MyRectangle.class
	javac RectangleTester.java

triangle.o :	triangle.c triangle.h
	gcc -c triangle.c

triangleTester.o :	triangleTester.c triangle.h
	gcc -c triangleTester.c

triangleTester$(EXECEXT) : triangleTester.o triangle.o
	gcc -o triangleTester$(EXECEXT) triangleTester.o triangle.o -lm

Triangle.class	: Triangle.java
	javac Triangle.java

TriangleTester.class : TriangleTester.java Triangle.class
	javac TriangleTester.java

FigureViewer.class : FigureViewer.java DrawingCanvas.class 
	javac FigureViewer.java
 
RectangleTesterGraphics.class : RectangleTester.java MyRectangle.class FigureViewer.class RectangleTesterGraphics.java
	javac RectangleTesterGraphics.java

TriangleTesterGraphics.class : TriangleTester.java Triangle.class FigureViewer.class TriangleTesterGraphics.java
	javac TriangleTesterGraphics.java


Point.class : Point.java
	javac Point.java

GeoFeature.class : GeoFeature.java Point.class
	javac GeoFeature.java


DragonVectorReader.class : DragonVectorReader.java GeoFeature.class
	javac DragonVectorReader.java


DrawingCanvas.class  : DrawingCanvas.java
	javac DrawingCanvas.java

SimpleVectorApp.class : SimpleVectorApp.java Point.class \
			GeoFeature.class DragonVectorReader.class \
			DrawingCanvas.class
	javac SimpleVectorApp.java

NetworkApp.class : NetworkApp.java
	javac NetworkApp.java


clean : 
	-rm *.class
	-rm *.o
	-rm triangleTester$(EXECEXT)
