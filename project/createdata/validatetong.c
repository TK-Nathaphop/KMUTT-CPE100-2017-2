/******************************************************************************
 *
 *  validate.c
 *
 *      This module is for validating data/checking correctness.
 *
 *  Created by Natthawat Tungruethaipak (Tong)    ID : 3426
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

/***************************** LOCAL FUNCTION ********************************/

/* LOCAL FUNCTION.
 * This program compares two strings and tell the user whether it's the same or not 
 * Arguments:
 *     input - Keep a mail from user
 *     exist - Keep the right tld that we have
 * Return 0, If both strings are not the same.
 * Return 1, If both strings are the same.
 */
int _compare(char *pInput, char *pExist)
    {
    int bOk = 1;
    int count = 0;                  /* For loop */
    if (strlen(pInput) == strlen(pExist))
        {
        while (count < strlen(pInput))
            {
            if (pInput[count] != pExist[count])     
                bOk = 0;   /* If a character is not the same, this string is different */
            count++;
            }
        }
    else
        bOk = 0;
    return bOk;
    }

/* LOCAL FUNCTION.
 * Check the tld of mail from user. This program will check whether the tld
 * of the program exist or not.
 * Arguments:
 *     pMail    - Keep a mail from a user
 *     pTldType - Keep what type of tld
 * Return 0, The tld of mail is incorrect.
 * Return 1, The tld of mail is correct.
 */
int _tldCheck(char *pMail, int *pTldType)
    {
    int bOk = 0;
    int count = 4;                             /* For loop */
    int tld4Check = 0;                         /* Is tld with 4 char? */
    int tld6Check = 0;                         /* Is tld with 6 char? */
    char *pTld4Char[2] = {".net", ".com"};     /* Group of tld with 4 char */
    char *pTld6Char[2] = {".co.th", ".ac.th"}; /* Group of tld with 6 char */
    char in4TLD[4] = {0};                      /* Input tld with 4 char */
    char in6TLD[6] = {0};                      /* Input tld with 6 char */
    while (count > 0)
        {
        /* Get input tld from mail string(4 char) */
        in4TLD[4 - count] = pMail[strlen(pMail) - count];
        count -= 1;
        }
    count = 6;
    while (count > 0)
        {
        /* Get input tld from mail string(6 char) */
        in6TLD[6 - count] = pMail[strlen(pMail) - count];
        count -= 1;
        }
    count = 0;
    in4TLD[4] = '\0';
    in6TLD[6] = '\0';
    while (count < 2)
        {
        /* Check the tld (4 char) is valid or not */
        bOk = _compare(in4TLD, &pTld4Char[count][0]);
        if (bOk)
            { 
            tld4Check = 1;   
            *pTldType = 4;      /* Determine what the type of tld */
            break; 
            }
        /* Check is the tld valid or not */
        bOk = _compare(in6TLD, &pTld6Char[count][0]);
        if(bOk)
            { 
            tld6Check = 1;    
            *pTldType = 6;       /* Determine what the type of tld */
            break; 
            }
        count++;
        }
        if(!bOk)
            return 0;  /* If the tld is invalid then email is invalid */
    return 1;
    }

/* LOCAL FUNCTION.
 * Check the dot detail. This program will make sure that the dot will not
 * close to special symbol.
 * Argument:
 *     pMail - Keep mail from user
 * Return 0, If the dot is not close to special symbol.
 * Return 1, If the dot is close to special symbol.
 */
int _dotDetailCheck(char *pMail)
    {
    int count = 1;                  /* Start at the second character */
    int type = 0;                   /* Type of character */
    int forType = 0;                /* Type of forward character */
    int backType = 0;               /* Type of backward charater */
    while (count < strlen(pMail))
        {
        type = isalnum(pMail[count]); 
        forType = isalnum(pMail[count + 1]);
        backType = isalnum(pMail[count - 1]);
        if (type == 0)
            { /* The character is not alphabet or numeric */
            /* The previous and next character is not alphabet or numeric */
            if (forType == 0 || backType == 0)
                return 0; 
            }   
        count++;
        }
    return 1;
    }   

/* LOCAL FUNCTION.
 * Check the part of mail after address(@).
 * This program will check whether the second part of mail is valid or not
 * Arguments:
 *     pMail   - Keep mail from user
 *     tldType - Check what type of tld 
 * Return 0, if the second part mail is incorrect.
 * Return 1, if the second part mail is correct. 
 */
int _secondPartEmailCheck(char *pMail, int tldType)
    {
    int count = 0;               /* For loop */
    int countAlpha = 0;          /* Count the alphabet */
    int begin = count;           /* Determine where the second part start */
    while (count < strlen(pMail))
        {
        if(pMail[count] == '@')
            break;    /* Determine where the second part start */
        count++;
        }
    count++;
    while (count < strlen(pMail) - tldType)
        {
        /* Condition of the character is the alphanumeric, - and . */
        if ((isalnum(pMail[count]) || (pMail[count] == '-') || (pMail[count] == '.')))
            {
            if (isalpha(pMail[count]))
                countAlpha++;
            }
            /* If character other than these, it's valid and out of loop */
            else
                return 0;
            count++;
        }
    /* There is no alphabet */
    if (countAlpha == 0)
        return 0;
    return 1;
    }


/* LOCAL FUNCTION.
 * Check the part of email before address (@).
 * This function will check the part of mail before @ whether it is valid or not.
 * Argument:
 *     pMail - Keep mail from user
 * Return 0, if the first part mail is incorrect.
 * Return 1, if the first part mail is correct.
 */
int _firstPartEmailCheck(char *pMail)
    {
    int count = 0;             /* For loop */
    int countAlpha = 0;        /* Count a letter in string */
    int countAddress = 0;      /* Count the address (@) */
    while (count < strlen(pMail))        /* Check until it reach the end of string */
        {
        /* Condition of character for the alphanumeric, '-', '_', and '.'' */
        if ((isalnum(pMail[count]) || (pMail[count] == '-') || (pMail[count] == '_')
            ||(pMail[count] == '.')) && isalnum(pMail[0]))
            {
            if (isalpha(pMail[count]))
                countAlpha++;
            }
        /* If the character is '@' then stop checking */
        else if((pMail[count] == '@') && (isalnum(pMail[0])))
            {
            countAddress++;
            break;
            }
        /* If the character is other than these, invalid */
        else
            return 0;
        count++;
        }
    /* If there is no alphabet or @, then it's invalid */
    if((countAddress == 0) || (countAlpha == 0))
        return 0;
    return 1;
    }

/* LOCAL FUNCTION.
 * Check phone number of Thai people. 
 * Argument:
 *     string - Keep phone number from a user
 * Return 0, if phone number is incorrect.
 * Return 1, if phone number is correct.
 */
int _checkMobilenumber(char string[128])
    {
    if(string[1] == '6')
        {
        if(string[2] != '6' && string[2] != '7' && string[2] != '9')
            return 1;
        return 0;
        }
    else if(string[1] == '8' || string[1] == '9')
        return 1;
    return 0;
    }

/* LOCAL FUNCTION.
 * Check the character is digit or not
 * Argument:
 *     string - Keep phone number from user
 * Return 0, if phone number is incorrect.
 * Return 1, if phone number is correct.
 */
int _checkDigit(char *pString)
    {
    int i = 0;    /* For loop */
    for (i = 0; i < strlen(pString); i++)
        {
        if (isspace(pString[i]))       /* There is spacebar */
            return 0;
        else if (!isdigit(pString[i])) /* There is an alphabet or puntuation */
            return 0;
        }
    return 1;
    }

/**************************** PUBLIC FUNCTION ********************************/

/* Get the date to day and current time.
 * Argument:
 *     date - Date that return [0] - day, [1] - month, [2] - year, [3] - hour, [4] - minute
 */
void dateToday(int date[])
    {
    char input[LEN] = {0}; /* Get input from date */
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

/* LOCAL FUNCTION.
 * Compare date now and input.
 * Argument:
 *     date - Date to check
 * date[0] = day, date[1] = month, date[2] = year
 * Return 0 if date is after current
 * Return 1 if date is before current
 */
int _dateBirthCompare(int date[])
    {
    int today[5];
    dateToday(today);
    //today[0] = day, today[1] = month, today[2] = year
    /* year input is earlier than now */
    if (date[2] < today[2])
        return 1;
    else if (date[2] == today[2])
        {
        if (date[1] < today[1])
            return 1;
        else if (date[1] == today[1])
            {
            if (date[0] < today[0])
                return 1;
            else if (date[0] == today[0])
                return 1;
            }
        }
    return 0;
    }

/* Validate and check a command which type of command is.
 * Arguments:
 *      pCheck -  Keep string that we want to check
 *      pString -  Keep string that we want to return
 * Return type of enum command.
 */
COMMAND_TYPE checkCommand(char *pCheck, char *pString)
    {
    char *pCut = strchr(pCheck, ' ');    /* Get address after spacebar */
    /* Array of command which arrange follow enum */
    char command[][LEN] = {"","/s", "/c", "/find", "/home", "/help", "/next",
                           "/pending", "/profile", "/signout", "/acceptf",
                           "/denyf", "/addfriend", "/unfriend"};
    int i = 0; /* For loop */
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
                    strcpy(pString, pCut);
                }
            return i;   /* Command correct. */
            }
        }
    /* Otherwise, command error */
    return C_ERROR;
    }

/* Validate a mail of user.
 * Argument:
 *     pString - Keep mail from user that we want to validate
 * Return 0, if the mail is invalid.
 * Return 1, if the mail is valid.
 */
int validateMail(char *pString)
    {
    int i = 0;          /* For loop */
    int bOk = 0;
    int countSpace = 0; /* Count a space bar */
    int tldType = 0;    /* Type of tld */
    for (i = 0; i < strlen(pString); i++)
        {
        if (isspace(pString[i]))
            countSpace++;
        }
    if (countSpace != 0)
        return 0;
    bOk = _firstPartEmailCheck(pString);               /* Check the string before address (@) */
    printf("1 : %d\n", bOk);
    if (bOk)
        bOk = _tldCheck(pString, &tldType);            /* Check for tld */
    printf("2 : %d\n", bOk);
    if (bOk)
        bOk = _secondPartEmailCheck(pString, tldType); /* Check the string after address (@) */
    printf("3 : %d\n", bOk);
    if (bOk)
        bOk = _dotDetailCheck(pString);                /* Check for dot */
    printf("4 : %d\n", bOk);
    return bOk;
    }

/* Validate phone number of user.
 * Argument:
 *     pString - Keep phone number from a user that we want to validate
 * Return 1, if phone number is correct.
 * Return 2, if phone number is not format.
 *     - The length of phone number is 10
 *     - The first character is not 0
 * Return 3, if phone number is not digit.
 * Return 4, if phone number is not Thai number.
 * (Thai phone number starts with 066 067 069 08 and 09) 
 */
int validatePhone(char *pString)
    {
    if (strlen(pString) != 10)          /* The length of phone number is not 10 */
        return 2;
    if (pString[0] != '0')              /* Phone number doesn't start with 0 */
        return 2;
    if (!_checkDigit(pString))          /* Phone number is not digit */
        return 3;
    if (!_checkMobilenumber(pString))   /* Phone number is not Thai number */
        return 4;
    return 1;
    }

/* Validate name of user.
 * Argument:
 *     pString - Keep name of user that we want to validate
 * Return 0, if name of user is incorrect.
 * Return 1, if name of user is correct.
 */
int validateName(char *pString)
    {
    int i = 0;              /* For loop */
    char temp[LEN] = {0};   /* Keep string temporary */
    strcpy(temp, pString);
    /* Loop check that character in name is allow or not. */
    for(i = 0; i < strlen(temp); i++)
        {
        if (!((isalpha(temp[i])) || (temp[i] == '\'') || 
            (temp[i] == '-') || (temp[i] == '.') || 
            ((isspace(temp[i])) && (isalpha(temp[i+1])))))
            return 0;   
        }
    if(islower(temp[0]))
        temp[0] = toupper(temp[0]);
    strcpy(pString,temp);
    return 1;
    }

/* Check day, month, year and time that they exist or not.
 * Argument:
 *     date[] - date of date
 * Return 0, if date is incorrect.
 * Return 1, if date is correct.
 */
int validateBirthDate(int date[])
    {
    int bOk = 0;
    if ((date[0] == 0) || (date[1] == 0) || (date[2] == 0))
        return 0;
    /* Check month that have 30 days */
    if ((date[1] == 4) || (date[1] == 6) || (date[1] == 9)
        || (date[1] == 11))
        {
        if ((date[0] >=1) && (date[0] <= 30))
            bOk = _dateBirthCompare(date);
        }
    /* Check February month. First check leap year, and then check days */
    else if (date[1] == 2)
        {
        /* Leap year */
        if (((date[3] % 4) == 0) && ((date[0] >= 1) && (date[0] <= 29)))
            bOk = _dateBirthCompare(date);
        /* Common year */
        else if (((date[3] % 4) != 0) && ((date[0] >= 1) && (date[0] <= 28)))
            bOk = _dateBirthCompare(date);
        }
    /* Check month that have 31 days */
    else
        {
        if ((date[0] >= 1) && (date[0] <= 31))
            bOk = _dateBirthCompare(date);
        }
    return bOk;
    }

/* Validate password of user.
 * Argument:
 *      pString - Keep password that we want to validate
 * Return 1, if password is valid.
 * Return 2, if the length of password is too long.
 * Return 3, if user get a spcial symbol.
 */
int validatePassword(char *pString)
    {
    int i = 0;      /* For loop */
    int space = 0;  /* Count space bar */
    int digit = 0;  /* Count digit */
    int upper = 0;  /* Count upper character */
    int lower = 0;  /* Count lower character */
    if (strlen(pString) < 8 || strlen(pString) > 16) /* The length of phone number is not between 8 to 16 */
        return 2;
    for (i = 0; i < strlen(pString); i++)
        {  
        if ((pString[i] == '?') || (pString[i] == '@') || (pString[i] == '%')
            || (pString[i] == '#') || (pString[i] == '$'))
            return 3;               /* There is a special symbol */
        if (isdigit(pString[i]))    /* User gets a number */
            digit++;
        if (isupper(pString[i]))    /* User gets a upper case */
            upper++;
        if (islower(pString[i]))    /* User gets a lower case */
            lower++;
        if (isspace(pString[i]))    /* User gets a space bar */
            space++;
        }
    if(digit != 0 && upper != 0 && lower != 0 && space != 0)
        return 1;
    }