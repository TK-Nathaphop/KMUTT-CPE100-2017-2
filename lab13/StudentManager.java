/******************************************************************************
 *
 * StudentManager.java
 * 
 *  Simple class to represent a student in a registration system.
 *  This problem loob ask for add data, show all names and loop find student ID.
 *
 *  Created by Nathaphop ID 60070504320.
 *
 *****************************************************************************/

import java.io.*;
import java.util.*;

public class StudentManager extends Student
    {    
    protected static ArrayList<Student> allStudents = new ArrayList<Student>();
    
    /* Loop get new student into array list */
    public static void getStudents()
        {
        Student newStudent;
        String ask = "Dummy";
        boolean bContinue = true;
        allStudents.clear();
        while (bContinue)
            {
            newStudent = new Student();
            allStudents.add(newStudent);
            System.out.println();
            /* Loop ask user add more or not */
            while(!(ask.compareTo("Y") == 0) && !(ask.compareTo("N") == 0))
                {
                ask = IOUtils.getString("Continue? (Y/N)");
                if (ask.compareTo("Y") == 0)
                    bContinue = true;
                else if (ask.compareTo("N") == 0)
                    bContinue = false;
                else
                    System.out.println("Wrong input!");
                }
            ask = "Dummy";
            }
        }

    /* Print all student list name */
    public static void listStudents()
        {
        Student nextStudent;
        int i = 0;
        for(i = 0; i < allStudents.size(); i++)
            {
            nextStudent = allStudents.get(i);
            System.out.println(nextStudent.getStudentName());
            }
        }

    /* Loop ask ID, find and print information about student */
    public static void findStudents()
        {
        Student findStudent;
        int input = 1;
        int i = 0;
        /* Loop ask user for find student */
        while (input != 0)
            {
            input = IOUtils.getInteger("Student ID (0 for end): ");
            /* If 'input' less than 0, it mean user didn't number */
            if (input < 0)
                continue;
            /* If 'input' equal 0, it mean user want to end */
            else if (input == 0)
                break;
            /* Loop find student ID in array */
            for(i = 0; i < allStudents.size(); i++)
                {
                findStudent = allStudents.get(i);
                if(findStudent.getStudentId() == input)
                    {
                    findStudent.display();
                    System.out.println("Average Grade:" 
                                        + findStudent.computeAvgGrade());
                    break;
                    }
                else if (i+1 == allStudents.size())
                    System.out.println("Not found that student");
                }
            System.out.println();
            }
        }

    /* Main method loop ask student and then prints it.
    */
    public static void main(String arguments[])
        {
        getStudents();  /* Get a new student into data */
        System.out.println();
        listStudents(); /* Print all student name */
        System.out.println();
        findStudents(); /* Find student in data */
        System.out.println("Good bye!");
        }
    }