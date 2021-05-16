/******************************************************************************
 *
 * abstractLinkedList.c
 *
 * Control data structure that are related to linked list.
 *
 *      Created by Chawakorn Boonrin (Bright)    ID : 3415
 *      17 APRIL 2018
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "simpleFacebook.h"

/***************************** LOCAL FUNCTION ********************************/

/* Free all FRIENDLIST_T structure that keep in linked list.
 * Arguments:
 *      pHead - Head node of friend linked list that we want to delete
 */
void _freeFriendList(FRIENDLIST_T *pHead)
    {
    FRIENDLIST_T *pTemp = pHead;    /* Temporary node */
    FRIENDLIST_T *pDel = pHead;     /* Node that we want to delete */
    while (pDel != NULL)
        {
        pTemp = pDel -> pNext;
        free(pDel);
        pDel = pTemp;
        }
    }

/* Loop write all of tag and data in linked list of friend into file
 * Arguments:
 *      pHead - Head node that linked list
 *      pFile - File that we want to write down
 *      tag - Tag of data that we want to write in front
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
        if(pDelete != NULL)
            free(pDelete);
        }
    }

/**************************** PUBLIC FUNCTION ********************************/

/* Find friend from linked list of friend. The key is E-mail.
 * Arguments:
 *   pHead - Head node of linked list.
 *   pFind - Node that we want to find by use Email of user.
 * If found, return address of node back. If not found, Return NULL.
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
 * Arguments:
 *    pHead - Head node of linked list.
 * Return 1, if success. Return -1, If can't allocate memory.
 * Return 0, if pAdd is NULL.
 */
int pushFriend(FRIENDLIST_T **pHead, USER_T *pAdd)
    {
    FRIENDLIST_T *pNew = NULL;      /* New linked list */
    pNew = (FRIENDLIST_T*) calloc(1, sizeof(FRIENDLIST_T));
    if(pNew == NULL)    /* Can't allocate */
        return -1;
    else if (pAdd == NULL)  /* If there isn't any data, return 0 */
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
 * Arguments:
 *      pHead - Head node of linked list.
 * Return data in node. If 'pHead' doesn't have any data, Return NULL.
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

/* See data head node of friend. But not free linked list
 * This function usually uses in pending request.
 * Arguments:
 *      pHead - Head node of linked list.
 * Return data in node. If 'pHead' doesn't have any data, Return NULL.
 */
USER_T* peekFriend(FRIENDLIST_T *pHead)
    {
    USER_T *pReturn = NULL;             /* Data that return back */
    if (pHead == NULL)  /* If head node is Null, return Null */
        pReturn = NULL;
    else if (pHead != NULL) /* If not NULL return of head data */
        pReturn = pHead->pData; 
    return pReturn;
    }

/* Count how many friend in linked list
 * This function can use with pending friend request.
 * Arguments:
 *      pHead - Head node of linked list.
 * Return data in node. If 'pHead' doesn't have any data, Return NULL.
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
 *   pHead - Head node of linked list
 *   pDel - User that want to delete node of linked list of friend.
 * Return 1, If delete node success. Return 0, If can't found node.
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
    else    /* Else, Node that we want to delete not head node */
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
    /* Otherwise, it not found node that want delete */
    return 0;
    }

/* Write friend relation and pending request into relation file
 * Arguments:
 *      pData - Data of user that want to write
 *      pFile - File that want to write
 */
void writeFriend(USER_T *pData, FILE *pFile)
    {
    char tag[][LEN] = {"USER", "FRIEND", "PENDING"};
    char mail[LEN] = {0};
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

/* Free linked list of friend and linked list of pending requst in user.
 * Argument:
 *      pData - Data that we want to delete friend linked list.
 */
void freeFriend(USER_T* pData)
    {
    _freeFriendList(pData->pHeadF);
    _freeFriendList(pData->pHeadP);
    return;
    }