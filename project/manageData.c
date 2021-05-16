/******************************************************************************
 *
 *  manageData.c
 *
 *      Control all data. This part module manage all of data structure to
 *      working together. There are AVL Binary tree, Hash table, Graph,
 *      Linked list of friend, Linked list of status and comment.
 *  
 *      Created by Nathaphop Sundarabhogin    ID : 3420
 *      16 April 2018
 *
 ******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleFacebook.h"
#include "validate.h"
#include "abstractTree.h"
#include "abstractHash.h"
#include "abstractGraph.h"
#include "abstractStatus.h"

/* User that login into system */
static USER_T *_userLogin = NULL;

/* Get E-mail and password. Then send E-mail to find data.
 * If found, check password correct or not.
 * Arguments:
 *      mail - E-mail that user input
 *      password - Password that want to check with E-mail
 * Return 1, if found user data and password correct.
 * Return 0, if found user data but password doesn't correct.
 * Return -1, if Not found user data. 
 */
int signIn(char *pMail, char *pPassword)
    {
    USER_T *pUser = hashTableLookup(pMail); /* User after find */
    /* Don't found user with that E-mail */
    if (pUser == NULL)
        return -1;
    /* Found user and password correct */
    else if (strcasecmp(pPassword, pUser->password) == 0)
        {
        _userLogin = pUser;
        return 1;
        }
    /* Found user but password not correct */
    else
        return 0;
    }

/* Used for read data from file.
 * Set system like user login to add data.
 * Argument:
 *      pUser - User that want to access sign in
 */
void accessSignIn(USER_T *pUser)
    {
    _userLogin = pUser;
    }

/* This function working with function in controlStatus.c.
 * It can Initial status, get status, go to next status
 * depends on select that input
 * Arguments:
 *      select - select what do you want to do about status
 *              1 for initial status, 2 for get status, 3 for go next status
 *      status - status that we want to return
 * Return 1, for success. Return 0, if don't have any friend or status to display.
 * Return -1, if can't allocate memory.
 */
int statusMenu(int select, STATUS_T **pStatus)
    {
    int retVal = 0;     /* Return value */
    if (select == 1)        /* Intial status to get status in data */
        {
        retVal = initialStatus(_userLogin);
        }
    else if (select == 2)   /* Get status from database */
        {
        *pStatus = getStatus();
        if(*pStatus == NULL)    /* Don't have any status */
            retVal = 0;
        else
            retVal = 1;
        }
    else if (select == 3)   /* Go to get next status */
        {
        nextStatus();
        retVal = 1;
        }
    else if (select == 4)   /* Clear all status */
        clearStatus();
    return retVal;
    }


/* Add user that want to be friend to friend pending request.
 * Argument:
 *      pPending - User that want to add to be pending request.
 * Return 2, if pending user have been add friend to user already.
 * Return 1, add to pending request success.
 * Return 0, if Both are friend already or waited for accept friend.
 * Return -1, if can't allocate memory.
 */
int addPending(USER_T* pPending)
    {
    /* User that want to send pending request and user login are same */
    if (_userLogin == pPending)
        return 3;
    /* Find pending user in linked list of pending request of user */
    else if (findFriend(_userLogin->pHeadP, pPending->mail) != NULL)
        return 2;
    /* Find pending user in linked list of user's friend */
    else if (findFriend(_userLogin->pHeadF, pPending->mail) != NULL)
        return 0;
    /* Find user in linked list of pending request of pending user. */
    else if (findFriend(pPending->pHeadP, _userLogin->mail) != NULL)
        return 0;
    else    /* Otherwise, they're not friend */
        return pushFriend(&pPending->pHeadP, _userLogin);
    }

/* Delete user that we don't want to be friend in friend list or remove from
 * pending request.
 * Argument:
 *      pAdd - User that want to add to be friend
 * Return 4, if user that want to unfriend is sent pending request by user login.
 * Return 3, if user that want to unfriend is same as user login.
 * Return 2, if user that want to unfriend is in user's pending request.
 * Return 1, if delete success.
 * Return 0, if they're not friend.
 */
int unFriend(USER_T* pDel)
    {
    /* User that want to delete and user login are same */
    if (_userLogin == pDel)
        return 3;
    /* Find user that want to delete in user login pending request */
    else if (findFriend(_userLogin -> pHeadP, pDel->mail) != NULL)
        return 2;
    /* Delete from linked list of friend of user */
    else if (deleteFriend(&_userLogin -> pHeadF, pDel) == 1)
        {
        deleteFriend(&pDel->pHeadF, _userLogin);
        pDel->friends--;
        _userLogin->friends--;
        return 1;
        }
    else if (deleteFriend(&pDel -> pHeadP, _userLogin) == 1)
        return 4;
    else
        return 0;
    }

/* Add user that want to be friend into friend list of user that login.
 * Argument:
 *      pAdd - User that want to add to be friend.
 * Return 1, if success. Return 0, if pAdd and user that login are already friend.
 * Return -1, if can't allocate memory.
 */
int addFriend(USER_T* pAdd)
    {
    int retVal = 1; /* Return value */
    /* Add 'pAdd' into list of friend of user. */
    if(findFriend(_userLogin->pHeadF, pAdd->mail)== NULL)
        {
        retVal = pushFriend(&_userLogin->pHeadF, pAdd);
        _userLogin->friends++;
        }
    else
        retVal = 0;
    if (retVal == -1)   /* Can't allocate memory. */
        return retVal;
    /* Add user into list of friend of friend. */
    if(findFriend(pAdd->pHeadF, _userLogin->mail)== NULL)
        {
        retVal = pushFriend(&pAdd->pHeadF, _userLogin);
        pAdd->friends++;
        }
    else
        retVal = 0;
    if (retVal == -1)   /* Can't allocate memory. */
        return retVal;
    return retVal;
    }

/* Update a new status into user data
 * Arguments:
 *      pText - Text that want to update
 *      date - Current time that user update
 *      select - Select to add to head or tail
 *               1 - for add to head (the newest status)
 *               2 - for add to tail (the oldest status)
 * Return new status back. But if can't allocate memory return NULL.
 */
STATUS_T* updateStatus(char *pText, int date[], int select)
    {
    STATUS_T *pNew = (STATUS_T*)calloc(1, sizeof(STATUS_T));
    if(pNew == NULL)
        return NULL;
    strcpy(pNew->text, pText);
    memcpy(pNew->date, date, sizeof(pNew->date));
    pNew->owner = _userLogin;
    addStatus(_userLogin, pNew, select);
    return pNew;
    }

/* Update a new status into user data
 * Arguments:
 *      pText - Text that want to update
 *      date - Current time that user update
 * Return new status back. But if can't allocate memory return NULL.
 */
COMMENT_T* updateComment(STATUS_T *pStatus, char *pText, int date[])
    {
    COMMENT_T *pNew = (COMMENT_T*)calloc(1, sizeof(COMMENT_T));
    if(pNew == NULL)
        return NULL;
    strcpy(pNew->text, pText);
    memcpy(pNew->date, date, sizeof(pNew->date));
    pNew->owner = _userLogin;
    addComment(pStatus, pNew);
    return pNew;
    }

/* See the data in pending linked list
 * Return user that add pending request to user and amount of friend pending
 * Argument:
 *      count - Return count how many friend
 * Return data in the first node of pending linked list
 */
USER_T* lookPending(int *count)
    {
    *count = countFriend(_userLogin->pHeadP);
    return peekFriend(_userLogin->pHeadP);
    }

/* Accept the latest pending request to be friend of user
 * Return 1 if success. Return 0 if not have any pending request
 * Return -1 if can't allocate memory
 */
int acceptFriendPending()
    {
    int retVal = 0;     /* Return value */
    USER_T *pAdd = popFriend(&_userLogin->pHeadP);
    if(pAdd == NULL)
        return 0;
    return addFriend(pAdd);
    }

/* Deny the latest pending request to be friend of user.
 * Return 1 if success. Return 0 if not have any pending request
 */
int denyFriendPending()
    {
    int retVal = 0;     /* Return value */
    USER_T *pAdd = popFriend(&_userLogin->pHeadP);
    if(pAdd == NULL)
        return 0;
    else
        return 1;
    }

/* Find data from hash table.
 * Argument:
 *      pFind - E-mail of user that we want to find
 * Return address of user that we find.
 */
USER_T* findData(char *pFind)
    {
    return hashTableLookup(pFind);
    }

/* Add data to hash table. If there is some collision it'll keep in tree
 * Argument:
 *      pNew - New data that we want to add.
  * Return 1 for success. Return 0 for same data. Return -1 for can't allocate.
 */
int addData(USER_T *pNew)
    {
    return hashTableInsert(pNew);
    }

/* Return address of user that login back.
 */
USER_T* getUser()
    {
    return _userLogin;
    }

/* Write data into file
 * Arguments:
 *      pFile - File that we want to write
 *      select - File that we select to write
 */
void writeFile(FILE *pFile, int select)
    {
    int i = 0;
    int max = hashTableBucketSize();
    USERTREE_T* pRoot = NULL;
    void (*function)(USERTREE_T *pCurrent, FILE *pFile) = NULL;
    if (select == 1)      /* Write Profile file */
        function = &writeProfileTree;
    else if (select == 2) /* Write relation file */
        function = &writeFriendTree;
    else if (select == 3) /* Write Status file */
        function = &writeStatusTree;
    /* Loop write data */
    for(i = 0; i < max; i++)
        {
        pRoot = hashTableData(i);
        if(pRoot != NULL)
            function(pRoot, pFile);
        }
    }

/* User log out from system. Set '_userLogin' to NULL.
 */
void signOut()
    {
    _userLogin = NULL;
    }

/* Find suggest friend of user that we want.
 * Argument:
 *      pSuggestF - Amount of suggest friend
 * Return suggest friend of user back.
 */
USER_T** suggestFriend(int *pSuggestF)
    {
    return findSuggestFriend(_userLogin, pSuggestF);
    }