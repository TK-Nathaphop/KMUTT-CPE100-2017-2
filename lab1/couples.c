/******************************************************************************
 *
 *  couples.c
 *
 *      This program get a text file from terminal line and read name and gender
 *      from file. After that ask user which are in couple. In the end print
 *      summary to user.
 *
 *      Nathaphop Sundarabhogin (KLA) ID 3420
 *          16 JAN 2018
 *
 ******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 100

typedef struct _person
    {
    char name[LEN];             /* Person's name */
    char gender;                /* Person's gender */
    struct _person * pPartner;   /* Another PERSON_T who is this partner. */
    } PERSON_T;   

/****************************** Declare Function ******************************/
FILE* openFile(char fileName[]);
PERSON_T** getData(FILE* pFile, int* amount);
int askName(char name[][LEN]);
int findName(PERSON_T** people, int amount, char name[LEN]);
void makeCouple(PERSON_T** people,int amount, int position[]);
void printData(PERSON_T** people,int amount);
void printCouple(PERSON_T** people, int amount);

/* Open text file and read data. Then print all of data and get input from user
 * who is in a couple. When user input 'done', print all of couples and release
 * all data in program. Then exit the program.
 */
int main(int argc, char* argv[])
    {
    FILE* pFile = NULL;         /* Get address of file. */
    PERSON_T **people = NULL;   /* Keep array of pointer. */
    char name[2][LEN] = {0};    /* Name of 2 people. */
    int position[2] = {0};      /* Keep position after find name */
    int check = 0;              /* Check return value from another function */
    int amount = 0;             /* Amount of people. */
    int i = 0;                  /* Count loop */
    if (argc != 2) /* Check that user input text file or not. */
        {
        printf("Please input file name after run this program\n");
        printf("Example: ./couples people.txt\n");
        exit(0);
        }
    pFile = openFile(argv[1]);          /* Open file and check that it can open */
    people = getData(pFile, &amount);   /* Get data and amount from file */
    fclose(pFile);
    printf("Welcome to couples program.\n");
    printf("Read %d people:\n", amount);
    printData(people,amount);           /* Print all of data to user */
    while(1) /* Loop ask and store who are in a couple. */
        {
        check = askName(name); /* Ask and check that what is user input */
        if (check == 0)   /* User input wrong format */
            printf("\tError: you must enter two names.\n");
        else if (check == 1) /* User input 'done' */
            {
            printf("\n");
            printCouple(people,amount);
            for(i = 0; i < amount; i++) /* Release each data */
                free(people[i]);
            free(people);
            printf("Bye!\n");
            exit(0);
            }
        else if (check == 2) /* User input 2 names that are in couple */
            {
            /* Find position of data that want to know. */
            position[0] = findName(people, amount, name[0]);
            position[1] = findName(people, amount, name[1]);
            /* If it's not error case, make a couple. */
            if ((position[0] != -1) && (position[1] != -1))
                makeCouple(people, amount, position);
            }
        }
    }

/* Get file name that want to open and open that file. If open success, return
 * address after open.
 */
FILE* openFile(char fileName[])
    {
    FILE* pFile = NULL;         /* Get address of open file. */
    pFile = fopen(fileName,"r");
    if (pFile == NULL)  /* Check that can open file or not. */
        {
        printf("Can't open text file. Program exit.\n");
        exit(0);
        }
    return pFile;
    }

/* Read amount of people from text file and allocate pointer to pointer with
 * amount of people. Then loop read each line, while read each line allocate 1
 * structure and keep in pointer to pointer array. When finished return address
 * of pointer to pointer and amount back.
 */
PERSON_T** getData(FILE* pFile, int* amount)
    {
    PERSON_T** people = NULL;   /* Keep data after read from file */
    char line[LEN] = {0};       /* Keep each line from file */
    int i = 0;                  /* Count loop */
    /* Read amount of data and check that it can read or not. */
    if (fgets(line, sizeof(line), pFile) != NULL)
        sscanf(line, "%d", amount);
    else
        {
        printf("Can't read amount of people. Program exit.\n");
        exit(0);
        }
    people = (PERSON_T**)calloc(*amount, sizeof(PERSON_T*));
    if (people == NULL) /* Check that can allocate pointer to pointer or not */
        {
        printf("Can't allocate memory for variable. Program exit.\n");
        exit(0);
        }
    /* Read each line and allocate new structure to keep data */
    for(i = 0; (fgets(line,sizeof(line),pFile) != NULL) && (i < *amount); i++)
        {
        people[i] = calloc(1,sizeof(PERSON_T));
        if (people[i] == NULL) /* Check that can allocate memory or not */
            {
            printf("Can't allocate memory to keep data. Program exit.\n");
            exit(0);
            }
        sscanf(line, "%s %c", people[i]->name, &people[i]->gender);
        }
    return people;
    }

/* Get data and amount of data, then print all of name and gender to user.
 */
void printData(PERSON_T** people,int amount)
    {
    int i = 0;  /* Count loop */
    for(i = 0; i < amount; i++)
        printf("\t%s %c\n", people[i]->name, people[i]->gender);
    printf("\n");
    return;
    }

/* Get address of name and ask user for input 2 names. If user input wrong form,
 * print error message and return -1. But if user input correct, return 1 */
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
    else if (check == 2)
        {
        strcpy(name[0], nameInput[0]);
        strcpy(name[1], nameInput[1]);
        return 2;
        }
    else
        return 0;
    }

/* Get data, amount of data and name that want to find. Then loop find name in
 * data. If found a name, return position of that data. But if not, return '-1'.
 */
int findName(PERSON_T** people, int amount, char name[LEN])
    {
    int i = 0;  /* Count loop */
    for (i = 0; i < amount; i++)
        {
        if (strcasecmp(name, people[i]->name) == 0)
            return i;
        }
    /* If out of loop that mean doesn't found that name */
    printf("\tError: person %s does not exists\n", name);
    return -1;
    }
    
/* Get data, amount of data and 2 positions that want to make a couple. Before
 * stored they are in couple, check that they are the same people, gender or not.
 * Then check that they're in another couple or not. If they're in another couple,
 * print message and set to be 'NULL'. After that, set 2 persone to be a couple.
 */
void makeCouple(PERSON_T** people, int amount, int position[])
    {
    /* If 2 positions is the same, that means user input same 2 names. */
    if (position[0] == position[1])
        {
        printf("\tError: you must not enter the same name.\n");
        return;
        }
    /* If gender of 2 persons is the same, print error message. */
    else if (people[position[0]]->gender == people[position[1]]->gender)
        {
        printf("\tError: %s and %s are the same gender.\n",
            people[position[0]]->name,
            people[position[1]]->name);
        return;
        }
    /* Both condition below check that 2 persons there are another couple and set
     * the another couple to 'NULL'. Then print message to user. */
    if ((people[position[0]]-> pPartner != NULL) 
        && (people[position[0]]->pPartner != people[position[1]])
        && (people[position[1]]->pPartner != people[position[0]]))
        {
        printf("\t%s is breaking up with %s and is now a couple with %s\n",
               people[position[0]]->name,
               people[position[0]]->pPartner->name,
               people[position[1]]->name);
        people[position[0]]-> pPartner -> pPartner = NULL;
        }
    if ((people[position[1]]-> pPartner != NULL)
        && (people[position[0]]->pPartner != people[position[1]])
        && (people[position[1]]->pPartner != people[position[0]]))
        {
        printf("\t%s is breaking up with %s and is now a couple with %s\n",
               people[position[1]]->name,
               people[position[1]]-> pPartner ->name,
               people[position[0]]->name);
        people[position[1]]-> pPartner -> pPartner = NULL;
        }
    people[position[0]]->pPartner = people[position[1]];
    people[position[1]]->pPartner = people[position[0]];
    return;
    }


/* Get data and amount. Then print summary who are in couple. */
void printCouple(PERSON_T** people,int amount)
    {
    int i = 0;              /* Count loop */
    int printCouple = 0;    /* Count that program have already printed couple */
    for (i = 0; i < amount ; i++)
        {
        /* This condition for they're in couple and only male. */
        if ((people[i]->pPartner != NULL) && (people[i]->gender == 'M'))
            {
            if (printCouple == 0)   /* Print head of summary */
                {
                printf("Couples:\n");
                printCouple = 1;
                }
            printf("\t%s is coupled with %s\n", people[i]->name,
                                              people[i]->pPartner->name);
            }
        }
    return;
    }