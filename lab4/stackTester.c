/*
 *  stackTester.c 
 *
 *  Driver program for illustrating a stack
 *
 *  Created by Sally Goldin, 21 December 2011 for CPE 113
 *    Fixed problem with main arguments, 29 Jan 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "abstractStack.h"

int getMenuOption();
char * getTimestampString();

/* Loop asking for actions until the user chooses to exit */
int main(int arc, char * argv[])
{
    int handle = 0;
    char input[64];
    char stringval[64];
    char* removedString = NULL;
    char* newString = NULL;
    int retval = 0;
    
    int choice = getMenuOption();
    while (choice != 5)
    {
	switch (choice)
	{
	    case 1:  /* push */
	        {
		newString = getTimestampString();
		printf("About to push: %s\n", newString);
                if (!push(newString))
		   {
		   printf("Error! stack is full!\n");
		   free(newString);
		   } 
		break;
	        }
	    case 2: /* pop */
	        {
		removedString = pop();
		if (removedString == NULL)
		   {
		   printf("Error! stack is empty!\n");
		   } 
                else
		   {
		   printf("Popped: %s\n", removedString);
		   free(removedString);
                   }
		break;
	        }
	    case 3:
	        {
	        stackClear();
		break;
		}
	    case 4:
	        {
	        printDebug();
		break;
		}
	    default:
		printf("Invalid option - we should never get here!\n");
	    }  /* end switch  */
	choice = getMenuOption();
    }      /* end while loop */

/* exit here - we're done */
}


/* Show menu of options. Return the user-selected option
 */
int getMenuOption()
{
    char input[32];
    int option = -1;
    while (option < 0)
       {
       printf("\nQueue Tester options:\n");
       printf("  1 - Add an item to the stack (push)\n");
       printf("  2 - Remove an item from the stack (pop)\n");
       printf("  3 - Clear and reset stack\n");
       printf("  4 - Show current stack contents\n");
       printf("  5 - Exit\n");
       printf("Which option? ");
       fgets(input,sizeof(input),stdin);
       sscanf(input,"%d",&option);
       if ((option > 5) || (option < 1))
           {
	   printf("Invalid selection - choose 1 to 4\n");
	   option = -1;
	   }
       }
    printf("\n");
    return option;
}

/* Create a string that shows the current date and time
 * and return it. Note that this function allocates memory
 * which should be freed.
 */
char * getTimestampString()
{

     char * format = "Created at %T";
     char * buffer = (char*) malloc(32);
     time_t t;
     struct tm *tmp;
     if (buffer == NULL)
        {
	fprintf(stderr,"Memory allocation error in getTimestampString\n");
	exit(1);
        } 
     t = time(NULL);
     tmp = localtime(&t);
     strftime(buffer, 32, format, tmp);
     return buffer;  
}
