/******************************************************************************
 *
 * controlStatus.c
 *
 *      Implementary of status and comment.
 *      Manage structure of linked list of status and linked list of comment.
 *      Keep status that will show to user in this file.
 *
 *      Created by Natthawat Tungruethaipak (Tong)    ID : 60070503426
 *      17 APRIL 2018
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "simpleFacebook.h"

static STATUS_T ** _status = NULL;  /* Status that we want to show to user */
static int _arrayBox = 0;           /* Amount of friend */

/***************************** LOCAL FUNCTION ********************************/

/* LOCAL FUNCTION.
 * This function swap position of status in array.
 * Arguments:
 *      status1, status2 - Status that we want to swap
 */         
void _swap(STATUS_T** status1, STATUS_T** status2)
    {
    STATUS_T* temp = *status1;  /* Temporary status */
    *status1 = *status2;
    *status2 = temp;
    }

/* LOCAL FUNCTION.
 * Compare between 2 dates of status.
 * ARGUMENT:
 *     date1 - Status of first date that want to compare.
 *     date2 - Status of second date that want to compare.
 * Return 0 - If first date is later than or equal to second date.
 * Return 1 - If first date is ealier than second date.
 */
int _dateStatusCpr(STATUS_T *date1, STATUS_T *date2)
    {
    if (date1 == NULL)
        return 1;
    else if (date2 == NULL)
        return 0;
    /* Compare which year is later or ealier. */
    else if (date1 -> date[2] > date2 -> date[2])
        return 0;
    else if (date1 -> date[2] < date2 -> date[2])
        return 1;
    /* If years are the same, Compare which month is later or ealier. */
    else if (date1 -> date[1] > date2 -> date[1])
        return 0;
    else if (date1 -> date[1] < date2 -> date[1])
        return 1;
    /* If months are the same, Compare which day is later or ealier. */
    else if (date1 -> date[0] > date2 -> date[0])
        return 0;
    else if (date1 -> date[0] < date2 -> date[0])
        return 1;
    /* If days are the same, Compare which hour is later or ealier. */
    else if (date1 -> date[3] > date2 -> date[3])
        return 0;
    else if (date1 -> date[3] < date2 -> date[3])
        return 1;
    /* If hours are the same, Compare which minutes is later or ealier. */
    else if (date1 -> date[4] > date2 -> date[4])
        return 0;
    else if (date1 -> date[4] < date2 -> date[4])
        return 1;
    return 0;   /* Otherwise, both days are the same. */
    }

/* LOCAL FUNCTION.
 * This function takes last element as pivot, places the pivot element at its
 * correct position in sorted array, and places all smaller (smaller than pivot)
 * to left of pivot and all greater elements to right of pivot.
 * Arguments:
 *      status - array of address status
 *      low - Starting index
 *      high - Ending index
 * Return number of partitioning index.
 */
int _partition(int low, int high)
    {
    STATUS_T * pivot = _status[high];    /* Pivot of array */
    int i = (low - 1);                   /* Index of smaller element */
    int j;                               /* Count loop */
    for (j = low; j <= high- 1; j++)
        {
        /* If current element is smaller than or equal to pivot */
        if (_dateStatusCpr(pivot, _status[j]))
            {
            i++; /* increment index of smaller element */
            _swap(&_status[i], &_status[j]);
            }
        }
    _swap(&_status[i + 1], &_status[high]);
    return (i + 1);
    }

/* LOCAL FUNCTION.
 * Get array of address status and starting and ending of array.
 * Then sorted it by compare with date. The lastest status will be on [0].
 * Arguments:
 *      status - array of address status
 *      low - Starting index
 *      high - Ending index
 */
void _quickSortStatus(int low, int high)
    {
    if (low < high)
        {
        int pi = _partition(low, high); /* pi is partitioning index */
        _quickSortStatus(low, pi - 1);  /* Separately sort elements before
                                            partition and after partition */
        _quickSortStatus(pi + 1, high);
        }
    }

/* Free all comment node in linked list.
 * Arguments:
 *      pHead - Head node of comment linked list that we want to delete
 */
void _freeCommentList(COMMENT_T *pHead)
    {
    COMMENT_T *pTemp = pHead;    /* Temporary node */
    COMMENT_T *pDel = pHead;     /* Node that we want to delete */
    while (pDel != NULL)
        {
        pTemp = pDel -> pNext;
        free(pDel);
        pDel = pTemp;
        }
    }

/**************************** PUBLIC FUNCTION ********************************/

/* Clear array of status and set amount of friend to 0.
 */
void clearStatus()
    {
    if(_status != NULL) /* Clear old data */
        free(_status);
    _arrayBox = 0;
    _status = NULL;
    }

/* Return the latest status back.
 * If not have status to display, return NULL.
 */
STATUS_T *getStatus()
    {
    if (_status == NULL)
        return NULL;
    else if (_status[0] == NULL)
        return NULL;
    else
       return _status[0];
    }

/* Set latest status to next status of linked list.
 * Then sorting status by date.
 */
void nextStatus()
    {
    if (_status == NULL)
        return;
    /* If status at [0] is NULL,
     * that mean display all of status already. */
    else if (_status[0] == NULL)
        clearStatus();
    else if (_status[0] != NULL)
        {
        _status[0] = _status[0] -> pNext;
        _quickSortStatus(0, (_arrayBox - 1));
        }
    }

/* Add new status into linked list status of user
 * Arguments:
 *      pUser - User that want to add a new status
 *      pNew - New status that want to add
 *      select - Select to add to head node or tail node of status
 *               1 - Add to head, 2- Add to tail
 */
void addStatus(USER_T *pUser, STATUS_T *pNew, int select)
    {
    STATUS_T *pTemp = NULL; /* Temporary status */
    if(select == 1) /* Add to head node */
        {
        pTemp = pUser->pHeadS;
        if(pUser->pHeadS == NULL)
            pUser->pTailS = pNew;
        pUser->pHeadS = pNew;
        pNew->pNext = pTemp;
        }
    else /* Add to tail node */
        {
        pTemp = pUser->pTailS;
        pUser->pTailS = pNew;
        if(pTemp != NULL)   /* Set pointer of last status to new status. */
            pTemp->pNext = pNew;
        else                /* Otherwise, that mean user doesn't have any status */
            pUser->pHeadS = pNew;
        }
    }

/* Add new comment into linked list comment of status.
 * Arguments:
 *      pUser - User that want to add a new status
 *      pNew - New status that want to add
 */
void addComment(STATUS_T* pStatus, COMMENT_T *pNew)
    {
    COMMENT_T *pTemp = pStatus->pTailC; /* Temporary comment */
    /* Add comment to tail node of comment */
    pStatus->pTailC = pNew;
    if(pTemp != NULL)   /* Set pointer of last comment to new comment. */
        pTemp->pNext = pNew;
    else    /* Otherwise, that mean user doesn't have any comment */
        pStatus->pHeadC = pNew;
    }

/* Intial array of stautus steady for display.
 * Get amount of friend and calloc array of status 
 * and get head node of status from each friend.
 * Argument:
 *      pUser - User that we want to get status from friend list
 * Return 1, when get status success.
 * Return -1, if can't calloc array.
 */  
int initialStatus(USER_T *pUser)
    {
    STATUS_T** pStatus = NULL;      /* Status that we get from friend */
    FRIENDLIST_T* pFriend = NULL;   /* Friend of user */
    USER_T *pDataF = NULL;          /* Data of friend */
    int amount = 0;                 /* Amount of status */
    int i = 0;                      /* Count loop */
    clearStatus(); /* Clear old data */  
    /* Get amount of friend from user and plus one for status of user */
    amount = (pUser -> friends) + 1; 
    pFriend = pUser->pHeadF;
    pStatus = (STATUS_T**)calloc(amount, sizeof(STATUS_T*));
    if (pStatus == NULL) /* Can't allocate memory, return -1 */
        return -1;
    pStatus[0] = pUser->pHeadS;
    /* Loop get status from each friend */
    for (i = 1; (pFriend != NULL) && (i < amount); i++)
        {
        pDataF = pFriend->pData;
        pStatus[i] = pDataF->pHeadS; /* Get head node of status */
        pFriend = pFriend->pNext;
        }
    /* Keep friend data into static memoery */
    _status = pStatus;
    _arrayBox = amount;
    _quickSortStatus(0, (_arrayBox - 1));  /* Sort status */
    return 1;
    }

/* Write status and comment into status file and free status and comment
 * Arguments:
 *      pData - Data that we want to write down status into file
 *      pFile - File that we want to write
 */
void writeStatus(USER_T *pData, FILE *pFile)
    {
    char tag[][LEN] = {"STATUS", "COMMENT", "MAIL", "DATE"}; /* Tag of data */
    char mail[LEN] = {0};                          /* Mail of user */
    char text[LONGLEN] = {0};                      /* Text of status/comment */
    STATUS_T *pCurrentS = pData->pHeadS;           /* Current Status */
    STATUS_T *pNextS = NULL;                       /* Next Status */
    COMMENT_T *pCurrentC = NULL;                   /* Current Comment */
    COMMENT_T *pNextC = NULL;                      /* Next comment  */
    USER_T *pUserC = NULL;                         /* User of comment */
    while(pCurrentS != NULL)    /* Write status into file */
        {
        strcpy(mail, pData->mail);
        strcpy(text, pCurrentS->text);
        pNextS = pCurrentS->pNext;      /* Keep next pointer of status */
        pCurrentC = pCurrentS->pHeadC;
        fprintf(pFile, "%s %s\n", tag[0], text);
        fprintf(pFile, "%s %s\n", tag[2], mail);
        fprintf(pFile, "%s %d %d %d %d %d\n", tag[3], pCurrentS->date[0],
                                            pCurrentS->date[1], pCurrentS->date[2],
                                            pCurrentS->date[3], pCurrentS->date[4]);
        while(pCurrentC != NULL)    /* Write down comment in file */
            {
            pUserC = pCurrentC->owner;
            strcpy(mail, pUserC->mail);
            strcpy(text, pCurrentC->text);
            pNextC = pCurrentC->pNext;  /* Keep next pointer of comment */
            fprintf(pFile, "%s %s\n", tag[1], text);
            fprintf(pFile, "%s %s\n", tag[2], mail);
            fprintf(pFile, "%s %d %d %d %d %d\n", tag[3], pCurrentC->date[0],
                                                pCurrentC->date[1], 
                                                pCurrentC->date[2],
                                                pCurrentC->date[3],
                                                pCurrentC->date[4]);
            free(pCurrentC);
            pCurrentC = pNextC;
            }
        free(pCurrentS);
        pCurrentS = pNextS;
        }
    }