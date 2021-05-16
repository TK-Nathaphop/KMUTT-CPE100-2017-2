/*
 *  FigureViewer
 *
 *  Simple graphical application to display simple geometric figures
 *
 *  Created by Nathaphop Sundarabhogin ID 60070503420
 *  25 April 2018
 */
 
import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

/**
 * Application to display figures
 */
public class FigureViewer extends JFrame implements ActionListener
    {
    private static int counter = 0; /* so we can count and label triangles */ 
    /* UI objects */
    private DrawingCanvas drawCanvas = null;
    private JButton clearButton = null;
    private JButton exitButton = null;
    private Color colors[] = {Color.RED, Color.GREEN, Color.BLUE,
                              Color.MAGENTA, Color.ORANGE};

    /**
     * Constructor creates the User Interface.
     */
    public FigureViewer()
        {
        super("Figure Viewer");
        buildUI();
        }

    /**
     * Create the visible part of the user interface. 
     */
    private void buildUI()
        {
        JPanel mainPanel = new JPanel(new BorderLayout());
        mainPanel.setBorder(new EmptyBorder(10,10,10,10));
        JPanel controlPanel = new JPanel(new FlowLayout());
        controlPanel.setBorder(new EtchedBorder());

        clearButton = new JButton("Clear");
        clearButton.addActionListener(this);
        controlPanel.add(clearButton);

        exitButton = new JButton("Exit");
        exitButton.addActionListener(this);
        controlPanel.add(exitButton);
        mainPanel.add(controlPanel, BorderLayout.NORTH);
 
        drawCanvas = new DrawingCanvas(400,400);
        drawCanvas.setBorder(new EtchedBorder());
        drawCanvas.setBackground(Color.white);
        mainPanel.add(drawCanvas, BorderLayout.CENTER);
        getContentPane().add(mainPanel, BorderLayout.CENTER);
        }

    /** 
     * This is the method required for the ActionListener 
     * interface. It handles the necessary actions when 
     * buttons are pressed.
     */
    public void actionPerformed(ActionEvent e)
        {
        Object source = e.getSource();
        if (source == exitButton)
            {
            System.exit(0);
            }
        else if (source == clearButton)
            {
            drawCanvas.clear();
            counter = 0;
            }
        }

    /** 
     * Display a triangle on the drawing canvas
     * @param  figure  Triangle to draw
     */
    public void drawTriangle(Triangle figure)
        {
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;
        Graphics2D graphics = (Graphics2D) drawCanvas.getGraphics();
        Color drawColor = colors[counter % 5];
        graphics.setPaint(drawColor);
        counter++;
        for (int i = 0; i < 3; i++)
            {  
            int pt1 = i+1;
            int pt2 = ((i+1) % 3) + 1;
            x1 = figure.getX(pt1);
            y1 = figure.getY(pt1);
            x2 = figure.getX(pt2);
            y2 = figure.getY(pt2);
            x1 *=10;    /* multiply by 10 so we can use small numbers for coords*/
            y1 *=10;
            x2 *=10;
            y2 *=10;
            graphics.drawLine(x1,y1,x2,y2);
            }
        /* label in the center */
        graphics.setColor(Color.BLACK);
        graphics.drawString(new String(" " + counter),(x1 + x2)/2,
                                        (y1 + y2)/2); 
        }

    /** 
     * Display a triangle on the drawing canvas
     * @param  figure  Rectangle to draw
     */
    public void drawRectangle(MyRectangle figure)
        {
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;
        Graphics2D graphics = (Graphics2D) drawCanvas.getGraphics();
        Color drawColor = colors[counter % 5];
        graphics.setPaint(drawColor);
        counter++;
        for (int i = 0; i < 2; i++)
            {  
            int pt1 = i+1;
            int pt2 = ((i+1) % 2) + 1;
            x1 = figure.getX(pt1);
            y1 = figure.getY(pt1);
            x2 = figure.getX(pt2);
            y2 = figure.getY(pt2);
            x1 *=10;    /* multiply by 10 so we can use small numbers for coords*/
            y1 *=10;
            x2 *=10;
            y2 *=10;
            graphics.drawLine(x1,y1,x2,y1); /* Top Line */
            graphics.drawLine(x1,y1,x1,y2); /* Left Line */
            graphics.drawLine(x1,y2,x2,y2); /* Base Line */
            graphics.drawLine(x2,y1,x2,y2); /* Right Line */
            }
        /* label in the center */
        graphics.setColor(Color.BLACK);
        graphics.drawString(new String(" " + counter),(x1 + x2)/2,
                                        (y1 + y2)/2); 
        }
    }




