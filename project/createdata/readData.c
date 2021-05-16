#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleFacebook.h"
#include "userInterface.h"
#include "abstractHash.h"
#include "abstractTree.h"
#include "abstractStatus.h"
#include "abstractGraph.h"
#include "manageData.h"
#include "dumpFile.h"
#define datafile "sampledata.txt"
#define graphfile "sampledataFriend.txt"
#define statusfile "sampledataStatus.txt"

/* LOCAL FUNCTION.
 * Read E-mail from file, find data and set program 
 * like user login with E-mail to add data.
 * Argument:
 *      pFile - File that want to read E-mail
 * Return user that read from file.
 */
USER_T* _findAccess(char mail[LEN])
    {
    USER_T *pData = NULL;   /* Data that send to access login */
    pData = findData(mail);
    if (pData == NULL)  /* Can't find data */
        printError(4);
    else    /* Set system to working like user login */
        accessSignIn(pData);
    return pData;
    }

FILE* openFile(char filename[], char tag[])
	{
	FILE* open = fopen(filename,tag);
	if(open == NULL)
		printError(2);
	return open;
	}

/* Read all of data and keep in array */
void readTextData(FILE *pFile, USER_T **data, int max)
	{
	int count = 0;
	int line = 0;
	USER_T* pData = NULL;
	char input[512] = {0};
	char tag[LEN] = {0};
	char dataText[LEN] = {0};
	while ((fgets(input, sizeof(input), pFile) != NULL) && (count <= max))
		{
		line++;
		pData = (USER_T*)calloc(1, sizeof(USER_T));
		if(pData == NULL)
			printError(2);
		sscanf(input, "%s %[^\n]",tag ,dataText);
		if(strcmp(tag,"EMAIL") == 0)
			{
			if(findData(pData->mail) != NULL)
				{
				printf("Line No. %d",line);
				printf("%s have the same E-mail in system\n",pData->mail);
				free(pData);
				exit(0);
				}
			else
				{
				strcpy(pData->mail, dataText);
				count++;
				}
			}
		if(fgets(input, sizeof(input), pFile) != NULL)
			{
			line++;
			sscanf(input, "%s %[^\n]",tag ,dataText);
			if(strcmp(tag,"PASSWORD") == 0)
				strcpy(pData->password, dataText);
			else
				{
				printf("No Password on line %d",line);
				exit(0);
				}
			}
		if(fgets(input, sizeof(input), pFile) != NULL)
			{
			sscanf(input, "%s %[^\n]",tag ,dataText);
			line++;
			if(strcmp(tag,"NAME") == 0)
				strcpy(pData->name, dataText);
			else
				{
				printf("No Name on line %d",line);
				exit(0);
				}
			}
		if(fgets(input, sizeof(input), pFile) != NULL)
			{
			sscanf(input, "%s %[^\n]",tag ,dataText);
			line++;
			if(strcmp(tag,"BIRTH") == 0)
				sscanf(dataText,"%d %d %d",&pData->dateBirth[0], &pData->dateBirth[1], &pData->dateBirth[2]);
			else
				{
				printf("No Birthdate on line %d",line);
				exit(0);
				}
			}
		if(fgets(input, sizeof(input), pFile) != NULL)
			{
			sscanf(input, "%s %[^\n]",tag ,dataText);
			line++;
			if(strcmp(tag,"PHONE") == 0)
				strcpy(pData->phone, dataText);
			else
				{
				printf("No Phone on line %d",line);
				exit(0);
				}
			}
		if(fgets(input, sizeof(input), pFile) != NULL)
			{
			sscanf(input, "%s %[^\n]",tag ,dataText);
			line++;
			if(strcmp(tag,"GENDER") == 0)
				{
				if(strcmp(dataText,"MALE") == 0)
					pData->gender = G_MALE;
				else
					pData->gender = G_FEMALE;
				}
			else
				{
				printf("No Gender on line %d",line);
				exit(0);
				}
			}
		data[count-1] = pData;
		printf("Data No.%d\n",count);
		printf("Password: %s\n", pData->password);
		printf("\n");
		}
	}

void readTextGraph(FILE *pFile)
	{
    USER_T *pData = NULL;   /* Data that we will add to linked list */
	USER_T *pPend = NULL;	/* Pending data */
	char text[LONGLEN] = {0};
	char tag[LEN] ={0};
	char mail[10][LEN] = {0};
	int amount = 0;
	int i = 0;
	int line = 0;
	int (*function)(USER_T *pData) = NULL;
    int retVal = 0;         /* Return Value */
	while(fgets(text,sizeof(text),pFile) != NULL)
		{
		line++;
		printf("READ TEXT\n");
		printf("Read Line: %d\n",line);
		amount = sscanf(text, "%s %s %s %s %s %s %s %s %s %s %s", tag, mail[0],mail[1],mail[2],mail[3],mail[4],mail[5],mail[6],mail[7],mail[8],mail[9]);
    	pData = findData(mail[0]);
    	if(pData == NULL)
    		printError(4);
    	if (strcmp(tag, "FRIEND") == 0)        /* Read tag 'FRIEND' */
        	{
        	function = &addFriend;
        	printf("USER: %s\n",mail[0]);
        	printf("Friend:\n");
        	for(i=1; i < (amount-1); i++)
        		{
        		accessSignIn(pData);
        		pData = findData(mail[i]);
        		printf("%s\n",mail[i]);
        		retVal = function(pData);
        		if((retVal!=1) &&(retVal !=0))
        			printError(5);
        		}
        	printf("\n");
        	}
    	else if (strcmp(tag, "PENDING") == 0)  /* Read tag 'PENDING' */
        	{
        	function = &addPending;
        	printf("USER: %s\n",mail[0]);
        	printf("Pending:\n");
        	for(i=1; i < (amount-1); i++)
        		{
        		_findAccess(mail[i]);
        		printf("%s\n",mail[i]);
        		retVal = function(pData);
        		if((retVal!=1) &&(retVal !=0))
        			printError(5);
        		}
        	printf("\n");
        	}
    	else
	        printError(7);  /* Format of tag doesn't correct */
	    memset(mail,0,sizeof(mail));
		}
	}

void readTextStatus(FILE *pFile)
	{
	USER_T *pData = NULL;   /* Data that we will add to linked list */
	STATUS_T *pStatus = NULL;
	COMMENT_T *pComment = NULL;
	char text[LONGLEN] = {0};
	char textS[LONGLEN] = {0};
	char tag[LEN] ={0};
	char mail[LEN] = {0};
	int amount = 0;
	int date[5] = {0};
	int i = 0;
	int line = 0;
	int (*function)(USER_T *pData) = NULL;
    int retVal = 0;         /* Return Value */
	while(fgets(text, sizeof(text),pFile) != NULL)
		{
		line++;
		printf("Read Line: %d\n",line);
		amount = sscanf(text, "%s %s %[^\n]", tag, mail, textS);
		printf("E-mail: %s\n",mail);
		printf("%s : %s\n",tag,textS);
		printf("\n");
		if (amount != 3)
			{
			printf("Error! don't have data\n");
			exit(0);
			}
    	if (strcmp(tag, "STATUS") == 0)        /* Read tag 'FRIEND' */
        	{
        	if(fgets(text, sizeof(text), pFile) == NULL)
        		{
        		printf("Error! Don't have date\n");
        		exit(0);
        		}
        	line++;
			printf("Read Line: %d\n",line);
        	sscanf(text, "%s %d %d %d %d %d",tag ,&date[0], &date[1], &date[2], &date[3], &date[4]);
        	if(strcmp(tag, "DATE")!=0)
        		{
        		printf("ERROR! No tag DATE\n");
        		exit(0);
        		}
        	pStatus = updateStatus(textS, date, 2);
        	if(pStatus == NULL)
        		printError(1);
        	}
    	else if (strcmp(tag, "COMMENT") == 0)  /* Read tag 'PENDING' */
        	{
        	if(fgets(text, sizeof(text), pFile) == NULL)
        		{
        		printf("Error! Don't have date\n");
        		exit(0);
        		}
        	line++;
			printf("Read Line: %d\n",line);
        	sscanf(text, "%s %d %d %d %d %d",tag ,&date[0], &date[1], &date[2], &date[3], &date[4]);
        	if(strcmp(tag,"DATE")!=0)
        		{
        		printf("ERROR! No tag DATE\n");
        		exit(0);
        		}
        	if(pStatus == NULL)
        		{
        		printf("Error! Don't have status before");
        		exit(0);
        		}
        	pComment = updateComment(pStatus, textS, date);
        	if(pComment == NULL)
        		printError(5);
        	}
    	else
	        printError(7);  /* Format of tag doesn't correct */
		}
	}


/* Count how many items in file */
int countData(FILE *pFile)
	{
	int count = 0;
	char input[512] = {0};
	char tag[LEN] = {0};
	char data[LEN] = {0};
	while(fgets(input, sizeof(input), pFile) != NULL)
		{
		sscanf(input, "%s %[^\n]",tag ,data);
		if(strcmp(tag,"EMAIL") == 0)
			count++;
		}
	printf("There are %d items in file\n",count);
	rewind(pFile);
	return count++;
	}

void keepInMain(USER_T *data[],int max)
	{
	int i = 0;
	for(i=0;i<max;i++)
		{
		if(data[i] != NULL)
			{
			printf("No. %d\n",i);
			printData(data[i]);
			addData(data[i]);
			}
		}
	}

int main()
	{
	char input[100] = {0};
	int count = 0;
	USER_T **data = NULL;
	FILE* pFile = openFile(datafile, "r");
	count = countData(pFile);
	data = (USER_T**)calloc(count,sizeof(USER_T*));

	readTextData(pFile, data, count);
	fclose(pFile);
	keepInMain(data, count);

	pFile = openFile(graphfile, "r");
	readTextGraph(pFile);
	fclose(pFile);

	pFile = openFile(statusfile, "r");
	readTextStatus(pFile);
	fclose(pFile);
	writeDatabase();
	}