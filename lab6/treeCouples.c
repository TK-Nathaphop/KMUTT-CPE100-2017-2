/******************************************************************************
 *
 *  treeCouples.c
 *
 *      This program get a text file from terminal line and read name and gender
 *      from file. After that ask user to print all people and which persons are 
 *      in couple. In the end print all of couple to user.
 *
 *      Nathaphop Sundarabhogin (KLA) ID 60070503420
 *          20 February 2018
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
    struct _person *pLeft;      /* Pointer to Left node child */
    struct _person *pRight;     /* Pointer to Right node child */
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

/* Insert a new node into the correct location in the tree. Compare string in
 * new node and current node which is less than and keep in the left child. But
 * if more than, keep in right child.
 *  Arguments:
 *      pNew - New Node that want to add
 *      pCurrent - Current that we consider
 */
void insertNode(PERSON_T* pNew,PERSON_T* pCurrent)
    {
    /* If it's less than current node, keep in left child. */
    if (strcmp(pNew->name,pCurrent->name) < 0)
        {
        if (pCurrent->pLeft == NULL)
            pCurrent->pLeft = pNew;
        else
            insertNode(pNew,pCurrent->pLeft);
        }
    /* Otherwise, It's more than current node. Keep in Right child. */
    else
        {
        if (pCurrent->pRight == NULL)
            pCurrent->pRight = pNew;
        else
            insertNode(pNew,pCurrent->pRight);
        }
    return;
    }

/* Read all people in file then keep in new tree and return it back.
 *  Arguments:
 *      pFile - file that want to read
 *      amount - amount of people
 */
PERSON_T* readFile(FILE* pFile, int *amount)
    {
    char input[LEN] = {0};      /* Get input from text file */
    PERSON_T* pRoot = NULL;     /* Keep New root and return it back after read */
    PERSON_T* pNew = NULL;      /* Create new node after read each line */
    int count = 0;              /* Count how many people in file */
    /* Read each line in file */
    while (fgets(input, sizeof(input), pFile) != NULL)
        {
        pNew = calloc(1, sizeof(PERSON_T));
        if (pNew == NULL)   /* If can't allocate memory, print error and exit */
            programError(3);
        sscanf(input, "%s %s", pNew->name, pNew->gender);
        if (pRoot == NULL)  /* If it's new node, it's root of tree */
            pRoot = pNew;
        else /* Otherwise, add new node to tree */
            insertNode(pNew,pRoot);
        count++;
        }
    *amount = count;
    return pRoot;
    }

/* Print all people in tree by in-order traversal.
 * Argument:
 *      pCurrent - Current node that want to consider / print people
 */
void printAll(PERSON_T* pCurrent)
    {
    if (pCurrent->pLeft != NULL)
        printAll(pCurrent->pLeft);
    printf("    %s %s\n", pCurrent->name, pCurrent->gender);
    if (pCurrent->pRight != NULL)
        printAll(pCurrent->pRight);
    return;
    }

/* Print all people that are in couple by in-order traversal.
 * Argument:
 *      pCurrent - Current node that want to consider / print couple.
 */
void printCouple(PERSON_T* pCurrent)
    {
    if (pCurrent->pLeft != NULL)
        printCouple(pCurrent->pLeft);
    if ((pCurrent->pPartner != NULL) && (pCurrent->gender[0] == 'M'))
        printf("\t%s is coupled with %s\n", pCurrent->name,
                                            pCurrent->pPartner->name);
    if (pCurrent->pRight != NULL)
        printCouple(pCurrent->pRight);
    return;
    }

/* Get address of name and ask user for input 2 names. If user input wrong format,
 * print error message and return 0. But if user input correct, return 1. 
 */
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
int askPrint()
    {
    char input[LEN] = {0};  /* Get input from terminal line */
    while(1)
        {
        printf("Do you want to all people(Y/N)? ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%s", input);
        if ((strlen(input) == 1) && (input[0] == 'Y' || input[0] == 'y'))
            return 1;
        if ((strlen(input) == 1) && (input[0] == 'N' || input[0] == 'n'))
            return 0;
        else
            printf("Error: Please answer only 'Y' or 'N'\n");
        }
    }

/* Find person that want to know in tree and return that node back
 * Arguments:
 *      pCurrent - Node that we consider
 *      nameFind - Name of person that we want to find
 */
PERSON_T* findPerson(PERSON_T* pCurrent, char nameFind[])
    {
    PERSON_T *pFound = NULL;    /* Keep node that we want to find */
    int check = 0;              /* Keep value after compare 2 names */
    if (pCurrent != NULL)
        {
        check = strcasecmp(nameFind, pCurrent->name);
        if (check == 0)         /* Found node */
            pFound = pCurrent;
        else if(check < 0)      /* Go to Left node */
            pFound = findPerson(pCurrent->pLeft, nameFind);
        else                    /* Otherwise, Go to right node */
            pFound = findPerson(pCurrent->pRight, nameFind);
        }
    return pFound;
    }

/* Make 2 persons into a couple relation. If both of them are same gender or
 * same people, It'll print error message.
 *  Arguments:
 *      pPerson1 and pPerson2 - 2 persons that want to make a couple.
 */
void makeCouple(PERSON_T* pPerson1, PERSON_T* pPerson2)
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

/* Free all of data in tree by using post-order traversal
 * Argument:
 *      pCurrent - Current node that we consider
 */
void freeTree(PERSON_T* pCurrent)
    {
    if (pCurrent->pLeft != NULL)
        freeTree(pCurrent->pLeft);
    if (pCurrent->pRight != NULL)
        freeTree(pCurrent->pRight);
    free(pCurrent);
    }

/* MAIN FUNCTION. Read data in file and ask which persons are in a couple.
 * After finished, print all of couples to user and free all of data in tree.
 */
int main (int argc, char *argv[])
    {
    FILE *pFile = NULL;         /* Get address after open file */
    PERSON_T* pRoot = NULL;     /* Head of the list */
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
    pRoot = readFile(pFile, &amount);
    fclose(pFile);
    printf("Welcome to couples program.\n");
    printf("Read %d people:\n", amount);
    /* Ask user that want to print all data or not */
    check = askPrint();
    if(check = 1)
        printAll(pRoot);
    printf("\n");
    /* Ask to make a Couple */
    while(1)
        {
        check = askName(name); /* Ask and check that what user input */
        if (check == 0)   /* User input wrong format */
            printf("\tError: you must enter two names.\n");
        else if (check == 1) /* User input 'done' */
            {
            printf("\n");
            printf("Couples:\n");
            printCouple(pRoot);
            freeTree(pRoot); /* Release each data */
            printf("Bye!\n");
            exit(0);
            }
        else if (check == 2) /* User input 2 names that are in couple */
            {
            /* Find persons in data. */
            pPerson1 = findPerson(pRoot, name[0]);
            pPerson2 = findPerson(pRoot, name[1]);
            /* If not found person, Print error message */
            if(pPerson1 == NULL)
                printf("Error: Person %s does not exits.\n", name[0]);
            if (pPerson2 == NULL)
                printf("Error: Person %s does not exits.\n", name[1]);
            /* If it's not error case, make a couple. */
            if ((pPerson1 != NULL) && (pPerson2 != NULL))
                makeCouple(pPerson1, pPerson2);
            }
        }
    }