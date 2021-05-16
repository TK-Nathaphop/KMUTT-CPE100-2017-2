#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define LEN 100

/* LOCAL FUNCTION. Remove 'new line' from last character out.
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

int strnum(char text[])
	{
	int i = 0;
	for(i=0; i < strlen(text); i++)
		if(!isdigit(text[i]))
			return 0;
	return 1;
	}

long long int calculate(int n)
	{
	int answer = 0;
	if (n != 0)
		{
		printf("%d! is recursive case. Answer = %d * recursion of %d! Recursion to calculate %d!\n", n, n, n - 1, n - 1);
		printf("Recursion to calculate %d\n", n-1);
		answer = calculate (n-1);
		}
	else if (n == 0)
		{
		printf("0! is base case return answer of 0! = 1\n");
		return 1;
		}
	printf("Calculate %d! complete.\n", n-1);
	printf("\tReturn answer from %d! = %d to calcalate %d! = [%d * %d!] = %d\n", n-1, answer, n, n, n-1, answer*n);
	answer = answer*n;
	return answer;
	}

int main()
	{
	char input[LEN] = {0};
	int n = 0;
	int answer = 0;
	printf("My Recursion Programs.\n");
	printf("Program calculate n! by recursion (n<=15)\n");
	while(1)
		{
		printf("Enter n = ");
		fgets(input, sizeof(input), stdin);
		cutLine(input);
		if((strnum(input)==0) || (strlen(input) == 0))
			printf("Input error, please enter number between 0-15\n");
		else
			{
			sscanf(input,"%d", &n);
			if ((n > 15) || (n < 0))
				printf("Input error, please enter number between 0-15\n");
			else
				{
				answer = calculate(n);
				printf("Complete calculation of %d! , answer = %d\n", n, answer);
				printf("press [y] to continue,  others to exit.");
				fgets(input, sizeof(input), stdin);
				sscanf(input,"%s",input);
				if (!((input[0] == 'y') && (strlen(input) == 1)))
					break;
				}
			}
		}
	printf("End Program.\n Program writen by 60070503420  NATHAPHOP SUNDARABHOGIN\n");
	}