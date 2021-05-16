/**
 * triangle.c
 *
 * C module to create a triangle "object" with both public
 * and private functions. 
 *
 *   Created by Sally Goldin, 23 April 2013 for CPE 113 
 *
 */
#include <stdlib.h>
#include <math.h>
#include "triangle.h"


/**
 * Calculate the length of one side of the triangle.
 * This is private method used by calcPerimeter and calcArea.
 * @param  pTriangle  Pointer to the triangle for calculation 
 * @param  which    1,2 or 3, for which side
 * @return length of side, or -1 if 'which' is out of range.
 */
double calcLength(TRIANGLE_T* pTriangle, int which)
   {
   double len = -1;
   int index1 = -1;
   int index2 = -1;
   if (pTriangle != NULL)
      {
      switch (which)
         {
	 case 1:  
	      index1 = 0;
	      index2 = 1;
	      break;
	 case 2:  
	      index1 = 1;
	      index2 = 2;
	      break;
	 case 3:  
	      index1 = 0;
	      index2 = 2;
	      break;
	      
         }
      if (index1 >= 0)
         {
	 len = sqrt(
            pow(pTriangle->xcoord[index1] - pTriangle->xcoord[index2],2) +
	    pow(pTriangle->ycoord[index1] - pTriangle->ycoord[index2],2)); 
         }
      }  /* endif not null */
   return len;
   }

/** PUBLIC FUNCTIONS **/

/**
 * Initialize a triangle with the passed coordinates
 * @param     pTriangle  Pointer to the triangle to initialize 
 * @param     x1         X coord of first vertex
 * @param     y1         Y coord of first vertex
 * @param     x2         X coord of second vertex
 * @param     y2         Y coord of second vertex
 * @param     x3         X coord of third vertex
 * @param     y3         Y coord of third vertex
 * @return    1 if okay, -1 if triangle pointer is null
 */
int initTriangle(TRIANGLE_T* pTriangle, 
                  int x1, int y1, int x2, int y2, int x3, int y3)
   {
   int status = -1;
   if (pTriangle != NULL)
      {
      pTriangle->xcoord[0] = x1;
      pTriangle->xcoord[1] = x2;
      pTriangle->xcoord[2] = x3;
      pTriangle->ycoord[0] = y1;
      pTriangle->ycoord[1] = y2;
      pTriangle->ycoord[2] = y3;
      status = 1;
      }
   return status;
   }

/** 
 * Return one of the X coordinates
 * @param  pTriangle  Pointer to triangle whose information we want 
 * @param  which    1, 2, or 3 specifying which vertex we want
 * @return vertex X coordinate, or -1 if argument is not 1, 2 or 3
 *                or pTriangle is NULL
 */
int getX(TRIANGLE_T* pTriangle,int which)
    {
    int coordVal = -1;
    if ((which > 0) && (which < 4) && (pTriangle != NULL))
        coordVal = pTriangle->xcoord[which-1];  
        /* remember arrays start at o! */
    return coordVal;
    }


/** 
 * Return one of the Y coordinates
 * @param  pTriangle  Pointer to triangle whose information we want 
 * @param  which    1, 2, or 3 specifying which vertex we want
 * @return vertex Y coordinate, or -1 if argument is not 1, 2 or 3
 *                or pTriangle is NULL
 */
int getY(TRIANGLE_T* pTriangle, int which)
    {
    int coordVal = -1;
    if ((which > 0) && (which < 4) && (pTriangle != NULL))
        coordVal = pTriangle->ycoord[which-1];  
        /* remember arrays start at o! */
    return coordVal;
    }


/**
 * calculate the perimeter of this triangle
 * @param  pTriangle  Pointer to triangle whose information we want 
 * @return perimeter value or negative if triangle is null
 */
double calcPerimeter(TRIANGLE_T* pTriangle)
    {
    double perimeter = 0;
    int i = 0;
    for (i = 1; i < 3; i++)
       {
       perimeter = perimeter + calcLength(pTriangle,i);
       } 
    return perimeter;
    }

/**
 * calculate the area of a triangle
 * @param  pTriangle  Pointer to triangle whose information we want 
 * @return area value or -1 if triangle pointer is null
 */
double calcArea(TRIANGLE_T* pTriangle)
    {
        /* area formula is  
        |Ax(By - Cy) + Bx(Cy - Ay) + Cx(Ay - By)|/2
        */
    int numerator = 0;
    int result = -1;
    if (pTriangle != NULL)
       {
       numerator = pTriangle->xcoord[0] * 
	   (pTriangle->ycoord[1] - pTriangle->ycoord[2]);
       numerator += pTriangle->xcoord[1] * 
	   (pTriangle->ycoord[2] - pTriangle->ycoord[0]);
       numerator += pTriangle->xcoord[2] * 
	   (pTriangle->ycoord[0] - pTriangle->ycoord[1]);
       result = (double) abs(numerator) / 2.0;
       }
    return result;
    }

