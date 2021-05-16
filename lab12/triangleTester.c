/**
 * triangleTester.c
 *
 * Simple main to exercise the triangle functions in triangle.c
 *
 *   Created by Sally Goldin, 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "triangle.h"

/**
 * Asks for one of the coordinates, and returns it
 * as the function value.
 * @param   prompt    String to print, telling which coordinate
 * @return  the coordinate. 
 */
int getOneCoordinate(char* prompt)
   {
   int value = 0;	   
   char inputString[32];
   printf("%s ", prompt);
   fgets(inputString,sizeof(inputString),stdin);
   sscanf(inputString,"%d",&value);
   return value;
   }


/* Main method asks for coordinates and then
 * creates new triangles. Then it calls the 
 * perimeter and area methods for the newly created
 * triangle.
 */
int main()
   {
   int bContinue = 1;
   TRIANGLE_T * pTriangle = NULL;    
   while (bContinue)
      {
      int x1, x2, x3;
      int y1, y2, y3;
      double perim, area;
      x1 = getOneCoordinate("Enter x for point 1 (negative to exit): ");
      if (x1 < 0)
         {
	 bContinue = 0;
	 }
      else
         {
	 if (pTriangle != NULL)    /* if this isn't the first round */
             free(pTriangle);
         pTriangle = (TRIANGLE_T*) calloc(1,sizeof(TRIANGLE_T));
         if (pTriangle == NULL)
             break;  /* allocation error - just get out */
	 y1 = getOneCoordinate("Enter y for point 1: ");
	 x2 = getOneCoordinate("Enter x for point 2: ");
	 y2 = getOneCoordinate("Enter y for point 2: ");
	 x3 = getOneCoordinate("Enter x for point 3: ");
	 y3 = getOneCoordinate("Enter y for point 3: ");
	 initTriangle(pTriangle,x1,y1,x2,y2,x3,y3);
	 perim = calcPerimeter(pTriangle);
	 printf("Perimeter is %.2f\n",perim);
	 area = calcArea(pTriangle);
	 printf("Area is %.2f\n\n", area);
	 }   
      }
   printf("Good bye!\n\n");
}
