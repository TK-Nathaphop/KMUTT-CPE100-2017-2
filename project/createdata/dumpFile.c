/******************************************************************************
 *
 * dumpFile.c
 *
 *        This module uses for reading database, validating and sorting all of data
 *        (After read from database), creating new database, saving database, and 
 *        writing dump file.
 *      
 *      Created by SETTHAWUT LEELAWATTHANAPANIT (SAAB)    ID : 3466
 *      17 APRIL 2018
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleFacebook.h"
#include "manageData.h"
#include "userInterface.h"
#include "validate.h"
#define PROFILE_FILE "profileFB.dat"
#define RELATION_FILE "relationFB.txt"
#define STATUS_FILE "statusFB.txt"

/************** LOCAL FUNCTIONS, don't declare in header file ****************/

/* LOCAL FUNCTION.
 * Open database file and return back. If there isn't any file create new one.
 * Argument:
 *      pOpen - file name that we want to open
 *      select - Select for text file[1] or binary file[2]
 * Return file after open back.
 */
FILE *_openFileRead(char *pOpen, int select)
    {
    FILE *pFile = NULL;     /* Get address after open file. */
    char type[LEN] = {0};       /* type of file */
    if (select == 1)    /* Text file */
        strcpy(type,"r");
    else if (select == 2)   /* Binary File */
        strcpy(type,"rb");
    pFile = fopen(pOpen, type);
    if(pFile == NULL)   /* If can't open read file, create new data file. */
        {
        if (select == 1)    /* Text file */
            strcpy(type,"w");
        else if (select == 2)   /* Binary File */
            strcpy(type,"wb");
        printf("#SYSTEM: Data file not found, create new data file.\n");
        pFile = fopen(pOpen, type);
        if(pFile == NULL) /* If can't open a new file, program is crashed. */
            printError(3);
        fclose(pFile);
        printf("#SYSTEM: Create data file success.\n\n");
        pFile = fopen(pOpen, type);
        /* After create new file, but program can't open it. Program is crashed. */
        if(pFile == NULL)
            printError(2);
        }
    return pFile;
    }

/* LOCAL FUNCTION.
 * Open database file and return back. If there isn't any file create new one.
 * Argument:
 *      pOpen - file name that we want to open
 *      select - Select for text file[1] or binary file[2]
 * Return file after open back.
 */
FILE *_openFileWrite(char *pOpen, int select)
    {
    FILE *pFile = NULL;     /* Get address after open file. */
    char type[LEN] = {0};       /* type of file */
    if (select == 1)    /* Text file */
        strcpy(type,"w");
    else if (select == 2)   /* Binary File */
        strcpy(type,"wb");
    pFile = fopen(pOpen, type);
    if(pFile == NULL)   /* If can't open read file, create new data file. */
        {
        printf("#SYSTEM: Error! Unable to create new data file!\n");
        printf("#SYSTEM: Program exit!\n");
        exit(0);
        }
    return pFile;
    }

/* LOCAL FUNCTION.
 * Read E-mail from file, find data and set program 
 * like user login with E-mail to add data.
 * Argument:
 *      pFile - File that want to read E-mail
 * Return user that read from file.
 */
USER_T* _mailAccess(char mail[LEN])
    {
    USER_T *pData = NULL;   /* Data that send to access login */
    pData = findData(mail);
    if (pData == NULL)  /* Can't find data */
        printError(4);
    else    /* Set system to working like user login */
        accessSignIn(pData);
    return pData;
    }

/* Subfunction of '_readStatusFile' read mail and date in file
 * and validate.
 * Arguments:
 *      pFile - File that we want to read
 *      mail - Mail for return after read
 *      date - Date for return after read
 */
void _readDataStatus(FILE *pFile, char mail[LEN], int date[])
    {
    char read[LONGLEN] = {0};   /* Text read from file */
    char tag[LEN] = {0};        /* Tag of data */
    /* Read mail of owner of status/comment */
        if (fgets(read, sizeof(read), pFile) == NULL)
            printError(8);  /* Unable to read data */
        else if (sscanf(read,"%s %s", tag, mail) != 2)
            printError(5);  /* Wrong format of tag and data */
        else if (strcmp(tag, "MAIL") != 0)
            printError(7);  /* Tag not arrange correctly */
        _mailAccess(mail);
        /* Read date of status/comment */
        if(fgets(read, sizeof(read), pFile) == NULL)
            printError(8);  /* Unable to read data */
        else if(sscanf(read,"%s %d %d %d %d %d", tag, &date[0], &date[1], 
                                            &date[2], &date[3], &date[4]) != 6)
            printError(5);  /* Wrong format of tag and data */
        else if (strcmp(tag, "DATE") != 0)
            printError(7);  /* Tag not arrange correctly */
    }

/* Subfunction of '_readRelationFile' check data it's friend or pending,
 * validate and then keep in data.
 * Arguments:
 *      tag - Tag name of data
 *      mail - Mail of tag
 */
void _readDataRelation(char tag[LEN], char mail[LEN])
    {
    int (*function)(USER_T *pData) = NULL;
    /* Function that work depends on FRIEND tag/ PENDING tag */
    int retVal = 0;         /* Return Value */
    USER_T *pData = NULL;   /* Data that we will add to linked list */
    if (strcmp(tag, "FRIEND") == 0)        /* Read tag 'FRIEND' */
        {
        function = &addFriend;
        pData = findData(mail);
        if (pData == NULL) 
            printError(4);    /* Can't find data */
        }
    else if (strcmp(tag, "PENDING") == 0)  /* Read tag 'PENDING' */
        {
        function = &addPending;
        pData = getUser();
        _mailAccess(mail);
        }
    else
        printError(7);  /* Format of tag doesn't correct */
    retVal = function(pData);
    /* Can't allocate memory */
    if (retVal == -1)
        printError(1);
    /* If it not success or already add, there're some problems */
    else if ((retVal != 1) && (retVal != 0))
        printError(6);
    if (strcmp(tag, "PENDING") == 0)  /* Set access back */
        accessSignIn(pData);
    }

/* LOCAL FUNCTION.
 * Read all profile of user in file
 */
void _readProfileFile(FILE* pFile)
    {
    USER_T *pNew = NULL;    /* New data after read */
    pNew = (USER_T*)calloc(1, sizeof(USER_T));
    if(pNew == NULL)    /* Can't allocate memory */
        printError(1);
    while(fread(pNew, sizeof(USER_T), 1, pFile) == 1)
        {
        if(findData(pNew->mail) != NULL)   /* Found same data */
            {
            printf("#SYSTEM: There are same E-mail in system.\n");
            free(pNew);
            }
        else
            addData(pNew);
        pNew = (USER_T*)calloc(1, sizeof(USER_T));
        if(pNew == NULL)    /* Can't allocate memory */
            printError(1);
        }
    /* Out from loop free pNew that we doesn't read data */
    free (pNew);
    }

/* LOCAL FUNCTION.
 * Read all relation of user in relation file.
 * Argument:
 *      pFile - File that want to read
 */
void _readRelationFile(FILE* pFile)
    {
    char read[LONGLEN] = {0};  /* Read data from file */
    char tag[LEN] = {0};       /* Tag of data */
    char mail[LEN] = {0};      /* Mail */
    while(fgets(read, sizeof(read), pFile) != NULL)
        {
        if(sscanf(read,"%s %s", tag, mail) != 2)
            printError(5);  /* Wrong format of tag and data */
        if (strcmp(tag, "USER") == 0)        /* Read tag 'FRIEND' */
            _mailAccess(mail);
        else    /* Otherwise, it's tag 'FRIEND' or 'PENDING' */
            {
            _readDataRelation(tag, mail);
            }
        }
    }

/* LOCAL FUNCTION.
 * Read all relation of user in relation file.
 * Argument:
 *      pFile - File that want to read
 */
void _readStatusFile(FILE *pFile)
    {
    int type = 0;                   /* Use to know it's status or comment
                                       1 - Status, 2 - Comment, */
    char read[LONGLEN+LEN] = {0};   /* Read data from file */
    char text[LONGLEN] = {0};       /* Text of status/comment */
    char tag[LEN] = {0};            /* Tag of data */
    char mail[LEN] = {0};           /* Owner of status/comment */
    int date[5] = {0};              /* Date of status/comment */
    STATUS_T *pStatus = NULL;       /* Keep Status */
    while(fgets(read, sizeof(read), pFile) != NULL)
        {
        if(sscanf(read,"%s %[^\n]", tag, text) != 2)
            printError(5);          /* Wrong format of tag and data */
        if (strcmp(tag, "STATUS") == 0)        /* Check for tag 'STATUS' */
            type = 1;
        else if (strcmp(tag, "COMMENT") == 0)  /* Check for tag 'COMMENT' */
            type = 2;
        else
            printError(7);  /* Tag not arrange correctly */
        _readDataStatus(pFile, mail, date);
        if (type == 1)  /* Keep Status */
            {
            pStatus = updateStatus(text, date, 2);
            if (pStatus == NULL)
                printError(1);  /* Can't allocate memory */
            }
        else if (type == 2) /* Keep Comment */
            {
            if (pStatus == NULL)
                printError(7); /* Tag not arrange correctly */
            else if (updateComment(pStatus, text, date) == NULL)
                printError(1);  /* Can't allocate memory */
            }
        }
    }

/* LOCAL FUNCTION. Validate all event data after read file. If event code is
 * invalid, eject that data. If data in event is not valid, delete event data
 * (Keep event code). After validate, return new data and amount back.
 * ARGUMENTS: pEvent - All of event data,  pAmount - Amount of event data.
 */
void validateDatabase()
    {
    
    }

/***************** PUBLIC FUNCTION, declare in header file *****************/

/* Open each file and read all data into system
 */
void readDatabase()
    {
    FILE *pFile = NULL;     /* File that we want to read */

    /* Open profile file and read*/
    pFile = _openFileRead(PROFILE_FILE, 2);
    _readProfileFile(pFile);
    if(pFile != NULL)
        fclose(pFile);
    pFile = NULL;

    /* Open relation file and read */
    pFile = _openFileRead(RELATION_FILE, 1);
    _readRelationFile(pFile);
    if(pFile != NULL)
        fclose(pFile);
    pFile = NULL;
    /* Open status file and read */
    pFile = _openFileRead(STATUS_FILE, 1);
    _readStatusFile(pFile);
    if(pFile != NULL)
        fclose(pFile);
    pFile = NULL;
    /* Set system to signout */
    signOut();
    }

/* Open each file and write down all data into each file
 */
void writeDatabase()
    {
    FILE *pFile = NULL;     /* File that we want to write */
    /* Write data into relation file */
    pFile = _openFileWrite(RELATION_FILE, 1);
    writeFile(pFile, 2);
    fclose(pFile);
    printf("#SYSTEM: Save data into relation file success\n");
    /* Write data into status file */
    pFile = _openFileWrite(STATUS_FILE, 1);
    writeFile(pFile, 3);
    fclose(pFile);
    printf("#SYSTEM: Save data into status file success\n");
    /* Write data into profile file */
    pFile = _openFileWrite(PROFILE_FILE, 2);
    writeFile(pFile, 1);
    fclose(pFile);
    printf("#SYSTEM: Save data into profile file success\n");
    }