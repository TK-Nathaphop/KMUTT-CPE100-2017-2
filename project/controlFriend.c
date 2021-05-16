/******************************************************************************
 *
 * controlFriend.c
 *
 *      Implementary of graph of relation of friends. 
 *      Manage structure of linked list of friend and
 *      linked list of friend pending request.
 *
 *      Created by Chawakorn Boonrin (Bright)    ID : 60070503415
 *      17 April 2018
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "simpleFacebook.h"
#include "abstractGraph.h"
#include "abstractHash.h"

#define MAXSUGGEST 2

static int amountSuggestF = 0;

/***************************** LOCAL FUNCTION ********************************/

/* Loop write all of tag and data in linked list of friend into relation file
 * and free data.
 * Arguments:
 *      pHead - Head node that linked list
 *      pFile - File that we want to write down
 *      tag - Tag of data that we want to write in front of data
 */
void _writeFriend(FRIENDLIST_T *pHead, FILE *pFile, char tag[])
    {
    FRIENDLIST_T *pCurrent = pHead;     /* Current node of linked list */
    FRIENDLIST_T *pDelete = NULL;       /* Node that want to delete */
    USER_T *pData = NULL;               /* Data of friend list */
    char mail[LEN] = {0};               /* E-mail that write down after tag */
    while(pCurrent != NULL)
        {
        pData = pCurrent->pData;
        strcpy(mail, pData->mail);
        fprintf(pFile, "%s %s\n", tag, mail);
        pDelete = pCurrent;
        pCurrent = pCurrent->pNext;
        /* Free linked list node. */
        if(pDelete != NULL)
            free(pDelete);
        }
    }

/* LOCAL FUNCTION.
 * Find suggest friend from friend of friends of user that we want.
 * ARGUMENTS:
 *     pUser    - Keep user profile that wants to find suggest friend
 *     pUserF   - Keep linked list of friends of user
 *     pFriendF - Keep linked list of friend of friends of user
 *     pSuggest - Keep all suggest friend profiles
 */
void _findFOF(USER_T *pUser, FRIENDLIST_T *pUserF, FRIENDLIST_T *pFriendF, USER_T **pSuggest)
    {
    while ((pFriendF != NULL) && (amountSuggestF != MAXSUGGEST))
        {
        if (findFriend(pFriendF, pUser->mail) == NULL)
            { /* That user is not a friend with a friend of friend */
            pSuggest[amountSuggestF] = pFriendF->pData;
            amountSuggestF++;
            }
        pFriendF = pFriendF->pNext;
        }
    return;
    }

/* LOCAL FUNCTION.
 * Taking a random to find suggest friend.
 * ARGUMENTS:
 *     pUser    - Keep user profile that wants to find suggest friends
 *     pSuggest - Keep all suggest friend profiles
 */
void _randomFriend(USER_T *pUser, USER_T **pSuggest)
    {
    int i = 0;                   /* For loop */
    int bOk = 1;
    USER_T *pRandomUser = randomFriendHash();  /* Keep data of user that is taken a random */
    /* Both mail of user that is taking a random and user are not the same */
    if ((strcasecmp(pRandomUser->mail, pUser->mail) == 0)
         || (findFriend(pUser->pHeadF, pRandomUser->mail) != NULL))
        bOk = 0;
    /* Find pending user of user that we want in linked list of pending request
     * of pending user that is taken a random */
    else if (findFriend(pRandomUser->pHeadP, pUser->mail) != NULL)
        bOk = 0;
    /* Find pending user of random user in linked list of pending request of
     * pending user that we want to find suggest friends */
    else if (findFriend(pUser->pHeadP, pRandomUser->mail) != NULL)
        bOk = 0;
    if (amountSuggestF > 0)
        { /* There are friend in 'pSuggest' */
        for (i = 0; i < MAXSUGGEST, i < amountSuggestF; i++)
            {
            /* Both random user and user in 'pSuggest' are the same */
            if (strcasecmp(pRandomUser->mail, pSuggest[i]->mail) == 0)
                bOk = 0;
            }
        }
    if (bOk)
        {
        pSuggest[amountSuggestF] = pRandomUser;
        amountSuggestF += 1;
        }
    return;
    }

/**************************** PUBLIC FUNCTION ********************************/

/* Find friend from linked list of friend which the key is E-mail.
 * Arguments:
 *   pHead - Head node of linked list.
 *   pFind - E-mail that we want to find.
 * If found, return address of linked list node back. If not found, Return NULL.
 */
FRIENDLIST_T* findFriend(FRIENDLIST_T *pHead, char *pFind)
    {
    USER_T *pUser = NULL;               /* Data of user */
    FRIENDLIST_T *pCurrent = pHead;     /* Current node of linked list */
    while (pCurrent != NULL)
        {
        pUser = pCurrent -> pData;
        /* Compare E-mail that we want and E-mail in data */
        if (strcasecmp(pUser->mail, pFind) == 0)
            return pCurrent;
        else
            pCurrent = pCurrent->pNext;
        }
    return NULL; /* Otherwise, can't find data */
    }

/* Add new node to head node of linked list of friend.
 * This function can use with pending friend request.
 * Argument:
 *      pHead - Head node of linked list.
 * Return 1, if success.
 * Return -1, If can't allocate memory.
 * Return 0, if pAdd is NULL.
 */
int pushFriend(FRIENDLIST_T **pHead, USER_T *pAdd)
    {
    FRIENDLIST_T *pNew = NULL;      /* New linked list */
    pNew = (FRIENDLIST_T*) calloc(1, sizeof(FRIENDLIST_T));
    if(pNew == NULL)    /* Can't allocate memory. */
        return -1;
    /* If there isn't any data, return 0. Check prevent error. */
    else if (pAdd == NULL)
        {
        free(pNew);
        return 0;
        }
    else    /* Otherwise, can add data into linked list */
        {
        pNew->pData = pAdd;
        if (*pHead != NULL)
            pNew->pNext = *pHead;
        else
            pNew->pNext = NULL;
        *pHead = pNew;
        return 1;
        }
    }

/* Pop head node of linked list of friend and free node.
 * This function usually uses in pending request.
 * Argument:
 *      pHead - Head node of linked list.
 * Return data in head node.
 * If head node doesn't have any data, Return NULL.
 */
USER_T* popFriend(FRIENDLIST_T **pHead)
    {
    FRIENDLIST_T *pTemp = *pHead;       /* Temporary linked list */
    USER_T *pReturn = NULL;             /* Data that return back */
    /* If there isn't any data, return NULL */
    if (pTemp == NULL)
        return NULL;
    /* If next node exist, set next node */
    else if(pTemp->pNext != NULL)
        *pHead = pTemp->pNext;
    else    /* Otherwise, not have next node */
        *pHead = NULL;
    pReturn = pTemp->pData; 
    free(pTemp);
    return pReturn;
    }

/* See data of head node of linked list. But doesn't free node.
 * This function usually uses in pending request.
 * Argument:
 *      pHead - Head node of linked list.
 * Return data in head node.
 * If head node doesn't have any data, Return NULL.
 */
USER_T* peekFriend(FRIENDLIST_T *pHead)
    {
    USER_T *pReturn = NULL;             /* Data that return back */
    if (pHead == NULL)  /* If head node is NNULL, return NULL */
        pReturn = NULL;
    else if (pHead != NULL) /* If not NULL return data of head node */
        pReturn = pHead->pData; 
    return pReturn;
    }

/* Count how many friend in linked list
 * This function can use with pending friend request.
 * Argument:
 *      pHead - Head node of linked list.
 * Return amount of data in linked list.
 */
int countFriend(FRIENDLIST_T *pHead)
    {
    FRIENDLIST_T *pCurrent = pHead;    /* Current node in linked list */
    int count = 0;                     /* Count how many friend */
    while(pCurrent != NULL)
        {
        count++;
        pCurrent = pCurrent->pNext;
        }
    return count;
    }

/* Delete friend node that we want to remove from linked list.
 * Arguments:
 *      pHead - Head node of linked list.
 *      pDel - User that want to delete node of linked list.
 * Return 1, If delete node success.
 * Return 0, If can't found node in linked list.
 */
int deleteFriend(FRIENDLIST_T **pHead, USER_T *pDel)
    {
    FRIENDLIST_T *pPrevious = NULL; /* Previous node */
    FRIENDLIST_T *pFind = *pHead;   /* Node that we want to find */
    if (*pHead == NULL)  /* If head node is NULL, go back */
        return 0;
    /* If node that we want to delete is head node */
    else if (pFind -> pData == pDel)
        {
        if(pFind -> pNext != NULL)
            (*pHead) = pFind -> pNext;
        else
            (*pHead) = NULL;
        free (pFind);
        return 1;
        }
    else    /* Else, node that we want to delete isn't head node */
        {
        pPrevious = pFind;
        pFind = pFind->pNext;
        }
    while (pFind != NULL)   /* Loop find each node */
        {
        if (pFind->pData == pDel)
            {
            /* Node that we want to delete is in the middle */
            if (pFind -> pNext != NULL)
                pPrevious->pNext = pFind->pNext;
            else /* Node that we want to delete is tail */
                pPrevious = NULL;
            free (pFind);
            return 1;
            }
        pPrevious = pFind;
        pFind = pFind->pNext;
        }
    /* Otherwise, it doesn't found node that want to delete. */
    return 0;
    }

/* Write friend relation and pending request into relation file.
 * Arguments:
 *      pData - Data of user that want to write.
 *      pFile - File that want to write.
 */
void writeFriend(USER_T *pData, FILE *pFile)
    {
    char tag[][LEN] = {"USER", "FRIEND", "PENDING"};    /* Tag in front of data */
    char mail[LEN] = {0};                               /* Mail of user */
    /* Check that friend linked list or pending request aren't NULL
     * and write down mail into file. */
    if ((pData->pHeadF != NULL) || (pData->pHeadP != NULL))
        {
        strcpy(mail, pData->mail);
        fprintf(pFile, "%s %s\n", tag[0], mail);
        }
    /* Write friend relation into file */
    if(pData->pHeadF != NULL)
        _writeFriend(pData->pHeadF, pFile, tag[1]);
    /* Write pending request into file */
    if(pData->pHeadP != NULL)
        _writeFriend(pData->pHeadP, pFile, tag[2]);
    }
    
/* Find friend of friends' user that we want by the maximum of users
 * that is suggested to user is 3.
 * Arguments:
 *     pUser    - Keep data that we want to find friend of friend
 *     pSuggest - Keep friend of friend of user that we want
 * Return 0, if that user does not have friends.
 * Return 1, if there is one friend.
 * Return 2, if there are two friends.
 * Return 3, if there are three friends.
 */
USER_T** findSuggestFriend(USER_T *pUser, int *pSuggestF)
    {
    int bOk = 1;
    int i = 0;                               /* Count loop */
    int j = 0;                               /* Count loop */
    FRIENDLIST_T *pUserF = pUser->pHeadF;    /* Linked list of friends' user */
    FRIENDLIST_T *pFriendF = NULL;           /* Linked list of friend of friend */
    if (pUserF != NULL)
        { /* If that user has friends */
        USER_T *pTmp = pUserF->pData;        /* Keep structure temporary */
        FRIENDLIST_T *pHeadF = pTmp->pHeadF; /* Head linked list of friends' user */
        pFriendF = pHeadF;     /* Linked list of friend of friend */
        }
    USER_T **pSuggest = (USER_T**) calloc(MAXSUGGEST, sizeof(USER_T*));
    if (pSuggest == NULL)
        exit(0);
    amountSuggestF = 0;
    while ((pUserF != NULL) && (amountSuggestF != MAXSUGGEST))
        { /* If that user has friends */
        _findFOF(pUser, pUserF, pFriendF, pSuggest);
        pUserF = pUserF->pNext;
        }
    srand(time(0));
    while ((j != MAXSUGGEST + 3) && (amountSuggestF != MAXSUGGEST))
        { /* If we cannot find 2 suggest friends */ 
        _randomFriend(pUser, pSuggest);
        j++;
        }
    *pSuggestF = amountSuggestF;
    return pSuggest;
    }