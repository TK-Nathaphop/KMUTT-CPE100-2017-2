/******************************************************************************
 *
 *  newBubble.c
 *  
 *      Read a set of strings from a text file in to dynamic allocated array
 *      of pointer to pointer, sort the array using bubble sort and then write
 *      it to another text file. The original file includes a count of the
 *      number of strings and the maximum string size in the first line. 
 *
 *          Created by Nathaphop Sundarabhogin ID 60070503420
 *          23 Jan 2018
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "timeFunctions.h"
#define MAX 128

/*************** Declare Function ********************/
void swapStrings(char** array, int i, int j);
void sortArray(char **array, long int count);
void writeArray(char **array,long int count,char* outputFilename);
int readArray(char **array, long int count, FILE* pFp);
unsigned long recordTime(int bStart); 

/* Global variables */
/* Can delete it, but keep it for check that it's the same as 'stringBubble.c'
 * or not
 */
int maxsize = 0;      /* Length of longest string */

/* Main function. 
 * Reads first line of file to control allocation.
 * Allocates array and reads from the file. Then sorts
 * the strings and writes them to another file.
 */
int main(int argc, char* argv[])
    {
    char inputLine[MAX];  		/* buffer for reading file data */
    long int count = 0;   		/* number of lines/names in file */
    FILE* pInfile = NULL; 		/* File pointer for input file */
    unsigned long interval = 0; /* measure time required to sort */
    int i = 0;            		/* Count loop */
    char ** data = NULL;  		/* This will become array of pointer */
    /* Input and output filenames as specified by the user */
    char inputFile[MAX]; 
    char outputFile[MAX];

    /* check to make sure we have the right number of arguments */
    if (argc != 3)
       {
       fprintf(stdout,"Wrong number of arguments! Correct usage: \n");
       fprintf(stdout,"  ./stringBubble [inputfilename] [outputfilename]\n");
       exit(1);
       }
    /* Copy files from argument array to local variables */
    strcpy(inputFile,argv[1]); 
    strcpy(outputFile,argv[2]);

    /* Try to open the input file */
    pInfile = fopen(inputFile,"r");
    /* Check that the open succeeded */
    if (pInfile == NULL)
       {
       fprintf(stderr,"Unable to open file '%s'\n",inputFile);
       exit(1);
       }
    /* Read the first line in the file so we know what to allocate */
    if (fgets(inputLine,sizeof(inputLine),pInfile) == NULL)
       {
       fprintf(stderr,"Input file seems to be empty\n");
       exit(2);
       }
    sscanf(inputLine,"%ld %d",&count ,&maxsize);
    if (count == 0)
       {
       fprintf(stderr,"Input file does not have expected format\n");
       exit(3);
       }
    fprintf(stdout,"Input file %s contains %ld items to sort\n",inputFile,count);
    /* If we get this far, we can do the allocation */
    data = (char **) calloc(count,sizeof(char*)); /* size of pointer of char */        
    if (data == NULL)
       {
       fprintf(stderr,"Memory allocation error\n");
       exit(4);
       }
    /* Read the data. This function returns 0 if an error occurs */    
    if (!readArray(data,count,pInfile))
       {
       fprintf(stderr,"Error reading information from file\n");
       fclose(pInfile);
       free(data);
       exit(5);
       }
    fclose(pInfile);
    /* Sort the array*/
    recordTime(1);
    sortArray(data,count);
    interval = recordTime(0);
    fprintf(stdout,
         "Sorting %ld items required %ld microseconds\n",count,interval);
    fprintf(stdout,
     "(%ld microseconds per item)\n",interval/count);
    /* Write the sorted array to a file */
    writeArray(data,count,outputFile);
    for(i = 0; i < count; i++)
        {
        if(data[i] != NULL)
            free(data[i]);
        }
    free(data);
    }

/* Read the contents of the file into the array. When read each line, declare a
 * new address of string and keep in pointer array.
 * Arguments
 *     array    - one dimensional array of pointer of char
 *     count    - number of expected lines
 *     pFp      - file pointer for open input file 
 * Returns 1 for success, 0 if some read error (e.g. not enough ines in the file.
 */
int readArray(char **array, long int count, FILE* pFp)
    {
    char inputLine[MAX];  /* buffer for reading file data */
    int i;                /* loop counter */
    int bOk = 1;          /* return status */
    int len = 0;          /* for string length */ 
    for (i = 0; i < count; i++)
        {
        if (fgets(inputLine,sizeof(inputLine),pFp) == NULL)
            {
            bOk = 0;  /* File does not have expected num of lines */
            break;  
            } 
        /* get rid of newline then store */
        len = strlen(inputLine);
        if (inputLine[len-1] == '\n')
            inputLine[len-1] = '\0';
        array[i] = strdup(inputLine);
        }
    return bOk;
    }

/* Sort the array 'array' into ascending
 * order using the BubbleSort algorithm.
 * Arguments
 *     array    - one dimensional array of pointer of char
 *     count    - number of expected lines
 */
void sortArray(char **array, long int count)
    {
    long int i;                 /* Count loop */
    long int swapCount = 1;     /* Count sorting */
    char *temp = NULL;          /* Temporary address of string */
    while (swapCount > 0)
        {
        swapCount = 0;
        for (i = 0; i < count-1; i++)
            {
            /* if item[i] should be later than item [i+1] */
            if (strcmp(array[i], array[i+1]) > 0) 
                {
                swapStrings(array, i, i+1);
                swapCount = swapCount + 1;
                }
            }
        }
    return;
    }

/* Swap the contents of two strings.
 * Arguments
 *      array - one dimensional array of pointer of char
 *      i and j - position that want to swap
 * Upon return, array at position i will hold the address of j position.
 * And position j will hold the address of position i.
 */
void swapStrings(char** array, int i, int j)
    {
    char* temp;         /* Temporary to keep address of string */
    /* Swap position of 2 address */
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    return;
    }


/* Output the values stored in the array to a text file with
 * the same format as the input file
 * Arguments
 *     array    - one dimensional array of pointer of char
 *     count    - number of expected lines
 *     outputFilename - name of output file
 */
void writeArray(char **array,long int count,char* outputFilename)
    {
    int i;                      /* Count loop */
    FILE* pOutfile = NULL;      /* Get address after open file. */
    /* open output file */
    pOutfile = fopen(outputFilename,"w");
    if (pOutfile != NULL)
        { 
        fprintf(pOutfile,"%ld %d\n", count ,maxsize);
        for (i = 0; i < count; i++)
            fprintf(pOutfile,"%s\n", array[i]);
        fclose(pOutfile); /* Very important to close output files */
        }
    else
        fprintf(stderr,"Error - cannot open output file %s\n",outputFilename);
    return;
    }



