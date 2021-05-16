/******************************************************************************
 *
 *  postFixEval.c
 *
 *      Get Postfix mathematic and then calculate the answer then print the
 *      result to user. If user input 'DONE', exit program.
 *
 *          Created by Nathaphop Sundarabhogin ID 60070503420
 *          6 February 2018
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "abstractStack.h"
#define LEN 128

/* Get error case and print each error message
 */
void printError(int error)
    {
    if (error == 1)         /* Have a problem to allocate new memory */
        {
        printf("Error: Can't allocate new memory. Program Exit\n");
        exit(0);
        }
    else if (error == 2)    /* Program Underflow */
        {
        printf("Error: Program underflow please try again\n");
        }
    else if (error == 3)    /* Divide by 0 */
        printf("Error: Can't divide by 0\n");
    else if (error == 4)    /* There are number left in stack */
        printf("Error: Please check your prefix expression again\n");
    }

/* Get string and remove 'new line(\r\n)' from last character out.
 */
void cutLine(char *string)
    {
    char *pCut;    /* Get string after found <CR>. */
    pCut = strpbrk(string,"\r\n");
    if (pCut != NULL)
        *pCut = '\0';
    }

/* Get string and check that it's number or not. If it's number, return 1.
 * But if not, return 0.
 */
int checkNum(char* str)
    {
    int i = 0;      /* Count loop */
    for (i = 0; i<strlen(str); i++)
        {
        /* First condition for negative number */
        if ((str[0] == '-') && (strlen(str) > 1))
            continue;
        else if (!isdigit(str[i]))
            return 0;
        }
    return 1;
    }

/* Get 2 numbers and symbol then check what symbol it is, calculate it and return
 * result. (Notice that "number1 symbol number2"
 */
int calculate(int number1, char symbol, int number2)
    {
    if (symbol == '+')
        return number1 + number2;
    else if (symbol == '-')
        return number1 - number2;
    else if (symbol == '*')
        return number1 * number2;
    else if (symbol == '/')
        return number1 / number2;
    else /* If it's not anything (Error case) */
        return 0;
    }

/* Get string of postfix expression and calcaulte postfix expression (By using
 * Stack structure to keep data). Then return a result back. If there is some
 * error, change the first char of string to 'F' and return 0.
 */
int evaluatePostfix(char *postfix)
    {
    char *pToken = NULL;    /* Get Token from 'strtok' */
    char *pString1 = NULL;  /* Temporary keep data before push and get data
                               after pop */
    char *pString2 = NULL;  /* Get data after pop */
    char temp[LEN] = {0};   /* Temporary keep string */
    int number1 = 0;        /* Keep the first number before calculate */
    int number2 = 0;        /* Keep the second number before calculate */
    int result = 0;         /* Keep the result after calculate */
    pToken = strtok(postfix, " ");
    if(pToken == NULL)
        return 0;
    stackClear();   /* Clear all of stack before start keep stack */
    while(pToken != NULL)
        {
        if (checkNum(pToken))   /* If it's number keep in stack */
            {
            pString1 = strdup(pToken);
            if(pString1 == NULL)    /* Check allocated error */
                printError(1);
            else if(push(pString1) == 0)    /* If push error, allocated error. */
                printError(1);
            }
        else    /* Else, it's symbol */
            {
            /* Get data from stack */
            pString2 = pop();
            pString1 = pop();
            /* If can't get data, that mean data underflow. */
            if ((pString1 == NULL) || (pString2 == NULL))
                {
                printError(2);
                postfix[0] = 'F';
                return 0;
                }
            /* Change from string to integer and free data. */
            sscanf(pString2, "%d", &number2);
            sscanf(pString1, "%d", &number1);
            free(pString1);
            free(pString2);
            /* If divide by 0, it can't calculate */
            if (*pToken == '/' && number2 == 0)
                {
                printError(3);
                postfix[0] = 'F';
                return 0;
                }
            /* Send ot calculate, change to string and keep in stack. */
            result = calculate(number1, *pToken, number2);
            sprintf(temp, "%d",result);
            pString1 = strdup(temp);
            if(pString1 == NULL)    /* Can't allocate memory */
                printError(1);
            if(push(pString1) == 0) /* If push error, allocated error. */
                printError(1);
            }
        pToken = strtok(NULL, " ");
        }
    pString1 = pop();   /* Pop the result */
    sscanf(pString1, "%d", &result);
    /* If there're any data left in stack, prefix expression error */
    if(pop() != NULL)
        {
        printError(4);
        postfix[0] = 'F';
        return 0;
        }
    return result;
    }

/* MAIN FUNCTION. Asked user to input postfix expression and send to calculate.
 * Then print result to user. If user input 'DONE', program exit.
 */
int main()
    {
    char input[LEN] = {0};  /* Get input from terminal line */
    int result = 0;         /* Get the result */
    printf("Welcome to PostFixEval\n");
    while (1)
        {
        memset(input, 0, sizeof(input));
        printf("Enter a postfix expression:");
        fgets(input, sizeof(input), stdin);
        cutLine(input); /* Send to cut '\r\n' */
        /* If use input 'done', exit program */
        if (strcasecmp(input, "done") == 0)
            {
            printf("Bye!\n");
            exit(0);
            }
        else   /* Otherwise, send to calculate */
            {
            result = evaluatePostfix(input);
            if (input[0] != 'F')    /* If there isn't any error, print result */
                printf("%d\n",result);
            }
        }
    }