#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXDATA 100

typedef struct _test
{
	char *data;
	struct _test* pNext;
}TEST_T;

/* THIS IS HASH FUNCTION. USED FOR STUDY. We'll fix it after midterm */
unsigned int string_hash(void *string)
{
	/* This is the djb2 string hash function */

	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}

	return result%MAXDATA;
}

int main()
{
	TEST_T* hashTable[MAXDATA] = {0};	/* Hash Table, Keep all data in here */
	TEST_T* pNew = NULL;				/* Get new data from terminal line */
	TEST_T* pCurrent = NULL;			/* Current data for linked list in hash table */
	char input[200] = {0};				/* Get input from user */
	int count = 0;						/* Count how many list in data and print */
	int i = 0;							/* Loop */
	int a = 0;							/* Position of data after send to hash function */
	printf("Welcome to example of hash function!\n");
	printf("====================GET DATA========================\n");
	/* Loop ask */
	while(strcasecmp(input,"done")!=0)
		{
		printf("Input data ('done' for end): ");
		fgets(input,200,stdin);
		sscanf(input,"%s",input);

		/* Create new data */
		pNew = calloc(1,sizeof(TEST_T));
		if(pNew == NULL)
			exit(0);
		pNew->data = strdup(input);
		if(pNew->data == NULL)
			exit(0);

		/* Send string to hash function and get the address of hash table back */
		a=string_hash(input);
		printf("Position of '%s'\n on hash table: %d\n",input,a);
		printf("====================================\n");

		/* If it's new data keep in hash table, set that position to new */
		if(hashTable[a] == NULL)
			hashTable[a] = pNew;
		else /* But if there are some data in there keep in linked list */
			{
			pCurrent = hashTable[a];
			while(pCurrent != NULL)
				{
				if(pCurrent->pNext == NULL)
					{
					pCurrent->pNext = pNew;
					break;
					}
				pCurrent = pCurrent->pNext;
				}
			}
		}/* End loop ask */

	printf("\n====================PRINT DATA========================\n");
	/* Loop print all data */
	for(i = 0; i<MAXDATA; i++)
		{
		if((hashTable[i]) != NULL)	/* If there are data in hash table, print data */
			{
			count = 0;
			pCurrent = hashTable[i];
			while(pCurrent != NULL)	/* Print all of data that in linked list */
				{
				count++;
				printf("Data[%d][LinkedList:%d]%s\n",i,count, pCurrent -> data);
				pCurrent = pCurrent->pNext;
				}
			}
		}

	printf("\n====================FIND DATA========================\n");
	/* Example of loop find data */
	while(strcasecmp(input,"\n")!=0)
		{
		printf("Which data do you want to find (<CR> for end): ");
		fgets(input,200,stdin);
		sscanf(input,"%s",input);

		/* Send string to hash function and get the address of hash table back */
		a=string_hash(input);
		printf("Value after input hash function: %d\n",a);

		if((hashTable[a]) != NULL)	/* If there are data in hash table, print data */
			{
			count = 0;
			pCurrent = hashTable[a];
			while(pCurrent != NULL)	/* Print all of data that in linked list */
				{
				count++;
				if(strcmp(input,pCurrent->data) == 0)
					printf("Data[%d][LinkedList:%d]%s\n",a, count, pCurrent -> data);
				pCurrent = pCurrent->pNext;
				printf("====================================================\n");
				}
			if(count == 0)
				printf("Not Found!\n");
			}
		else
			printf("Not Found!\n");
		}
}