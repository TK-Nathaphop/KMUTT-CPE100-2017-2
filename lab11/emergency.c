/******************************************************************************
 *
 *  emergency.c
 *
 *      Simulate a hospital emergency room. This program will read a file
 *      and store each patient in a max heap. The extact the person and
 *      write in output file.
 *
 *          Nathaphop Sundarabhogin ID 60070503420
 *          26 April 2561
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractHeap.h"
#define LEN 128

typedef struct
    {
    char name[LEN];     /* First name of the patient */
    char problem[LEN];  /* Reason for coming to the emergency room */
    int severity;       /* indicates how serious the problem is
                           higher values mean more serious */
    }PATIENT_T;

/* Print error message that is a big problem and then exit
 * Argument:
 *      error - Error case
 */
void errorExit(int error)
    {
    printf("#SYSTEM: Program Error!\n");
    if (error == 1) /* Didn't input name of input file or name of output file */
        {
        printf("#SYSTEM: You must include input and output file\n");
        printf("#SYSTEM: Example: ./emergency input.txt output.txt\n");
        }
    else if (error == 2) /* Can't open input file */
        {
        printf("#SYSTEM: Can't open input file\n");
        }
    else if (error == 3) /* Can't open output file */
        {
        printf("#SYSTEM: Can't open output file\n");
        }
    else if (error == 3) /* Can't allocate memory */
        {
        printf("#SYSTEM: Can't allocate memory\n");
        }
    else if (error == 4) /* Have some error while insert to heap */
        {
        printf("#SYSTEM: Have some error while insert new data to heap\n");
        }
    printf("#SYSTEM: Program Exit\n");
    exit(0);
    }

/* Compare 2 patients.
 * If patient1 severity is lower than patient2 severity, return -1.
 * If patient1 severity is higher than patient2 severity, return 1.
 * If the severity values are the same, return 0.
 */
int comparePatients(void* patient1, void* patient2)
    {
    PATIENT_T* p1 = (PATIENT_T*)patient1;
    PATIENT_T* p2 = (PATIENT_T*)patient2;
    if (p1->severity < p2->severity)
        return -1;
    else if (p1->severity > p2->severity)
        return 1;
    else
        return 0;
    }

/* Count how many patient in file.
 * Argument:
 *      pFile - File that we want to count
 * Return amount of patient.
 */
int countPatient(FILE* pFile)
    {
    char input[LEN] = {0};  /* Get input from file */
    int count = 0;          /* Count how many patient */
    while(fgets(input,sizeof(input),pFile) != NULL)
        {
        count;
        if(strlen(input) == 1)
            break;
        }
    rewind(pFile);  /* Set to beginning of file */
    return count;
    }

/* Read all patients from file.
 * Argument:
 *      pFile - File that we want to read
 */
void readPatient(FILE *pFile)
    {
    char input[LEN] = {0};  /* Get input from file */
    PATIENT_T *pNew = NULL; /* New data */
    if(pFile == NULL)
        errorExit(2);
    while(fgets(input, sizeof(input),pFile) != NULL)
        {
        if(strlen(input) == 1)
            break;
        pNew = calloc(1, sizeof(PATIENT_T));
        if(pNew == NULL)
            errorExit(3);
        sscanf(input,"%s %s %d",pNew->name, pNew->problem, &pNew->severity);
        /* insert new data to heap */
        if(heapInsert(pNew) == 0)
            errorExit(4);
        }
    }

/* Write all patient data into output file and free all data in heap
 * Argument:
 *      pFile - File that we want to write down.
 */
void writePatient(FILE* pFile)
    {
    PATIENT_T *pData = heapExtract(); /* Data that we extract from heap */
    while(pData != NULL)
        {
        fprintf(pFile,"%s %s %d\n",pData->name, pData->problem, pData->severity);
        free(pData);
        pData = NULL; /* Set 'pData' to NULL for prevent error */
        pData = heapExtract();
        }
    }

/* Main Program. Count how many amount of patients, initial heap array,
 * read all patients in file and keep in heap array. Then write all patients
 * from heap array into output file.
 */
int main(int argc, char* argv[])
    {
    int amount = 0;         /* Amount of patient */
    FILE* pOpen = NULL;     /* File that we open */
    FILE* pClose = NULL;    /* File that we close */
    if ((argc < 3) || (argc > 3))   /* Check name of input/output file */
        errorExit(1);
    pOpen = fopen(argv[1], "r");
    if(pOpen == NULL)
        errorExit(2);
    /* Count how many patient, then initial array heap */
    amount = countPatient(pOpen);
    if(initHeap(&comparePatients, 1, amount) == 0)
        errorExit(3);
    printf("#SYSTEM: Read file\n");
    /* Read all patients in file */
    readPatient(pOpen);
    fclose(pOpen);
    pClose = fopen(argv[2], "w");
    if(pClose == NULL)
        errorExit(2);
    printf("#SYSTEM: Write file\n");
    /* Write patients from heap into output file */
    writePatient(pClose);
    fclose(pClose);
    printf("#SYSTEM: Finished!\n");
    printf("#SYSTEM: Good Bye!\n");
    }