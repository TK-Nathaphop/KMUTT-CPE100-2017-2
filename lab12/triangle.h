/*  
 *  Header file to create a triangle 'object' in C. Defines a struct
 *  type with 3 X and 3 Y coordinates.
 *
 *  Created by Sally Goldin, 23 April 2013 for CPE 113
 */

typedef struct 
{
    int xcoord[3];   /* X coordinates of three points in triangle */
    int ycoord[3];   /* Y coordinates of three points in triangle */
} TRIANGLE_T;

/* declarations of 'public' functions that can be called on a triangle */

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
		 int x1, int y1, int x2, int y2, int x3, int y3);

/** 
 * Return one of the X coordinates
 * @param  pTriangle  Pointer to triangle whose information we want 
 * @param  which    1, 2, or 3 specifying which vertex we want
 * @return vertex X coordinate, or -1 if argument is not 1, 2 or 3
 *                or pTriangle is NULL
 */
int getX(TRIANGLE_T* pTriangle,int which);

/** 
 * Return one of the Y coordinates
 * @param  pTriangle  Pointer to triangle whose information we want 
 * @param  which    1, 2, or 3 specifying which vertex we want
 * @return vertex Y coordinate, or -1 if argument is not 1, 2 or 3
 *                or pTriangle is NULL
 */
int getY(TRIANGLE_T* pTriangle, int which);

/**
 * calculate the perimeter of this triangle
 * @param  pTriangle  Pointer to triangle whose information we want 
 * @return perimeter value or negative if triangle is null
 */
double calcPerimeter(TRIANGLE_T* pTriangle);

/**
 * calculate the area of a triangle
 * @param  pTriangle  Pointer to triangle whose information we want 
 * @return area value or -1 if triangle pointer is null
 */
double calcArea(TRIANGLE_T* pTriangle);



