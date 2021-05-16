/******************************************************************************
 * 
 * hashDictionary.c
 *
 *   THIS HASH DICTIONARY DOES EXTRA
 *      - CAN PRINT PERCENTAGE OF COLLISION
 *      - ALLOW UP TO 3 DEFINITIONS
 *
 *      Store multiple words and difinitions. After building the dictionary,
 *      allow the user to request the definition of words. Each time the user
 *      enter word, look it up in the dictionary to find its definition and
 *      print them.
 *          
 *          Created by Nathaphop Sundarabhogin ID 60070503420
 *          3 APRIL 2018
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "abstractHashTable.h"
#include "timeFunctions.h"

#define STRLEN 200
#define STRWORD 32
#define ARRAYSIZE 26
#define BUCKET_COUNT 53
#define FILENAME "wordlist.txt"

typedef struct
    {
    char word[STRWORD];         /* Word in dictionary */
    char definition[3][STRLEN]; /* Definition of word */
    }WORD_T;

/* Print error message and exit
 * Argument:
 *      error - Error case
 */
void errorCase(int error)
    {
    if (error == 1) /* Have problem when open file */
        printf("Can't open file: %s.\n",FILENAME);
    else if (error == 2) /* Problem can't allocate memory */
        printf("Can't allocate new memory\n");
    else if (error == 3) /* Can't initialize the hash table */
        printf("Have some error while initialize the hash table\n");
    exit(0);
    }

/* Robust hash function that uses bitwise operations to
 * modify string values. Adapted from Kyle Loudon,
 * "Mastering Algorithms with C"
 */
unsigned int bitwiseOpHash(char* key)
    {
    unsigned int result = 0;
    unsigned int tmp = 0;
    int size = hashTableSize();
    int i = 0;
    for (i = 0; i < strlen(key); i++)
        {
        /* shift up four bits then add in next char */ 
        result = (result << 4) + key[i];
        if (tmp = (result & 0xf0000000))  /* if high bit is set */
            {
            /* XOR result with down shifted tmp */
            result = result ^ (tmp >> 24);
            /* then XOR with tmp itself */
            result = result ^ tmp;
            }
        }
    result = result % size;   /* make it fit in the table size */ 
    return result;
    }

/* Calculate percentage of collision and print.
 * Argument:
 *      collision - Amount of collision
 /*/
int computeCollision(int collision)
    {
    float percentage = collision*100/hashTableItemCount();
    printf("Amount of words: %d\n", hashTableItemCount());
    printf("Percentage Collision: %.02f %%\n", percentage);
    } 

/* Loop read text file each line, and send word to hash and keep data in linked
 * list of array.
 * Argument:
 *     dictionary - array of linked list
 */
void buildDictionary()
    {
    FILE *pFile = NULL;             /* Address of file after open */
    WORD_T *pNew = NULL;            /* New word for reading from each line */
    WORD_T *pFound = NULL;          /* Look up the same word */
    char text[STRLEN] = {0};        /* Text from reading each line */
    int count = 0;                  /* Count how many collision */
    int collision = 0;              /* Check that ther are collision or not */
    pFile = fopen(FILENAME,"r");
    if (pFile == NULL)  /* If can't open file, print error and exit */
        errorCase(1);
    /* Read each line in file */
    while (fgets(text, sizeof(text), pFile) != NULL)
        {
        if(text[0] == '\n') /* If it's blank line, across it */
            continue;
        pNew = (WORD_T*)calloc(1,sizeof(WORD_T));
        if (pNew == NULL)   /* If can't calloc, exit program */
            errorCase(2);
        sscanf(text,"%[^|]|%[^\n]", pNew->word, pNew->definition[0]);
        /* Search there are the same word or not */
        pFound = hashTableLookup(pNew->word);
        /* If there are the same word, keep definition in that word. */
        if(pFound != NULL)
            {
            if(strlen(pFound->definition[1]) == 0) 
                strcpy(pFound->definition[1], pNew->definition[0]);
            else if(strlen(pFound->definition[2]) == 0) 
                strcpy(pFound->definition[2], pNew->definition[0]);
            free (pNew);
            }
        /* If not have the same word insert a new one */
        else if(hashTableInsert(pNew->word, pNew, &collision) == 0)
            errorCase(2);
        /* Count how many collision */
        if(collision)
            count++;
        }
    printf("TEST:%d\n",count);
    computeCollision(count);
    fclose(pFile);
    return;
    }

/* Find word that want to know definition and print definition to terminal. If not
 * found, print no word to terminal.
 * Argument:
 *     dictionary - array of linked list
 *     stringFind - word that want to find in dictionary
 */
void printDefinition(char *stringKey)
    {
    WORD_T *pData = NULL;   /* Keep data after found it */
    long microseconds = 0;  /* Keep time value when look up */
    /* If there isn't any word, return */
    if ((stringKey == NULL) || (strlen(stringKey) == 0))
        {
        printf("Please input any word\n");
        return;
        }
    /* Find the word by key in hash table */
    recordTime(1);
    pData = hashTableLookup(stringKey);
    microseconds = recordTime(0);
    if(pData == NULL) /* If 'pData' equal to NULL, that mean word not found */
        printf("Word not found!\n");
    else
        {
        printf("Word: %s\n", pData->word);
        printf("Definition: %s\n", pData->definition[0]);
        if(strlen(pData->definition[1]) != 0) 
            printf("Definition: %s\n", pData->definition[1]);
        if(strlen(pData->definition[2]) != 0) 
            printf("Definition: %s\n", pData->definition[2]);
        }
    printf("Lookup required %ld microseconds\n\n", microseconds);
    return;
    }

/* Read text file for dictionary word. Then loop ask word from user and print
 * definition. After user input only new line, free all data and exit.
 */
int main()
    {
    char input[STRLEN] = {0};             /* Input from user */
    char word[STRWORD] = {0};             /* Word that want to find */
    if(hashTableInit(BUCKET_COUNT, &bitwiseOpHash)== 0)
        errorCase(3);
     /* Read text file */
    buildDictionary();
    printf("\n");
    while(1)    /* Loop ask until user input only '\n' */
        {
        memset(word,0,sizeof(word));
        memset(input,0,sizeof(input));
        printf("Input Word: ");
        fgets(input, sizeof(input), stdin);
        if(strlen(input) > STRWORD) /* Beware of long word */
            {
            printf("A word is too long!\n\n");
            continue;
            }
        else if(input[0] == '\n')   /* Input '\n', exit program */
            break;
        sscanf(input,"%s", word);
        /* Find definition of word and print */
        printDefinition(word);
        printf("\n");
        }
    hashTableFree(); /* Free all data */
    printf("Good bye!\n");
    }
