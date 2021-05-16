/******************************************************************************
 *
 *    simpleFacebook.c
 *
 *    Main program.
 *
 *    Created by SETTHAWUT LEELAWATTHANAPANIT (SAAB)    ID : 60070503466
 *        15 APRIL 2018
 *
 ******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleFacebook.h"
#include "validate.h"
#include "manageData.h"
#include "userInterface.h"
#include "dumpFile.h"

/* Declare function */
int controlSignIn();
int controlExit();
void controlHome();
void controlRegister();
void controlHeadStatus(int select);
void controlUpdateStatus(char *pText);
void controlUpdateComment(char *pText);
void controlFriend(int select, USER_T *pUser);
void controlPending();
void controlFindUser(char *find);
void controlFacebook();
void controlSuggestFriend();

int main()
    {
    char input[LEN] = {0};  /* Get input from user */
    int menu = 0;           /* Get menu from user */
    readDatabase();
    while(1)
        {
        headUserInterface();
        menu = askMenu();
        if (menu == 1) /* Register */
            controlRegister();
        else if (menu == 2) /* Sign in */
            {
            if (controlSignIn() == 1)
                controlFacebook();
            }
        else if (menu == 3)
            {
            if (controlExit() == 1)
                {
                system("clear");
                printf("Good bye from our Simple Facebook!\n");
                exit(0);
                }
            }
        }
    }

/* Control register part. Create a new user then ask user for input information
 * After input finished, keep in data structure.
 */
void controlRegister()
    {
    USER_T *pNew = (USER_T*)calloc(1,sizeof(USER_T));
    if (pNew == NULL)
        printError(1);
    headUserInterface();
    printf("REGISTER:\n");
    printf("Please input information below\n");
    printf("Hit <CR> to cancel.\n");
    /* Ask data from user. If some of these return 0 that mean user cancel. */
    if (askMail(pNew->mail) == 0)
        {
        free(pNew);
        return;
        }
    if (askPassword(pNew->password) == 0)
        {
        free(pNew);
        return;
        }
    if (askName(pNew->name) == 0)
        {
        free(pNew);
        return;
        }
    if (askPhone(pNew->phone) == 0)
        {
        free(pNew);
        return;
        }
    if (askBirthDate(pNew->dateBirth) == 0)
        {
        free(pNew);
        return;
        }
    if (askGender(&pNew->gender) == 0)
        {
        free(pNew);
        return;
        }
    /* After finish asking, keep into data structure. */
    addData(pNew);
    }

/* Control register part. Create a new user then ask user for input information
 * After input finished, keep in data structure.
 * Return 1, if sign in succes. Return 0, if cancel to sign in.
 */
int controlSignIn()
    {
    char input[LEN] = {0};       /* Get input from user */
    char mail[LEN] = {0};        /* Keep E-mail that user input */
    char password[LEN] = {0};    /* Keep Password that user input */
    int retVal = 0;              /* Return value */
    headUserInterface();
    while(1)
        {
        printf("SIGN IN:\n");
        /* Ask E-mail and password. If return 0, that mean user cancel. */
        if (askMail(mail) == 0)
            return 0;
        if (askPassword(password) == 0)
            return 0;
        /* After finish asking, send to SignIn into data structure. */
        retVal = signIn(mail, password);
        if (retVal == 1)
            {
            printf("Sign in success!\n");
            return 1;
            }
        else
            {
            if (retVal == 0)
                printf("Password not correct. Please try again.\n");
            else if (retVal == -1)
                printf("Can't find that E-mail. Please try again.\n");
            printf("\n");
            }
        }
    }

/* Control after sign in into Simple Facebook part.
 * This function will suggest friend, status and get command.
 */
void controlFacebook()
    {
    STATUS_T *pStatus = NULL;   /* Status of user */
    char input[LEN] = {0};      /* Get input from user */
    char text[LEN] = {0};       /* Get text after command */
    COMMAND_TYPE retVal = 0;    /* Return value */
    controlHeadStatus(1);
    headUserInterface();
    controlSuggestFriend();
    while(1)
        {
        controlHeadStatus(2);
        printf("Use command '/help' to see all command.\n");
        /* Ask command from user. If some of these return 0, mean user cancel. */
        retVal = askCommand(text);
        if (retVal == C_ERROR)
            printCommandError(1);
        else if (retVal == C_SIGNOUT)
            {
            signOut();
            return;
            }
        else if (retVal == C_STATUS)
            controlUpdateStatus(text);
        else if (retVal == C_COMMENT)
            controlUpdateComment(text);
        else if (retVal == C_FIND)
            controlFindUser(text);
        else if (retVal == C_HOME)
            controlHome(); 
        else if (retVal == C_HELP)
            printHelp();
        else if (retVal == C_NEXT)
            controlHeadStatus(3);
        else if (retVal == C_PENDING)
            controlPending();
        else if (retVal == C_PROFILE)
            printData(getUser());
        else if ((retVal == C_ACCEPTF) || (retVal == C_DENYF))
            printCommandError(2);
        else if ((retVal == C_ADDFRIEND) || (retVal == C_UNFRIEND))
            printCommandError(3);
        else if (retVal == C_UNFRIEND)
            printCommandError(1);
        memset(input, 0, sizeof(input));
        memset(text, 0, sizeof(text));
        }
    }


/* Control update status part.
 * Send text and current date to update status in database
 * If update success print status show user.
 * But if not, print error.
 */
void controlUpdateStatus(char *pText)
    {
    STATUS_T *pNew = NULL;  /* Get new status after update */
    int date[5] = {0};      /* Current date */
    dateToday(date);
    pNew = updateStatus(pText, date, 1);
    if(pNew == NULL)
        printError(1);
    else
        {
        controlHeadStatus(1);
        headUserInterface();
        }
    return;
    }

/* Control update comment part.
 * Send text and current date to update status in database
 * If update success print status show user.
 * But if not, print error.
 */
void controlUpdateComment(char *pText)
    {
    STATUS_T *pStatus = NULL;     /* Status that we want to update */
    COMMENT_T *pComment = NULL;   /* Get new status after update */
    int date[5] = {0};        /* Current date */
    statusMenu(2, &pStatus);
    if (pStatus == NULL)    /* Not have any status to comment */
        {
        printf("Not have any status to comment\n");
        return;
        }
    dateToday(date);
    pComment = updateComment(pStatus, pText, date);
    if(pComment == NULL)
        printError(1);
    else
        {
        headUserInterface();
        }
    return;
    }


/* Control function when user use command find another user.
 * If found user data, print information of that user.
 * Then control to get another command.
 * But if not, print not found and go back.
 * Argument:
 *      find - Name that we want to find.
 */
void controlFindUser(char *find)
    {
    USER_T* pFind = findData(find); /* User that we want to find */
    char dummy[LEN] = {0};          /* Dummy string to ask command */
    int retVal = 0;                 /* Return value */
    if(pFind == NULL)   /* Not found data */
        {
        printf("#SYSTEM: E-mail not correct. Can't find that user in system.\n");
        return;
        }
    else
        {
        headUserInterface();
        printf("FIND FRIEND:\n");
        printData(pFind);
        }
    while(1)
        {
        retVal = askCommand(dummy);
        if (retVal == C_HOME) /* '/home' command */
            {
            headUserInterface();
            return;
            }
        /* User want to add friend or unfriend */
        else if ((retVal == C_ADDFRIEND) || (retVal == C_UNFRIEND))
            controlFriend(retVal, pFind);
        /* User want to see help command */
        else if (retVal == C_HELP)
            {
            printHelp();
            printData(pFind);
            }
        else /* The other command not allow while find friend */
            printCommandError(4);
        }
    }

void controlPending()
    {
    int count = 0;
    int retVal = 0;
    USER_T* pFriend = lookPending(&count);
    char input[LEN] = {0};
    headUserInterface();
    while (pFriend!=NULL)
        {
        printf("There are %d peoples have been send you a pending request\n\n"
                                                                    ,count);
        printData(pFriend);
        printf("This user have been send pending request to be your friend\n");
        printf("Accept or not?\n");
        retVal = askPending();
        if (retVal == 1)
            {
            if(acceptFriendPending() == -1)
                printError(1);
            printf("%s is now your friend in Simple Facebook\n", pFriend->name);
            }
        else if (retVal == 2)
            {
            denyFriendPending();
            }
        else if (retVal == 3)
            {
            pFriend == NULL;
            headUserInterface();
            return;
            }
        printf("===============================================================\n\n");
        pFriend = lookPending(&count);
        controlHeadStatus(1);
        }
    if (pFriend == NULL)
        {
        printf("Don't have any friend pending request\n");
        }
    }

/* Control function when user want to add friend / delete friend
 * Argument:
 *      find - Name that we want to find.
 */
void controlFriend(int select, USER_T *pUser)
    {
    int retVal = 0; /* Return Value */
    if(select == C_ADDFRIEND)
        {
        retVal = addPending(pUser);
        if (retVal == -1)   /* Can't new allocate memoery */
            printError(1);
        else if (retVal == 0)    /* They're friend or add friend pending already */
            {
            printf("#SYSTEM: Can't send pending request to this user.\n");
            printf("#SYSTEM: Please unfriend this user first.\n");
            }
        else if (retVal == 2)   /* User is sent request by 'pUser' */
            {
            printf("#SYSTEM: This user has already send pending request to you.\n");
            printf("#SYSTEM: Please check in your pending request.\n");
            }
        else if (retVal == 3)   /* 'pUser' and user are the same */
            printf("#SYSTEM: You can't add yourself to be friend.\n");
        else
            printf("SYSTEM: Send pending request to this user success.\n");
        }
    else if (select == C_UNFRIEND)
        {
        retVal = unFriend(pUser);
        if (retVal == -1)   /* Can't new allocate memoery */
            printError(1);
        else if (retVal == 0)    /* They're not friend */
            {
            printf("#SYSTEM: You and this user aren't friend\n");
            printf("#SYSTEM: Please add friend this user first.\n");
            }
        else if (retVal == 2)    /* User login is sent request by 'pUser' */
            {
            printf("#SYSTEM: This user has already send pending request to you.\n");
            printf("#SYSTEM: Please check in your pending request.\n");
            }
        else if (retVal == 3)   /* 'pUser' and user are the same */
            printf("#SYSTEM: You can't unfriend yourself.\n");
        else if (retVal == 4)   /* 'pUser' is sent reqeust by user login */
            printf("#SYSTEM: Cancel send pending request\n");
        else
            printf("SYSTEM: Unfriend success.\n");
        }
    }

/* Control head of status what user want to do/show status/go to next status
 * Argument:
 *      select - select what user want to do
 *               1 for intial status
 *               2 for show status
 *               2 for nexts status
 */
void controlHeadStatus(int select)
    {
    STATUS_T *pStatus = NULL;
    int amount = 0;
    if(lookPending(&amount) != NULL)
        {
        printf("There are %d peoples send pending request to you\n", amount);
        }
    if (select == 1)                    /* Intial status */
        {
        if (statusMenu(1, NULL) == -1)
            printError(1);
        }
    else if (select == 2)                /* Print head status */
        {
        statusMenu(2, &pStatus);
        printf("STATUS:\n");
        printStatus(pStatus);
        printf("\n");
        }
    else if (select == 3)                /* Go to next status */
        {
        headUserInterface();
        statusMenu(3, NULL);
        }
    }

void controlHome()
    {
    controlHeadStatus(1);
    headUserInterface();
    controlSuggestFriend();
    }

/* Control function when user use command exit.
 * If user want to exit free all data. But if not, just go back.
 * Return 1, if user exit. Return 0, If user not exit.
 */
int controlExit()
    {
    int retVal = 0;
    retVal = askExit();
    if (retVal == 0)
        return 0;
    else if (retVal == 1)
        {
        writeDatabase();
        return 1;
        }
    }

/* Control function when we want to know about suggest friends. 
 */
void controlSuggestFriend()
    {
    int i = 0;         /* For loop */
    int suggestF = 0;  /* Amount of suggest friend */
    USER_T **pSuggest = NULL;
    pSuggest = suggestFriend(&suggestF);
    if (suggestF != 0)
        {  /* There is no suggest friend */
        printf("FRIEND SUGGEST:\n");
        for(i = 0; i < suggestF; i++)
            printData(pSuggest[i]);
        free(pSuggest);
        }
    }