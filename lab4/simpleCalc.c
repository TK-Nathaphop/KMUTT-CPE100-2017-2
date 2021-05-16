/*
 *   simpleCalc.c
 *
 *   This program uses a stack to convert an arithmetic expression in
 *   infix notation to one that is in post-fix notation.
 *
 *   In lab, students will expand this to use a stack in order
 *   to calculate the value as well.
 *
 *   Created by Sally Goldin, 26 December 2011 for CPE 113
 *   Modified 18 Jan 2012 to provide a sample solution for Lab 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "abstractStack.h"

#define OPENPAREN   1
#define CLOSEPAREN  2
#define OPERATOR    3
#define NUMBER      4


int convertToPostfix(char* infix, char* postfix);
int evaluatePostfix(char* postfix);
int validateExpr(char* infix);
int charType(char cval,char** asString);

int bTrace = 0;    /* allow user to control tracing */

/* Main function repeatedly asks the user for an expression
 * then converts and evaluates it.
 */
int main(int argc, char* argv[])
{
    char infixExpr[128];    /* will hold our infix expression */
    char postfixExpr[128];  /* we will build our post fix expression here */
    int bDone = 0;
    int bOk = 1;            /* record format error */    
    int result = 0;
    printf("Welcome to simpleCalc. This program can evaluate arithmetic expressions\n");
    printf("   that use  +, -, *, /, parentheses and integer numbers.\n");
    printf("   You must use parentheses around all groupings\n");
    printf("   For example:  (((6 + 7) * (22 - 5))/ 3)\n\n");
    printf("To trace the stack operations, run as './simpleCalc T'\n\n");
    if ((argc > 1) && ((argv[1][0] == 't') || (argv[1][0] == 'T')))
	bTrace = 1; 
    while (!bDone)
       {
       printf("Enter expression to evaluate. Leave blank to exit: ");
       fgets(infixExpr,sizeof(infixExpr),stdin);
       if (infixExpr[strlen(infixExpr)-1] == '\n')  /* get rid of newline */
           infixExpr[strlen(infixExpr)-1] = '\0';
       if (strlen(infixExpr) == 0)
           break;
       bOk = convertToPostfix(infixExpr,postfixExpr);
       if (!bOk)
          {
	  printf("Invalid expression - please try again\n\n");
          }
       else
	  {
	  printf("Infix expression: %s\n",infixExpr);
	  printf("Postfix expression: %s\n",postfixExpr);
          result = evaluatePostfix(postfixExpr);
	  printf("Value of expression: %d\n\n",result);
          } 
       }
}    
    
/*  Convert a string holding an infix expression to a postfix expression.
 *  Arguments
 *    infix      -    String holding infix expression
 *    postfix    -    Result of conversion.
 *  Returns 1 if infix expression okay, 0 if there's something invalid
 *    such as an illegal character or non-matching parentheses
 */
int convertToPostfix(char* infix, char* postfix)
{
    int bOk = 1;
    int i = 0;    /* char counter for infix string */
    int p = 0;    /* char counter for postfix string */
    char cval = 0;
    char * pushString = NULL;
    char * popString = NULL;
    int type = 0;
    bOk = validateExpr(infix);
    if (bOk) 
       {
       if (bTrace)
	   printf("  Converting: %s\n", infix);
       stackClear();     /* empty out the stack */
       for (i = 0; i < strlen(infix); i++)
          {
   	  cval = infix[i];
          type = charType(cval,&pushString);
          switch (type)
	     {
	     case OPENPAREN:   
		 /* push paren on to stack */
		 if (push(pushString) == 0)
		     {
		     printf("ERROR - stack overflow\n");
		     return 0;
		     }
		 if (bTrace)
                     printf(" --- Open paren - pushing onto stack\n");
		 break;
	     case CLOSEPAREN:
		 /* free the pushString - we won't need it */
		 if (bTrace)
                     printf(" --- Close paren\n");
		 free(pushString);
		 pushString = NULL;
		 /* pop from the stack */
		 popString = pop();
		 if (bTrace)
                     printf(" ------ popped %s\n",popString);
		 while ((popString != NULL) && (popString[0] == '('))
		     {
		     free(popString);
		     popString = pop();
                     if (bTrace)
                         printf(" ------ popped %s\n",popString);
		     }
		 if (popString != NULL)
		     {
		     postfix[p] = 0x20;   /* add a space */  
                     p++;
		     postfix[p] = popString[0];  /* then the operator */
		     p++;
		     if (bTrace)
                        printf(" ------ added %s to result\n",popString);
		     free(popString);
		     popString = NULL;          
		     }
		 break;
	     case OPERATOR:    
		 /* push operator onto the stack */
		 if (bTrace)
                     printf(" --- Operator - pushing onto stack\n");
		 if (push(pushString) == 0)
		     {
		     printf("ERROR - stack overflow\n");
		     return 0;
		     }
                 /* also add a space to the output */
		 postfix[p] = 0x20;  /* add the number to the expression */
		 p++;
		 break;
	     case NUMBER:     
		 /* add the number to the output */
		 free(pushString); /* we don't need it */
		 if (bTrace)
                    printf(" --- Number [%c] - copying to output\n",cval);
		 postfix[p] = cval;  /* add the number to the expression */
		 p++;
		 break;
             default:      /* space - just discard */
		 free(pushString);
	     }
          } 
       }
    /* When we finish, the stack may not be empty */
    /* There may be extra operators or open parens */
    if (bTrace)
       {
       printf("At the end of convertToPostfix, stack size is: %d\n",
           stackSize());
       }
    while ((popString = pop()) != NULL)
       {
       if (bTrace)
           printf("    Popped: %s\n", popString);
       cval = popString[0];
       free(popString);
       popString = NULL;
       type = charType(cval,&pushString);
       if (type == OPERATOR)
           {
           postfix[p] = ' ';
           p++;
           postfix[p] = cval;
           p++;
           }
       free(pushString);
       } 

    /* add the final zero terminator */
    postfix[p] = '\0';
    return bOk;
}


/*  Check that an infix expression is valid. This does not
 *  do a complete check, only makes sure that there are no
 *  illegal characters and that the parentheses are balanced
 *  Arguments
 *     infix   -  expression to check
 *  Returns 1 if valid, 0 if not
 */
int validateExpr(char* infix)
{
    int bOk = 1;
    int c = 0;   /* counter for chars */
    char cval = 0;
    int parenCount = 0;
    for (c = 0; (c < strlen(infix)) && (bOk); c++)
       {
       cval = infix[c];
       if (!strchr("()0123456789+-*/ ",cval))
          {
	  bOk = 0;  /* some illegal character */
          }
       else if (cval == '(')
          {
	  parenCount++;
          }
       else if (cval == ')')
          {
	  parenCount--;
          }
       }
    if (parenCount != 0)
	bOk = 0;  /* unbalanced parentheses */
    return bOk;
}


/* Test to see what kind of character the argument
 * cval is. Returns a constant from 1 to 4 (see values above).
 * Also allocates a string to hold the character so we can push
 * it onto the stack.
 * Arguments 
 *   cval     - character to test
 *   asString - allocated memory to push onto the stack
 */
int charType(char cval, char** asString) 
{
    int retval = 0;
    char* newString = calloc(2,sizeof(char));
    newString[0] = cval;
    *asString = newString;
    if (cval == '(')
	retval = OPENPAREN;
    else if (cval == ')')
	retval = CLOSEPAREN;
    else if (strchr("+-*/",cval) != NULL)
	retval = OPERATOR;
    else if (isdigit(cval))
	retval = NUMBER;
    return retval;
    /* Note if the character is a space, we will return
     * a zero. We'll just skip this
     */
}


/* Evaluates a postfix expression using a stack
 * This code will be provided by the student 
 * Argument
 *   postfix   -  postfix expression to be evaluated 
 * Returns the calculated result. 
 */
int evaluatePostfix(char* postfix)
{
    int result = 0;
    /* WRITE YOUR CODE HERE */

    return result;
}
