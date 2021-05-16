/**
 * MyRectangle.java
 *
 * Simple class representing a square object. Designed 
 * to show the idea of visibility, methods, class data, etc.
 *
 *   Created by Nathaphop Sundarabhogin ID 600703420
 *      25 April 2018
 */

public class MyRectangle
    {
    /** X coordinates of three points defining the square */
    private int xcoord[] = new int[2];

    /** Y coordinates of three points defining the square */
    private int ycoord[] = new int[2];

    /**
     * Constructor creates a new square by setting the
     * values of the sets of vertext coordinates.
     * @param     x1        X coord of first vertex
     * @param     y1        Y coord of first vertex
     * @param     x2        X coord of second vertex
     * @param     y2        Y coord of second vertex
     */

    public MyRectangle(int x1, int y1, int x2, int y2)
        {
        xcoord[0] = x1;
        xcoord[1] = x2;
        ycoord[0] = y1;
        ycoord[1] = y2;
        }

    /** 
     * Return one of the X coordinates
     * @param  which    1 ot 2 specifying which vertex we want
     * @return vertex X coordinate, or -1 if argument is not 1, 2 or 3
     */
    public int getX(int which)
        {
        int coordVal = -1;
        if ((which > 0) && (which < 3))
            coordVal = xcoord[which-1];  /* remember arrays start at o! */
        return coordVal;
        }

    /** 
     * Return one of the Y coordinates
     * @param  which    1 or 2specifying which vertex we want
     * @return vertex Y coordinate, or -1 if argument is not 1, 2 or 3
     */
    public int getY(int which)
        {
        int coordVal = -1;
        if ((which > 0) && (which < 3))
            coordVal = ycoord[which-1];  /* remember arrays start at o! */
        return coordVal;
        }

    /**
     * calculate the perimeter of this rectangle
     * @return perimeter value
     */
    public double calcPerimeter()
        {
        /* perimeter formula is  (2 * |x1 - x2|) + (2 * |y1 - y2|) */
        return (2 * Math.abs(xcoord[1] - xcoord[0])) +
                (2 * Math.abs(ycoord[1] - ycoord[0]));
        }

    /**
     * calculate the area of this rectangle
     * @return area value
     */
    public double calcArea()
        {
        /* area formula is |x1 - x2| * |y1 - y2| */
        return (Math.abs(xcoord[1] - xcoord[0]) *
               Math.abs(ycoord[1] - ycoord[0]));
        }
    }
