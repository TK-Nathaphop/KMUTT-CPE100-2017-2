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
#define datafile "sampledata.txt"
#define graphfile "sampledataFriend.txt"
#define statusfile "sampledataStatus.txt"

void printErrorData(int select)
	{
	if(select == 1)
		printf("Can't open file\n");
	else if (select == 2)
		printf("Can't allocate memory\n");
	exit(0);
	}


FILE* openFile(char filename[], char tag[])
	{
	FILE* open = fopen(filename,tag);
	if(open == NULL)
		printErrorData(1);
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
	char data[LEN] = {0};
	while ((fgets(input, sizeof(input), pFile) != NULL) && (count <= max))
		{
		line++;
		pData = (USER_T*)calloc(1, sizeof(USER_T));
		if(pData == NULL)
			printErrorData(2);
		sscanf(input, "%s %[^\n]",tag ,data);
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
				strcpy(pData->mail, data);
				count++;
				}
			}
		if(fgets(input, sizeof(input), pFile) != NULL)
			{
			line++;
			sscanf(input, "%s %[^\n]",tag ,data);
			if(strcmp(tag,"PASSWORD") == 0)
				strcpy(pData->password, data);
			else
				{
				printf("No Password on line %d",line);
				exit(0);
				}
			}
		if(fgets(input, sizeof(input), pFile) != NULL)
			{
			sscanf(input, "%s %[^\n]",tag ,data);
			line++;
			if(strcmp(tag,"NAME") == 0)
				strcpy(pData->name, data);
			else
				{
				printf("No Name on line %d",line);
				exit(0);
				}
			}
		if(fgets(input, sizeof(input), pFile) != NULL)
			{
			sscanf(input, "%s %[^\n]",tag ,data);
			line++;
			if(strcmp(tag,"BIRTH") == 0)
				sscanf(data,"%d %d %d",&pData->dateBirth[0], &pData->dateBirth[1], &pData->dateBirth[2]);
			else
				{
				printf("No Birthdate on line %d",line);
				exit(0);
				}
			}
		if(fgets(input, sizeof(input), pFile) != NULL)
			{
			sscanf(input, "%s %[^\n]",tag ,data);
			line++;
			if(strcmp(tag,"PHONE") == 0)
				strcpy(pData->phone, data);
			else
				{
				printf("No Phone on line %d",line);
				exit(0);
				}
			}
		if(fgets(input, sizeof(input), pFile) != NULL)
			{
			sscanf(input, "%s %[^\n]",tag ,data);
			line++;
			if(strcmp(tag,"GENDER") == 0)
				{
				if(strcmp(data,"MALE") == 0)
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
		data[count-1] = pNew;
		printf("Data No.%d\n",count);
		printData(data[count-1]);
		printf("Password: %s\n", pData->password);
		printf("\n");
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

writeData(FILE* pFile, USER_T ** data, int count)
	{

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
	pFile = openFile("profileFB.dat","wb");
	writeData(pFile,)
	fclose(pFile);
	}