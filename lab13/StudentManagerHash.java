/******************************************************************************
 *
 * StudentManagerHash.java
 * 
 *  Simple class to represent a student in a registration system.
 *  This problem loob ask for add data, show all names and loop find student ID.
 *
 *  Created by Nathaphop ID 60070504320.
 *
 *****************************************************************************/

import java.io.*;
import java.util.*;

public class StudentManagerHash extends Student
    {    
    protected static Hashtable<Integer,Student> allStudents
                     = new Hashtable<Integer,Student>();
    
    /* Loop get new student into hash table */
    public static void getStudents()
        {
        Student newStudent;
        String ask = "Dummy";
        boolean bContinue = true;
        Integer key;
        allStudents.clear();
        while (bContinue)
            {
            newStudent = new Student();
            key = new Integer(newStudent.getStudentId());
            allStudents.put(key, newStudent);
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
        Student student;
        Enumeration key = allStudents.keys();
        while(key.hasMoreElements())
            {
            student = (Student)allStudents.get(key.nextElement());
            System.out.println(student.getStudentName());
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
            findStudent = allStudents.get(input);
            if(findStudent != null)
                    {
                    findStudent.display();
                    System.out.println("Average Grade:" +
                                        findStudent.computeAvgGrade());
                    }
            else
                System.out.println("Not found that student");
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