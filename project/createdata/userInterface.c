/******************************************************************************
 *
 *  userInterface.c
 *
 *      This module working for user interface. Print display to terminal and
 *      asking input from user.
 *
 *      Created by Nathaphop Sundarabhogin (KLA)    ID : 3420
 *      18 April 2018
 *
 ******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "simpleFacebook.h"
#include "validate.h"

/***************************** LOCAL FUNCTION ********************************/

/* Print date, month, and year of birth date
 * Argument:
 *      date - date that we want to print
 */
void _printBirthDate(int date[])
    {
    char month[13][20] = {"","January", "February", "March", "April",
                          "May", "June", "July", "August", "September",
                          "October", "November", "December"};
    printf("%02d %s %4d", date[0], month[date[1]], date[2]);
    }

/**************************** PUBLIC FUNCTION ********************************/

/* Clear terminal and print head of program
 */
void headUserInterface()
    {
    int i = 0;      /* For loop */
    system("clear");
    for(i = 0; i < 90; i++)
    	printf("=");
    printf("\n");
    printf("\t\tTHE SIMPLE FACEBOOK PRESENTED BY RUN EVERY VERB TEAM!");
    printf("\n");
    for(i = 0; i < 90; i++)
    	printf("=");
    printf("\n");
    }

/* Remove 'new line' from last character out.
 * ARGUMENT: 
 *     string - String want to remove 'new line'.
 */
void cutLine(char *string)
    {
    char *pCut;    /* Get string after found <CR>. */
    pCut = strpbrk(string,"\r\n");
    if (pCut != NULL)
        *pCut = '\0';
    }

/* Print date, month, year, hour and minute
 * Argument:
 *      date - date that we want to print
 */
void printDate(int date[])
    {
    char month[13][20] = {"","January", "February", "March", "April",
                          "May", "June", "July", "August", "September",
                          "October", "November", "December"};
    printf("%02d %s %4d %02d:%02d", date[0], month[date[1]], date[2],
                                    date[3], date[4]);
    }

/* Print all data of user.
 * Argument:
 *      pUser - User that want to print data.
 */
void printData(USER_T *pUser)
    {
    printf("E-mail: %s\n", pUser->mail);
    printf("Name: %s\n", pUser->name);
    printf("Phone: %s\n", pUser->phone);
    if(pUser->gender == G_MALE)
        printf("Gender: Male\n");
    else
        printf("Gender: Female\n");
    printf("Birth date: ");
    _printBirthDate(pUser->dateBirth);
    printf("\n");
    printf("\n");
    }

/* Print instruction and command after user use command '/help'
 */
void printHelp()
    {
    char input[LEN] = {0};
    headUserInterface();
    printf("This program will act as a social network that named Facebook.\n");
    printf("But it’s just Simple Facebook\n");
    printf("\n");
    printf("Command:\n");
    printf("/help - See all command.\n");
    printf("/home - Go to first status or refresh program.\n");
    printf("/s <text> - Update new status.\n");
    printf("/c <text> - Comment current status.\n");
    printf("/next - See next status.\n");
    printf("/pending - See who are request to be your friend.\n");
    printf("/profile - See user's information.\n");
    printf("/find <E-mail> - Find another user Simple Facebook.\n");
    printf("/signout - Signout from Simple Facebook.\n");
    printf("\nAfter command '/pending' user can user only this command.\n");
    printf("/acceptf - Accept current friend pending request to be friend\n");
    printf("/denyf - Deny current friend pending request\n");
    printf("Otherwise, '/home' to go back or '/help' to see instruction.\n");
    printf("\nAfter command '/find <E-mail>' user can user only this command.\n");
    printf("/addfriend - Send friend pending request to friend that we find.\n");
    printf("/unfriend - Delete friend that we find.\n");
    printf("Otherwise, '/home' to go back or '/help' to see instruction.\n\n");
    return;
    }

/* Print that command input not correct.
 * Argument:
 *      error - type of error
 */
void printCommandError(int error)
    {
    if(error == 1)  /* Command not correct */
        {
        printf("#SYSTEM: Command not correct.\n");
        }
    /* Use '/acceptf' or '/denyf' without see pending request */
    else if (error == 2)
        {
        printf("#SYSTEM: Can't use that command right now.\n");
        printf("#SYSTEM: You must use command '/pending' first.\n");
        }
    /* Use '/addfriend' or '/unfriend' without find friend first */
    else if (error == 3)
        {
        printf("#SYSTEM: Can't use that command right now.\n");
        printf("#SYSTEM: You must use command '/find <E-mail>' first.\n");
        }
    /* Use '/pending' or '/find <E-mail>' without go back to home first */
    else if (error == 4)
        {
        printf("#SYSTEM: Can't use that command right now.\n");
        printf("#SYSTEM: You must go back to home first (/home).\n");
        }
    printf("#SYSTEM: Use command '/help' to see all command\n");
    printf("#SYSTEM: Please try again.\n\n");
    }

/* Get select then print message that want to print before exit
 * Argument:
 *      error - Error case.
 */
void printError(int error)
    {
    system("clear");
    if (error == 1) /* Can't allocate memory */
        printf("#SYSTEM: Program can't allocate memory program.\n");
    else if (error == 2)    /* Can't open read file */
        printf("#SYSTEM: Program can't open database file.\n");
    else if (error == 3)    /* Can't open write file */
        printf("#SYSTEM: Error! Unable to create new data file!\n");
    else if (error == 4)    /* Not found user data in file */
        {
        printf("#SYSTEM: Error while read data file.\n");
        printf("#SYSTEM: Can't find data in system.\n");
        }
    else if (error == 5)    /* Wrong format of tag and data */
        {
        printf("#SYSTEM: Error while read file.\n");
        printf("#SYSTEM: Wrong format of data file.\n");
        printf("#SYSTEM: After tag doesn't follow with data.\n");
        }
    else if (error == 6)    /* Have error when add friend/pening into list */
        {
        printf("#SYSTEM: Error while read file.\n");
        printf("#SYSTEM: Can't add user into friend list/pending list.\n");
        }
    else if (error == 7)    /* Format of tag doesn't correct */
        {
        printf("#SYSTEM: Error while read file.\n");
        printf("#SYSTEM: Wrong format of data file.\n");
        printf("#SYSTEM: Tag is not arrange correctly\n");
        }
    else if (error == 8)    /* Unable to read next data */
        {
        printf("#SYSTEM: Error while read file.\n");
        printf("#SYSTEM: Wrong format of data file.\n");
        printf("#SYSTEM: Unable to read next data\n");
        }
    printf("#SYSTEM: Program exit\n");
    exit(0);
    }

/**************************************/
void printComment(COMMENT_T *pComment)
    {
    USER_T *pOwner = NULL;
    char *pText = {0};
    int *pDate = NULL;
    pOwner = pComment->owner;
    pText = pComment->text;
    pDate = pComment->date;
    printf("\t%s\n", pOwner->name);
    printf("\t%s\n", pText);
    printf("\t");
    printDate(pDate);
    printf("\n");
    }

/* Print status and all comment of that status.
 * Argument:
 *      pStatus - Status that we want to print.
 */
void printStatus(STATUS_T *pStatus)
    {
    COMMENT_T *pCurrentC = NULL;    /* Current comment */
    USER_T *pOwnerS = NULL;         /* Owner of status */
    char *pText = NULL;             /* Text of status */
    int *pDate = NULL;              /* Date of status */
    if(pStatus != NULL) /* If Status not null, intinall all variable for work */
        {
        pOwnerS = pStatus->owner;
        pCurrentC = pStatus->pHeadC;
        pText = pStatus->text;
        pDate = pStatus->date;
        }
    else    /* Otherwise, print not have status to show */
        {
        printf("== Don't have any status to show ==\n");
        return;
        }
    printf("%s\n",pOwnerS->name);
    printDate(pDate);
    printf("\n%s\n",pText);
    /* After print status, Print all comment */
    if(pCurrentC != NULL)
        printf("\nComments:\n");
    while(pCurrentC != NULL)
        {
        printComment(pCurrentC);
        printf("\n");
        pCurrentC = pCurrentC->pNext;
        }
    }

/* Ask and validate e-mail (In progress)
 * Argument:
 *      pReturn - E-mail that we have to return
 * Return 1, if user input e-mail success.
 * Return 0, if user cancel to input e-mail.
 */
int askMail(char *pReturn)
    {
    char input[LEN] = {0};
    printf("E-mail: ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) == 1)
        return 0;
    cutLine(input);
    strcpy(pReturn, input);
    return 1;
    }

/* Ask and validate password (In progress)
 * Argument:
 *      pReturn - password that we have to return
 * Return 1, if user input e-mail success.
 * Return 0, if user cancel to input e-mail.
 */
int askPassword(char *pReturn)
    {
    char input[LEN] = {0};
    printf("Password: ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) == 1)
        return 0;
    cutLine(input);
    strcpy(pReturn, input);
    return 1;
    }

/* Ask and validate name (In progress)
 * Argument:
 *      pReturn - name that we have to return
 * Return 1, if user input e-mail success.
 * Return 0, if user cancel to input e-mail.
 */
int askName(char *pReturn)
    {
    char input[LEN] = {0};
    printf("Name: ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) == 1)
        return 0;
    cutLine(input);
    strcpy(pReturn, input);
    return 1;
    }

/* Ask and validate phone (In progress)
 * Argument:
 *      pReturn - phone that we have to return
 * Return 1, if user input e-mail success.
 * Return 0, if user cancel to input e-mail.
 */
int askPhone(char *pReturn)
    {
    char input[LEN] = {0};
    printf("Phone: ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) == 1)
        return 0;
    cutLine(input);
    strcpy(pReturn, input);
    return 1;
    }

/* Ask and validate phone (In progress)
 * Argument:
 *      pReturn - Array of date that we have to return
 * Return 1, if user input e-mail success.
 * Return 0, if user cancel to input e-mail.
 */
int askBirthDate(int pReturn[])
    {
    char input[LEN] = {0};
    printf("Birth Date (dd mm yyyy)\n");
    printf("(Example: 01 01 1998): ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) == 1)
        return 0;
    sscanf(input, "%d %d %d", &pReturn[0], &pReturn[1], &pReturn[2]);
    return 1;
    }

/* Ask and validate gender
 * Argument:
 *      pReturn - phone that we have to return
 * Return 1, if user input e-mail success.
 * Return 0, if user cancel to input e-mail.
 */
int askGender(GENDER_TYPE *pReturn)
    {
    char input[LEN] = {0};
    while(1)
        {
        printf("Gender('M' or 'F'): ");
        fgets(input, sizeof(input), stdin);
        if (strlen(input) == 1)
            return 0;
        cutLine(input);
        if ((strlen(input) == 1) && (input[0] == 'M'))
            {
            *pReturn = G_MALE;
            break;
            }
        if ((strlen(input) == 1) && (input[0] == 'F'))
            {
            *pReturn = G_FEMALE;
            break;
            }
        else
            printf("#SYSTEM: Error! Please input only 'M' or 'F'.\n\n");
        }
    return 1;
    }

/* Ask that user want to accept pending request to friend or not.
 * Return 1, if user answer 'y'. Return 2, if user answer 'n'.
 * Return 0, if user want to cancel.
 */
int askPending()
    {
    char input[LEN] = {0};
    while(1)
        {
        printf("'Y', 'N', or Hit <CR> to go back: ");
        fgets(input, sizeof(input), stdin);
        cutLine(input);
        if(strcasecmp(input, "y") == 0)
            return 1;
        else if(strcasecmp(input, "n") == 0)
            return 2;
        else if(strlen(input) == 0)
            return 3;
        else
            printf("Wrong input!\n");
        }
    }

/* Ask and get command from user.
 * Argument:
 *      pReturn - phone that we have to return
 * Return type of command that user input and some command of Simple Facebook
 * that have to return string.
 */
COMMAND_TYPE askCommand(char *pReturn)
    {
    char input[LEN] = {0};
    printf("Command: ");
    fgets(input, sizeof(input), stdin);
    cutLine(input);
    printf("\n");
    return checkCommand(input, pReturn);
    }

/* Print menu, ask user to select menu theb return menu that user select
 * Return 1-3. Return 1 for Register. Return 2 for Sign in. Return 3 for Exit.
 */
int askMenu()
    {
    char input[100] = {0};
    int menu = 0;
    while(1)
        {
        printf("\nMENU:\n");
        printf("    1 : Register\n");
        printf("    2 : Sign in\n");
        printf("    3 : Exit the program\n");
        printf("#SYSTEM: Select item that you want? : ");
        fgets(input, sizeof(input), stdin);
        cutLine(input);
        if ((strlen(input) == 1) && isdigit(input[0]))
            {
            sscanf(input,"%d", &menu);
            if ((menu >= 1) || (menu <= 3))
                return menu;
            }
        printf("#SYSTEM: Input is invalid. Please get input again.\n");
        }
    }

/* Loop ask user that exit or not
 * If exit dump all data to file and free all data
 * Return 1, if user want to exit program.
 * Return 0, if user don't want.
 */
int askExit()
    {
    char input[LEN] = {0};
    while (1)
        {
        printf("#SYSTEM: Do you want to exit the program? ( Y/N ): ");
        fgets(input, sizeof(input), stdin);
        cutLine(input);
        if ((input[0] == 'y') || (input[0] == 'Y') && (strlen(input) == 1))
            return 1;
        else if ((input[0] == 'n') || (input[0] == 'N') && (strlen(input) == 1))
            return 0;
        else
            {
            printf("#SYSTEM: Input is invalid. Please get input again.\n");
            }
        }
    }