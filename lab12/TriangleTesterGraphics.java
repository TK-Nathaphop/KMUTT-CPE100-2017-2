/**
 * Extension of TriangleTester that displays triangles, too.
 *
 *   Created by Sally Goldin, 23 April 2013 for CPE 113
 *
 */

import java.io.*;
import java.util.*;

public class TriangleTesterGraphics extends TriangleTester
{
   /* Main method first creates the viewer. Then it
    * asks for coordinates, creates new triangles, and displays them. 
    * Then prints the perimetr and area as well.
    */
   public static void main(String arguments[])
      {
      boolean bContinue = true;
      FigureViewer viewer = new FigureViewer();
      viewer.pack();
      viewer.show();
 
      while (bContinue)
         {
	 int x1, x2, x3;
	 int y1, y2, y3;
	 x1 = getOneCoordinate("Enter x for point 1 (negative to exit): ");
	 if (x1 < 0)
            {
	    bContinue = false;
	    }
	 else
            {
	    y1 = getOneCoordinate("Enter y for point 1: ");
	    x2 = getOneCoordinate("Enter x for point 2: ");
	    y2 = getOneCoordinate("Enter y for point 2: ");
	    x3 = getOneCoordinate("Enter x for point 3: ");
	    y3 = getOneCoordinate("Enter y for point 3: ");
	    Triangle triangle = new Triangle(x1,y1,x2,y2,x3,y3);
	    viewer.drawTriangle(triangle);
	    double perim = triangle.calcPerimeter();
	    System.out.println("Perimeter is " + perim);
	    double area = triangle.calcArea();
	    System.out.println("Area is " + area + "\n\n");
	    }
	 }   
      }

}
