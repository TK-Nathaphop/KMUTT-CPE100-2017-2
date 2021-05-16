/******************************************************************************
 *
 * controlBinaryTree.c
 *
 *      Implementary of AVL Binary tree. It can adjust it self to AVL Balance
 *      Tree. All function in file have a key is E-mail of user.
 *  
 *      Created by Nathaphop Sundarabhogin ID 60070503420
 *      16 April 2018
 *
 *****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "simpleFacebook.h"
#include "abstractStatus.h"
#include "abstractGraph.h"

/* Enum for type of unbalance tree kinds */
typedef enum
    {
    BALANCE = 0,   /* Tree is in balance */
    UNBAL_LL,      /* Left of Left */
    UNBAL_RR,      /* Right of Right */
    UNBAL_LR,      /* Left of Right */
    UNBAL_RL       /* Right of Left */
    }UNBAL_T;

/***************************** LOCAL FUNCTION ********************************/

/* LOCAL FUNCTION.
 * Get height of left node and right node, then difference right node and left node
 * (Height Right - Height Left). If left/right node is NULL, it equal to 0.
 * Argument:
 *      pNode - Node that we want to compare
 * Return a difference of right node and left node (Height Right - Height Left).
 */
int _compareHeight(USERTREE_T *pNode)
    {
    int leftHeight = 0;    /* height of left node */
    int rightHeight = 0;   /* height of right node */
    /* If left node is NULL, set to 0 */
    if (pNode->pLeft == NULL)
        {
        leftHeight = 0;
        }
    else if (pNode->pLeft != NULL)
        {
        leftHeight = pNode->pLeft->height;
        }
    /* If right node is NULL, set to 0 */
    if(pNode->pRight == NULL)
        {
        rightHeight = 0;
        }
    else if (pNode->pRight != NULL)
        {
        rightHeight = pNode->pRight->height;
        }
    return rightHeight - leftHeight;
    }

/* LOCAL FUNCTION.
 * Decide the height of node to add height.
 * Find out height of left and right node
 * which is greather than and add one for height of node
 * Argument:
 *      pNode - Node that we add a new height
 */
void _addHeight(USERTREE_T *pNode)
    {
    /* height of left node greather than right node */
    if (_compareHeight(pNode) < 0)
        pNode->height = (pNode->pLeft->height) + 1;
    /* height of right node greather than left node */
    else if(_compareHeight(pNode) > 0)
        pNode->height = (pNode->pRight->height) + 1;
    else /* Both are equal */
        {
        /* Decide to use height of left node or right node */
        if (pNode->pRight != NULL)
            pNode->height = (pNode->pRight->height) + 1;
        else if (pNode->pLeft != NULL)
            pNode->height = (pNode->pLeft->height) + 1;
        /* Otherwise, it's both NULL or leaf node */
        else
            pNode->height = 1;
        }
    }

/* LOCAL FUNCTION.
 * Find out what type of tree that are not unbalance.
 * Argument:
 *      pNode - Node that we consider
 * Return different type of tree that balance.
 */
UNBAL_T _unbalanceType(USERTREE_T *pNode)
    {
    UNBAL_T type = BALANCE;                  /* Type of rotation */
    USERTREE_T *pTemp = NULL;                /* Temporary node */
    int balFactor = _compareHeight(pNode);   /* Balance factor */
    /* Height of left node is greather than height of right node. */
    if (balFactor < -1)
        {
        pTemp = pNode->pLeft;
        /* Find out it's unbalance 'left of left' or 'right of left' */
        if (_compareHeight(pTemp) < 0)
            type = UNBAL_LL;
        else
            type = UNBAL_RL;
        }
    /* Height of right node is greather than height of left node. */
    else if (balFactor > 1)
        {
        pTemp = pNode->pRight;
        /* Find out it's unbalance 'right of right' or 'leftt of right' */
        if (_compareHeight(pTemp) > 0)
            type = UNBAL_RR;
        else
            type = UNBAL_LR;
        }
    return type;
    }

/* LOCAL FUNCTION.
 * Rotate unbalance tree to the left
 * Argument:
 *      pNode - Node that we consider.
 * Return node after rotate.
 */
USERTREE_T* _rotateLeft(USERTREE_T *pNode)
    {
    USERTREE_T *pRNode = pNode->pRight;  /* Node that we want to rotate */
    if (pRNode->pLeft != NULL)
        pNode->pRight = pRNode->pLeft;
    else
        pNode->pRight = NULL;
    pRNode->pLeft = pNode;
    return pRNode;
    }

/* LOCAL FUNCTION.
 * Rotate unbalance tree to the right
 * Argument:
 *      pNode - Node that we consider.
 * Return node after rotate.
 */
USERTREE_T* _rotateRight(USERTREE_T *pNode)
    {
    USERTREE_T *pLNode = pNode->pLeft;  /* Node that we want to rotate. */
    if (pLNode->pRight != NULL)
        pNode->pLeft = pLNode->pRight;
    else
        pNode->pLeft = NULL;
    pLNode->pRight = pNode;
    return pLNode;
    }

/* LOCAL FUNCTION.
 * Update height of sub tree from bottom to current node.
 * Argument:
 *      pCurrent - Current node that we we to update height.
 */
void _updateHeight(USERTREE_T *pCurrent)
    {
    /* traverse post order */
    if (pCurrent->pLeft != NULL)
        _updateHeight(pCurrent->pLeft);
    if (pCurrent->pRight != NULL)
        _updateHeight(pCurrent->pRight);
    /* Plus one height in current node consider from height of left and right. */
    _addHeight(pCurrent);
    return;
    }

/* LOCAL FUNCTION.
 * Find out type of unbalance tree and rotate tree to AVL Balance Tree.
 * If it's already balance don't do anything.
 * Argument:
 *      pNode - Node that we want to make it balance.
 * Return new node after make it balance.
 */
USERTREE_T* _balanceTree(USERTREE_T *pNode)
    {
    UNBAL_T type = _unbalanceType(pNode);   /* Type of unbalance tree */
    USERTREE_T *pReturn = NULL;             /* Node that we return after balance */
    if (type == BALANCE)
        return pNode;
    /* Unbalance tree Left of Left */
    else if (type == UNBAL_LL)
        pReturn = _rotateRight(pNode);
    /* Unbalance tree Right of Right */
    else if (type == UNBAL_RR)
        pReturn = _rotateLeft(pNode);
    /* Unbalance tree Right of Left */
    else if (type == UNBAL_RL)
        {
        /* Rotate 'Left node' to the left, then rotate current node the right. */
        pNode->pLeft = _rotateLeft(pNode->pLeft);
        pReturn = _rotateRight(pNode);    
        }
    /* Unbalance tree Left of Right */
    else if (type == UNBAL_LR)
        {
        /* Rotate 'Right node' to the Left, then rotate current node to the left. */
        pNode->pRight = _rotateRight(pNode->pRight);
        pReturn = _rotateLeft(pNode);    
        }
    _updateHeight(pReturn);
    return pReturn;
    }

/* LOCAL FUNCTION .
 * Add new node to tree, update height of each node and make tree to balance Tree.
 * Arguments:
 *      pCurrent - Current node of tree.
 *      pNew - New node of tree.
 * Return subtree after make it to balance tree.
 */
USERTREE_T* _insertBinaryTree(USERTREE_T *pCurrent, USERTREE_T *pNew)
    {
    USER_T *pCurData = pCurrent->pData;  /* Data of current node */
    USER_T *pNewData = pNew->pData;      /* Data of new node */
    /* Set height of new data to 1 */
    pNew->height = 1;
    /* Insert new data by using binary sorting tree */
    if (strcasecmp(pNewData->mail,pCurData->mail) > 0)
        {
        if (pCurrent->pRight != NULL)
            pCurrent -> pRight = _insertBinaryTree(pCurrent->pRight, pNew);
        else if (pCurrent->pRight == NULL)
            pCurrent->pRight = pNew;
        }
    else if (strcasecmp(pNewData->mail,pCurData->mail) < 0)
        {
        if (pCurrent->pLeft != NULL)
            pCurrent -> pLeft = _insertBinaryTree(pCurrent->pLeft, pNew);
        else if (pCurrent->pLeft == NULL)
            pCurrent->pLeft = pNew;
        }
    /* Plus one height in current node consider from left and right node */
    _addHeight(pCurrent);
    /* Return tree node after set to balance tree */
    return _balanceTree(pCurrent);
    }

/**************************** PUBLIC FUNCTION ********************************/

/* Free all data in tree.
 * Argument:
 *      pDelete - Subtree/node that we want to delete.
 */
void freeTree(USERTREE_T *pDelete)
    {
    USER_T* pData = pDelete->pData;
    /* traverse post order */
    if (pDelete->pLeft != NULL)
        freeTree(pDelete->pLeft);
    if (pDelete->pRight != NULL)
        freeTree(pDelete->pRight);
    freeStatus(pData->pHeadS);
    freeFriend(pData);
    free(pData);
    free(pDelete);
    }


/* Find data that we want from tree by using key (which key is e-mail).
 * Arguments:
 *      pCurrent - Current node of tree
 *      key - Key that we want to find
 * Return tree node that we want. 
 */
USERTREE_T* findDataTree(USERTREE_T *pCurrent, char* key)
    {
    printf("NULL EIEI\n");
    USER_T *pCurData = NULL;    /* Data of current node */
    USERTREE_T *pFound = NULL;  /* Tree node that we found */
    /* If current node is NULL, return NULL immediately for prevent bug */
    if (pCurrent == NULL)
        {
        return NULL;
        }
    else
        {
        printf("NOT NULL EIEI\n");
        pCurData = pCurrent->pData;
        /* Compare and traversal in tree to find data. */
        if (strcasecmp(key,pCurData->mail) > 0)
            pFound = findDataTree(pCurrent->pRight, key);
        else if (strcasecmp(key,pCurData->mail) < 0)
            pFound = findDataTree(pCurrent->pLeft, key);
        else if (strcasecmp(key,pCurData->mail) == 0)
            pFound = pCurrent;
        return pFound;
        }
    }

/* Random get data in tree. Usually used for suggest friend.
 * Argument:
 *      pUser - Keep node of user that we want to start to take a random
 * Return the data that we random in tree.
 */
USER_T* randomFriendTree(USERTREE_T *pUser)
    {
    int num = 0;    /* Keep number that random */
    /* Random number.
     * If it's '0', go to left node.
     * If it's '1', select current node.
     * If it's '2', go to right node.
     */
    num = rand() % 3;
    if (num == 0)               /* '0', Go left node */
        {
        if (pUser->pLeft != NULL)
            return randomFriendTree(pUser->pLeft);
        else    /* If left node is NULL, select current node immediately */
            return pUser->pData;
        }
    else if (num == 1)          /* '1', Select Current node */
        return pUser->pData;
    else if (num == 2)          /* '2', Go right node */
        {
        if (pUser->pRight != NULL)
            return randomFriendTree(pUser->pRight);
        else    /* If right node is NULL, select current node immediately */
            return pUser->pData;
        }
    }
    
/* Add new node to tree.
 * Arguments:
 *      pRoot - Root node of tree
 *      pNew - New tree that want to add
 * Return 1 for success. Return 0 for same data.
 */
int addDataTree(USERTREE_T **pRoot, USERTREE_T *pNew)
    {
    printf("BEFORE FIND\n");
    /* There is same data, return 0. */
    if(findDataTree(*pRoot, pNew->pData->mail) != NULL)
        return 0;
    printf("After FIND\n");
    /* Root node is NULL, set new data to root node. */
    if(*pRoot == NULL)
        {
        *pRoot = pNew;
        pNew->height = 1;
        }
    else    /* Otherwise send to insert */
        *pRoot = _insertBinaryTree(*pRoot, pNew);
    return 1;
    }

/* Traverse a tree (post-order traversal).
 * Write all of friend in tree to relation file.
 * and free all of data.
 * ARGUMENTS: pCurrent - Node that we want to write
 *            pFile    - File that we want to write
 */
void writeFriendTree(USERTREE_T *pCurrent, FILE *pFile)
    {
    USER_T* pData = NULL;    /* Data in tree node */
    if (pCurrent->pLeft != NULL)
        writeFriendTree(pCurrent->pLeft, pFile);
    if (pCurrent->pRight != NULL)
        writeFriendTree(pCurrent->pRight, pFile);
    pData = pCurrent->pData;
    writeFriend(pData, pFile);
    pData->pHeadF = NULL;
    return;
    }

/* Traverse a tree (post-order traversal).
 * Write all of status and comment in tree to status file.
 * ARGUMENTS: pCurrent - Node that we want to write
 *            pFile    - File that we want to write
 */
void writeStatusTree(USERTREE_T *pCurrent, FILE *pFile)
    {
    USER_T* pData = NULL;    /* Data in tree node */
    if (pCurrent->pLeft != NULL)
        writeStatusTree(pCurrent->pLeft, pFile);
    if (pCurrent->pRight != NULL)
        writeStatusTree(pCurrent->pRight, pFile);
    pData = pCurrent->pData;
    writeStatus(pData, pFile);
    pData->pHeadS = NULL;
    pData->pTailS = NULL;
    return;
    }

/* Traverse a tree (post-order traversal).
 * Write all of profile in tree to profile file.
 * ARGUMENTS: pCurrent - Node that wew want to write
 *            pFile    - File that we want to write
 */
void writeProfileTree(USERTREE_T *pCurrent, FILE *pFile)
    {
    USER_T* pData = NULL;    /* Data in tree node */
    if (pCurrent->pLeft != NULL)
        writeProfileTree(pCurrent->pLeft, pFile);
    if (pCurrent->pRight != NULL)
        writeProfileTree(pCurrent->pRight, pFile);
    pData = pCurrent->pData;
    /* Set all pointer in data to NULL */
    pData->pHeadF = NULL;
    pData->pHeadP = NULL;
    pData->pHeadS = NULL;
    pData->pTailS = NULL;
    fwrite(pData, sizeof(USER_T), 1, pFile);
    free(pData);
    free(pCurrent);
    return;
    }