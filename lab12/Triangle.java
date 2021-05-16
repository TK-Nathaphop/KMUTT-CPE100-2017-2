/**
 * Simple class representing a triangle object. Designed 
 * to show the idea of visibility, methods, class data, etc.
 *
 *   Created by Sally Goldin, 9 December 2011
 *   Modified 16 Dec 2011 to fix triangle area calculations
 *
 */

public class Triangle
{
   /** X coordinates of three points defining the triangle */
   private int xcoord[] = new int[3];

   /** Y coordinates of three points defining the triangle */
   private int ycoord[] = new int[3];

   /**
    * Constructor creates a new Triangle by setting the
    * values of the sets of vertext coordinates.
    * @param     x1        X coord of first vertex
    * @param     y1        Y coord of first vertex
    * @param     x2        X coord of second vertex
    * @param     y2        Y coord of second vertex
    * @param     x3        X coord of third vertex
    * @param     y3        Y coord of third vertex
    */
    public Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
    {
       xcoord[0] = x1;
       xcoord[1] = x2;
       xcoord[2] = x3;
       ycoord[0] = y1;
       ycoord[1] = y2;
       ycoord[2] = y3;
    }

    /** 
     * Return one of the X coordinates
     * @param  which    1, 2, or 3 specifying which vertex we want
     * @return vertex X coordinate, or -1 if argument is not 1, 2 or 3
     */
    public int getX(int which)
    {
        int coordVal = -1;
	if ((which > 0) && (which < 4))
            coordVal = xcoord[which-1];  /* remember arrays start at o! */
        return coordVal;
    }


    /** 
     * Return one of the Y coordinates
     * @param  which    1, 2, or 3 specifying which vertex we want
     * @return vertex Y coordinate, or -1 if argument is not 1, 2 or 3
     */
    public int getY(int which)
    {
        int coordVal = -1;
	if ((which > 0) && (which < 4))
            coordVal = ycoord[which-1];  /* remember arrays start at o! */
        return coordVal;
    }


    /**
     * calculate the perimeter of this triangle
     * @return perimeter value
     */
    public double calcPerimeter()
    {
	double perimeter = 0;
        for (int i = 1; i < 4; i++)
	    {
	    perimeter = perimeter + calcLength(i);
	    } 
        return perimeter;
    }


    /**
     * calculate the area of this triangle
     * @return area value
     */
    public double calcArea()
    {
        /* area formula is  
        |Ax(By - Cy) + Bx(Cy - Ay) + Cx(Ay - By)|/2
        */
        int numerator = xcoord[0] * (ycoord[1] - ycoord[2]);
        numerator += xcoord[1] * (ycoord[2] - ycoord[0]);
        numerator += xcoord[2] * (ycoord[0] - ycoord[1]);
        return (double) Math.abs(numerator) / 2;
    }


    /**
     * Calculate the length of one side of the triangle.
     * This is private method used by calcPerimeter and calcArea.
     * @param  which    1,2 or 3, for which side
     * @return length of side, or -1 if 'which' is out of range.
     */
    private double calcLength(int which)
    {
	double len = -1;
        int index1 = -1;
        int index2 = -1;
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
	   default:
                System.out.println("Invalid argument to calcLength!");
	   }
        if (index1 >= 0)
	   {
           len = Math.sqrt(Math.pow(xcoord[index1] - xcoord[index2],2) +
                               Math.pow(ycoord[index1] - ycoord[index2],2)); 
	   }
	return len;
    }



}
