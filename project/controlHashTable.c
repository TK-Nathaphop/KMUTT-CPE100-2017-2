/******************************************************************************
 *
 *  controlHashTable.c
 *
 *      Implementary of hash table. Keep data of hash table in this file.
 *
 *      Created by Setthawut Leelawatthanapanit (Saab)    ID : 60070503466
 *      17 APRIL 2018
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "simpleFacebook.h"
#include "abstractTree.h"
#define TABLESIZE 1001

/* Hash table */
static USERTREE_T *_pTable[TABLESIZE] = {0};

/***************************** LOCAL FUNCTION ********************************/

/* LOCAL FUNCTION.
 * Calcuate hash value from key(mail).
 * Argument: 
 *      pKey - Keep data(mail) that wants to know hash value
 * Return hash value after calculating.
 */
unsigned int _hashFunction(unsigned char *pKey)
    {
    long long int hashVal = 0;
    unsigned char *p;
    p = pKey;
    while ((*p != '\0') && (*p != '@'))
        {
        hashVal = 31 * (hashVal + *p);
        ++p;
        }
    return hashVal%TABLESIZE;
    }

/**************************** PUBLIC FUNCTION ********************************/

/* Insert a value into the hash table. Key is E-mail of user.
 * Argument:
 *      pPerson - Keep data that want to insert.
 * Return 1 for success. Return 0 for same data. Return -1 for can't allocate.
 */
int hashTableInsert(USER_T *pPerson)
    {
    USERTREE_T* pNew = (USERTREE_T*)calloc(1, sizeof(USERTREE_T)); /* New node 
                                                                      of tree */
    int index = 0;      /* Position of hash table after send to hash function */
    int retVal = 0;     /* Return value */
    int i = 0;          /* Count loop */
    if(pNew == NULL)    /* Can't allocate memory */
        return -1;
    /* Change all character of mail to lower case */
    for(i = 0; i < strlen(pPerson->mail); i++)
        pPerson->mail[i] = tolower(pPerson->mail[i]);
    index = _hashFunction(pPerson->mail);
    if (pNew == NULL)   /* Can't allocate memory */
        {
        if(pPerson != NULL)
            free(pPerson);
        retVal = -1;
        }
    else    /* Else, continue working */
        {
        pNew->pData = pPerson;
        retVal = addDataTree(&_pTable[index], pNew);
        /* Have same data, free all new data */
        if (retVal == 0)
            {
            free(pNew->pData);
            free(pNew);
            }
        }
    return retVal;
    }

/* Look up a data in the hash table.
 * Argument:
 *      pKey - Keep data(mail) that want to look up
 * If found it, return that data and return null if not found.
 */
USER_T* hashTableLookup(char *pKey)
    {
    int index = 0;                  /* Position of hash table */
    int i = 0;                      /* Count loop */
    USERTREE_T *pTreeNode = NULL;   /* Tree node after send to find */
    /* Change all character to lower case */
    for(i = 0; i < strlen(pKey); i++)
        pKey[i] = tolower(pKey[i]);
    index = _hashFunction(pKey);
    if (_pTable[index] != NULL)
        {
        pTreeNode = findDataTree(_pTable[index], pKey);
        if(pTreeNode == NULL)   /* Not found data */
            return NULL;
        else
            return pTreeNode->pData;
        }
    else
        return NULL;
    }

/* This function return maximum bucket of array of hash table
 */
int hashTableBucketSize()
    {
    return TABLESIZE;
    }

/* This function return root node of tree in hash table
 * Argument:
 *      position - position of array in hash table
 */
USERTREE_T* hashTableData(int position)
    {
    if (_pTable[position] != NULL)
        return _pTable[position];
    else
        return NULL;
    }

/* Taking a random data and return that data when function finishes.
 */
USER_T* randomFriendHash()
    {
    int num = 0;  /* Keep number that random. */
    while (1)   /* Loop for find until found data. */
        {
        num = rand()%TABLESIZE;
        if (_pTable[num] != NULL)
            return randomFriendTree(_pTable[num]);
        }
    }