/******************************************************************************
 *
 *  validate.c
 *
 *      This module working for validate data/ checking correctness.
 *
 *      Created by Nathaphop Sundarabhogin (KLA)    ID : 3420
 *      18 April 2018
 *
 ******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "simpleFacebook.h"

/* Get the date to day and current time.
 * ARGUMENT:
 *     date - Date that return [0] - day, [1] - month, [2] - year, [3] - hour, [4] - minute.
 */
void dateToday(int date[])
    {
    char input[LEN] = {0}; /* Get input from date. */
    time_t t = time(NULL);
    struct tm * tm = localtime(&t);
    /* Get current day. */
    strftime(input, sizeof(input), "%d", tm);
    sscanf(input, "%d", &date[0]);

    /* Get current month. */
    strftime(input, sizeof(input), "%m", tm);
    sscanf(input, "%d", &date[1]);

    /* Get current year. */
    strftime(input, sizeof(input), "%G", tm);
    sscanf(input, "%d", &date[2]);

    /* Get current hour. */
    strftime(input, sizeof(input), "%H", tm);
    sscanf(input, "%d", &date[3]);

    /* Get current minute. */
    strftime(input, sizeof(input), "%M", tm);
    sscanf(input, "%d", &date[4]);
    return;
    }

/* Validate and check command  which type of command is.
 * Arguments:
 *      pCheck - String that we want to check.
 *      pReturn -  String that we want to return
 * Return type of enum command.
 */
COMMAND_TYPE checkCommand(char *pCheck, char *pReturn)
    {
    char *pCut = strchr(pCheck, ' ');    /* Get address after spacebar */
    /* Array of command which arrange follow enum */
    char command[][LEN] = {"","/s", "/c", "/find", "/home", "/help", "/next",
                           "/pending", "/profile", "/signout", "/acceptf",
                           "/denyf", "/addfriend", "/unfriend"};
    int i = 0;
    /* First character isn't slash or have only one charater, command error. */
    if ((pCheck[0] != '/') || (strlen(pCheck) == 1))
        return C_ERROR;
    /* Have some text after command */
    if (pCut != NULL)
        {
        *pCut = '\0';
        pCut = pCut + 1;
        }
    for(i = 1; i < 14; i++)
        {
        if(strcasecmp(pCheck, command[i]) == 0)
            {
            /* For command that DON'T have text follow */
            if (i > 3)
                {
                /* Only '/s', '/c', '/find' that have text follow */
                if (pCut != NULL)
                    return C_ERROR;
                }
            /* For command that have text follow */
            else if (i <= 3)
                {
                /* '/s', '/c' and '/find' must have text follow */
                if (pCut == NULL)
                    return C_ERROR;
                else
                    {
                    if(strlen(pCut) == 0)
                        return C_ERROR;
                    strcpy(pReturn, pCut);
                    }
                }
            return i;   /* Command correct. */
            }
        }
    /* Otherwise, command error */
    return C_ERROR;
    }