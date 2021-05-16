/******************************************************************************
 *
 *  linkCouples.c
 *
 *      This program get a text file from terminal line and read name and gender
 *      from file. After that ask user to delete person and which persons are in
 *      couple. In the end print summary to user.
 *
 *      Nathaphop Sundarabhogin (KLA) ID 3420
 *          6 February 2018
 *
 ******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 128

typedef struct _person
    {
    char name[32];              /* Person's name */
    char gender[2];             /* Person's gender */
    struct _person *pPartner;   /* Pointer to another PERSON_T who is this
                                   person's partner. */
    struct _person *pNext;      /* Pointer to next person in the list */
    }PERSON_T;

/* This function get big error case then print error message to user and exit.
 */
void programError(int error)
    {
    if (error == 1)  /* User didn't input text file */
        {
        printf("Error: Please input an text file after run program\n");
        printf("Example: ./linkCouples inputFile.txt\n");
        }
    else if (error == 2) /* Have a problem when open file */
        {
        printf("Error: Can't open text file. Program Exit\n");
        }
    else if (error == 3) /* Have a problem to allocate new memory */
        {
        printf("Error: Can't allocate new memory. Program Exit\n");
        }
    else if (error == 4) /* User delete people until have 1 person left */
        {
        printf("Error: Have only 1 person left. Program Exit\n");
        }
    exit(0);
    }

/* Get file that want to read and address of amount. Loop read each line from
 * text file and keep each line in linked list then return address of head node
 * of linked list and amount back.
 */
PERSON_T* readFile(FILE* pFile, int *amount)
    {
    char input[LEN] = {0};      /* Get input from text file */
    PERSON_T* pHead = NULL;     /* Head node of the list */
    PERSON_T* pTail = NULL;     /* Tail of linked list */
    int count = 0;              /* Count how many people in file */
    while (fgets(input, sizeof(input), pFile) != NULL)
        {
        if (pTail == NULL) /* Read the first line */
            {
            pHead = calloc(1, sizeof(PERSON_T));
            if (pHead == NULL)
                programError(3);
            pTail = pHead;
            }
        else if ((pTail != NULL) && (pTail->pNext == NULL))
            {
            /* Calloc new structure in tail pointer */
            pTail->pNext = calloc(1,sizeof(PERSON_T));
            if (pTail->pNext == NULL)
                programError(3);
            /* Change Tail pointer to new poitner */
            pTail = pTail->pNext;
            }
        sscanf(input, "%s %s", pTail->name, pTail->gender);
        count++;
        }
    *amount = count;
    return pHead;
    }

/* Get head node of linked list and then print all of data */
void printData(PERSON_T* pHead)
    {
    PERSON_T *pCurrent = pHead;     /* Current node of the list */
    while (pCurrent != NULL)
        {
        printf("    %s %s\n", pCurrent->name, pCurrent->gender);
        pCurrent = pCurrent->pNext;
        }
    printf("\n");
    return;
    }

/* Get head node of linked list and then loop check to print all of couples.
 * If there isn't any couple, don't print anything (include title 'Couples:')
 */
void printCouple(PERSON_T* pHead)
    {
    PERSON_T* pCurrent = pHead;     /* Current node of the list */
    int check = 0;                  /* Check that there are any couple */
    for (pCurrent = pHead; pCurrent != NULL; pCurrent = pCurrent->pNext)
        {
        /* This condition forcouple and only male. */
        if ((pCurrent->pPartner != NULL) && (pCurrent->gender[0] == 'M'))
            {
            if (check == 0)   /* Print title */
                {
                printf("Couples:\n");
                check = 1;
                }
            printf("\t%s is coupled with %s\n", pCurrent->name,
                                                pCurrent->pPartner->name);
            }
        }
    return;
    }

/* Get address of name and ask user for input 2 names. If user input wrong format,
 * print error message and return 0. But if user input correct, return 1 */
int askName(char name[][LEN])
    {
    char input[LEN] = {0};          /* Get input from user. */
    char nameInput[3][LEN] = {0};   /* name that want to match in couples
                                     * [0] - Name person 1, [1] - Name person 2,
                                     * [2] - For Error case if user input more
                                     * than 2 */
    int check = 0;                  /* Keep value after 'sscanf' back. */
    printf("Enter couple: ");
    fgets(input,sizeof(input),stdin);
    /* 'sscanf' will return value in integer that could be successfully read */
    check = sscanf(input, "%s %s %s", nameInput[0], nameInput[1], nameInput[2]);
    if (check == 1)
        {
        /* If it can read only '1', that maybe user input 'done'. */
        if (strcasecmp(nameInput[0],"done") == 0)
            return 1;
        else
            return 0;
        }
    else if (check == 2) /* If read '2', return string and '2' back */
        {
        strcpy(name[0], nameInput[0]);
        strcpy(name[1], nameInput[1]);
        return 2;
        }
    else
        return 0;
    }

/* Loop get input from terminal line until user input 'Y' or 'N'. If user input
 * 'Y', return 1. But if user input 'N', return 0.
 */
int askDelete()
    {
    char input[LEN] = {0};  /* Get input from terminal line */
    while(1)
        {
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%s", input);
        if ((strlen(input) == 1) && (input[0] == 'Y' || input[0] == 'y'))
            return 1;
        if ((strlen(input) == 1) && (input[0] == 'N' || input[0] == 'n'))
            return 0;
        else
            {
            printf("Error: Please answer only 'Y' or 'N'\n");
            printf("Do you want to delete people(Y/N)? ");
            }
        }
    }

/* Get head node of the linked list and name that want to find then loop find it.
 * If found it, return that address back. But if not return 'NULL'.
 */
PERSON_T* findPerson(PERSON_T* pHead, char nameFind[])
    {
    PERSON_T *pCurrent = pHead;
    while (pCurrent != NULL)
        {
        if (strcasecmp(pCurrent->name, nameFind) == 0)
            return pCurrent;
        pCurrent = pCurrent->pNext;
        }
    /* If it out of loop, that mean not found */
    printf("Error: Person %s does not exits.\n", nameFind);
    return NULL;
    }

/* Get address of head node of linked list and name that want to delete. Then
 * find the position that want to delete and delete it.
 */
int deletePerson(PERSON_T** pHead, char nameFind[])
    {
    PERSON_T *pDelete = NULL;   /* Person that want to delete */
    PERSON_T *pTemp = *pHead;   /* Temporary person */
    char nameTemp[LEN] = {0};   /* Temporary name of person that deleted */
    /* Send to find position of person that want to delete */
    pDelete = findPerson(*pHead, nameFind);
    if (pDelete == NULL)    /* If not found, return 0 */
        return 0;
    /* If there are 1-2 persons left and user want to delete, print error message
     * and exit. Because we can't create couple with 1 person.*/
    else if (((*pHead)->pNext->pNext == NULL) || ((*pHead)->pNext == NULL))
        programError(4);
    strcpy(nameTemp, pDelete->name);
    /* If it's head node, change second node to head */
    if (pDelete == *pHead)
        {
        *pHead = (*pHead)->pNext;
        }
    else /* Otherwise maybe in the middle or tail node */
        {
        while(pTemp->pNext != pDelete)  /* Find the node before */
            {
            pTemp = pTemp->pNext;
            }
        /* If it's last node, set the 'pNext' of node before to NULL */
        if (pDelete->pNext == NULL)
            pTemp->pNext = NULL;
        /* Otherwise, it's node in the middle. Set 'pNext' of node before to
         * next node of deleted node */
        else
            pTemp->pNext = pDelete->pNext;
        }
    free(pDelete);
    printf("%s has been deleted. ", nameTemp);
    return 1;
    }

/* Get head node of linked list and 2 persons that want to make a couple. Then
 * set 2 of them to be a couple. If they've a couple, set 'pPartner' of partner
 * of old couple to NULL and print break up message.
 */
void makeCouple(PERSON_T* pHead, PERSON_T* pPerson1, PERSON_T* pPerson2)
    {
    /* If 2 persons is the same, that means user input same 2 names. */
    if (pPerson1 == pPerson2)
        {
        printf("\tError: you must not enter the same name.\n");
        return;
        }
    /* If gender of 2 persons is the same, print error message. */
    else if (strcasecmp(pPerson1->gender, pPerson2->gender) == 0)
        {
        printf("\tError: %s and %s are the same gender.\n", pPerson1->name,
                                                            pPerson2->name);
        return;
        }
    /* If Both of persons've already in a couple, don't do anything */
    else if ((pPerson1->pPartner == pPerson2) || (pPerson2->pPartner == pPerson1))
        return;
    /* Both condition below check that 2 persons there are another couple and set
     * the another couple to 'NULL'. Then print message to user. */
    if (pPerson1 -> pPartner != NULL)
        {
        printf("\t%s is breaking up with %s and is now a couple with %s\n",
               pPerson1->name,
               pPerson1->pPartner->name,
               pPerson2->name);
        pPerson1-> pPartner -> pPartner = NULL;
        }
    if (pPerson2-> pPartner != NULL)
        {
        printf("\t%s is breaking up with %s and is now a couple with %s\n",
               pPerson2->name,
               pPerson2-> pPartner ->name,
               pPerson1->name);
        pPerson2-> pPartner -> pPartner = NULL;
        }
    pPerson1->pPartner = pPerson2;
    pPerson2->pPartner = pPerson1;
    return;
    }

/* Get address of head node and loop print all of data */
void freeData(PERSON_T* pHead)
    {
    PERSON_T* pTemp = pHead;
    PERSON_T* pDel = pHead;
    while(pTemp != NULL)
        {
        pTemp = pDel->pNext;
        free(pDel);
        pDel = pTemp;
        }
    }

/* MAIN FUNCTION */
int main (int argc, char *argv[])
    {
    FILE *pFile = NULL;         /* Get address after open file */
    PERSON_T* pHead = NULL;     /* Head of the list */
    PERSON_T* pPerson1 = NULL;  /* Structure of first person */
    PERSON_T* pPerson2 = NULL;  /* Structure of second person */
    char input[LEN] = {0};      /* Get input from terminal line */
    char name[2][LEN] = {0};    /* Name of 2 people. */
    int amount = 0;             /* Amount of people */
    int check = 0;              /* Keep number to check ask */
    if (argc != 2)  /* Check that user input text file or not. */
        programError(1);
    /* Open file and check that it can open */
    pFile = fopen(argv[1], "r");
    if (pFile == NULL)
        programError(2);
    /* Read data in file and get head node of linked list */
    pHead = readFile(pFile, &amount);
    fclose(pFile);
    printf("Welcome to couples program.\n");
    printf("Read %d people:\n", amount);
    printData(pHead);
    /***** Ask for Delete Person part *****/
    printf("Do you want to delete people(Y/N)? ");
    check = askDelete();
    /* If check equal to 1, that mean user want to delete person */
    while (check == 1)
        {
        printf("Enter name to delete: ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%s", input);
        /* If person doesn't equal to 0, delete that person. But if equal to 0,
           that mean can't find that name. */
        if (deletePerson(&pHead, input))
            {
            amount--;
            printf("Continue(Y/N)? ");
            check = askDelete();
            }
        if (check == 0) /* User want to stop delete */
            {
            printf("Now there are %d people:\n", amount);
            printData(pHead);
            }
        }
    /***** Make a Couple Part *****/
    while(1)
        {
        check = askName(name); /* Ask and check that what user input */
        if (check == 0)   /* User input wrong format */
            printf("\tError: you must enter two names.\n");
        else if (check == 1) /* User input 'done' */
            {
            printf("\n");
            printCouple(pHead);
            freeData(pHead); /* Release each data */
            printf("Bye!\n");
            exit(0);
            }
        else if (check == 2) /* User input 2 names that are in couple */
            {
            /* Find persons in data. */
            pPerson1 = findPerson(pHead, name[0]);
            pPerson2 = findPerson(pHead, name[1]);
            /* If it's not error case, make a couple. */
            if ((pPerson1 != NULL) && (pPerson2 != NULL))
                makeCouple(pHead, pPerson1, pPerson2);
            }
        }
    }