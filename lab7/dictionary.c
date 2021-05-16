/******************************************************************************
 * 
 * dictionary.c
 *
 *      Store multiple words and difinitions. After building the dictionary,
 *      allow the user to request the definition of words. Each time the user
 *      enter word, look it up in the dictionary to find its definition and
 *      print them
 *          
 *          Created by Nathaphop Sundarabhogin ID 60070503420
 *          27 February 2018
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedListUtil.h"

#define STRLEN 200
#define STRWORD 32
#define ARRAYSIZE 26
#define FILENAME "wordlist.txt"

/* All 26 Alphabet */
char alphabet[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
                     'p','q','r','s','t','u','v','w','x','y','z'};


typedef struct
    {
    char word[STRWORD];         /* Word in dictionary */
    char definition[STRLEN];    /* Definition of word */
    }WORD_T;

/* Print error message and exit
 * Argument:
 *      error - Error case
 */
void errorCase(int error)
    {
    if (error == 1) /* Have problem when open file */
        printf("Can't open file: %s.\n",FILENAME);
    else if(error == 2) /* Problem can't allocate memory */
        printf("Can't allocate new memory\n");
    exit(0);
    }

/* Hash function, get word and then return number of alphabet order
 * (from a-z : 0-25)
 * Argument:
 *      word - word that want to hash
 */
int getDictIndex(char* word)
    {
    char c = tolower(word[0]);  /* Change to Lower case, to minus ASCII number */
    int position = c - 'a';     /* Difference of first char and 'a' */
    if(position < 0 || position > (ARRAYSIZE-1)) /* Prevent other alphabet input */
        position = 0;
    return position;
    }

/* Loop read text file each line, and send word to hash and keep data in linked
 * list of array.
 * Argument:
 *     dictionary - array of linked list
 */
void buildDictionary(LIST_HANDLE *dictionary)
    {
    FILE *pFile = NULL;             /* Address of file after open */
    WORD_T *pNew = NULL;            /* New word for reading from each line */
    char text[STRLEN] = {0};        /* Text from reading each line */
    int position = 0;               /* Position of the array after figure out */
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
        sscanf(text,"%[^:]:%[^\n]", pNew->word, pNew->definition);
        position = getDictIndex(pNew->word);
        /* If there isn't any list in table, created new list */
        if(dictionary[position] == NULL)
            {
            dictionary[position] = newList();
            if (dictionary[position] == NULL)
                errorCase(2);
            }
        /* Then keep the new data to the linked list */
        if(listInsertEnd(dictionary[position], pNew) == -1)
            errorCase(2);
        }
    fclose(pFile);
    return;
    }

/* Print all word and definition in dictionary
 * Argument:
 *     dictionary - array of linked list
 */
void printDictionary(LIST_HANDLE *dictionary)
    {
    int i = 0;              /* Count loop */
    WORD_T *pData = NULL;   /* Data that we want to print */
    /* Loop print each array */
    for (int i = 0; i < ARRAYSIZE; ++i)
        {
        printf("========== %c ==========\n",alphabet[i]);
        if (dictionary[i] == NULL) /* If there isn't linked list, print no word */
            printf("No words with letter \'%c\'\n", alphabet[i]);
        else
            {
            /* Reset linked list to first node, and check error return */
            if(listReset(dictionary[i]) == 0)
                printf("No words with letter \'%c\'\n", alphabet[i]);
            else
                {
                pData = listGetNext(dictionary[i]);
                if(pData == NULL)   /* If there isn't data, print no word */
                    {
                    printf("No words with letter \'%c\'\n", alphabet[i]);
                    continue;
                    }
                while(pData != NULL)    /* Print all data in linked list */
                    {
                    printf("%s: %s\n",pData->word, pData->definition);
                    pData = listGetNext(dictionary[i]);
                    }
                }
            }
        printf("\n");
        }
    return;
    }

/* Free all data in dictionary
 * Argument:
 *     dictionary - array of linked list
 */
void freeDictionary(LIST_HANDLE *dictionary)
    {
    int i = 0;              /* Count loop */
    WORD_T *pData = NULL;   /* Data that we want to print */
    for (int i = 0; i < ARRAYSIZE; ++i) /* Loop check all array */
        {
        if (dictionary[i] == NULL)  /* If there isn't any linked list, across it */
            continue;
        else
            {
            /* Reset linked list to first node, and check error return */
            if(listReset(dictionary[i]) == 0)
                continue;
            else
                {
                pData = listRemove(dictionary[i], 0);
                while(pData != NULL)
                    {
                    free(pData);
                    pData = listRemove(dictionary[i], 0);
                    }
                }
            }
        }
    return;
    }

/* Find word that want to know definition and print definition to terminal. If not
 * found, print no word to terminal.
 * Argument:
 *     dictionary - array of linked list
 *     stringFind - word that want to find in dictionary
 */
void printDefinition(LIST_HANDLE *dictionary,char *stringFind)
    {
    WORD_T *pData = NULL;   /* Keep data after found it */
    int position = 0;       /* Position of array after hash */
    int found = 0;          /* Check that found word or not */
    if(strlen(stringFind) == 0) /* If there isn't any word, return */
        {
        printf("Please input any word\n");
        return;
        }
    position = getDictIndex(stringFind);
    if (dictionary[position] == NULL)   /* No linked list in table */
            found = 0;
    else
        {
        /* Reset linked list to first node, and check error return */
        if(listReset(dictionary[position]) == 0)
            found = 0;
        else
            {
            pData = listGetNext(dictionary[position]);
            /* Loop compare string in all data in list */
            while(pData != NULL)
                { 
                if(strcasecmp(stringFind,pData->word) == 0)
                    {
                    found = 1;
                    printf("Definition: %s\n",pData->definition);
                    }
                pData = listGetNext(dictionary[position]);
                }
            }
        }
    if(found == 0) /* If 'found' equal to 0, that mean not found word */
        printf("Word not found!\n");
    return;
    }

/* Read text file for dictionary word. Then loop ask word from user and print
 * definition. After user input only new line, free all data and exit.
 */
int main()
    {
    LIST_HANDLE dictionary[ARRAYSIZE];    /* Array size of linked list */
    char input[STRLEN] = {0};             /* Input from user */
    char word[STRWORD] = {0};             /* Word that want to find */
    memset(dictionary,0,sizeof(dictionary));
     /* Read text file */
    buildDictionary(dictionary);
    /* Print all word and definition */
    printDictionary(dictionary);
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
        printDefinition(dictionary, word);
        printf("\n");
        }
    freeDictionary(dictionary); /* Free all data */
    printf("Good bye!\n");
    }