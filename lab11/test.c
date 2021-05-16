/******************************************************************************
 *
 *  emergency.c
 *
 *      Simulate a hospital emergency room. This program will read a file
 *      and store each patient in a max heap. The extact the person and
 *      write in output file.
 *
 *          Nathaphop Sundarabhogin ID 60070503420
 *          26 April 2561
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 256

/* Print error message that is a big problem and then exit
 * Argument:
 *      error - Error case
 */
void errorExit(int error)
    {
    printf("#SYSTEM: Program Error!\n");
    if (error == 1) /* Didn't input name of input file or name of output file */
        {
        printf("#SYSTEM: You must include input and output file\n");
        printf("#SYSTEM: Example: ./emergency input.txt output.txt\n");
        }
    else if (error == 2) /* Can't open input file */
        {
        printf("#SYSTEM: Can't open input file\n");
        }
    else if (error == 3) /* Can't open output file */
        {
        printf("#SYSTEM: Can't open output file\n");
        }
    else if (error == 3) /* Can't allocate memory */
        {
        printf("#SYSTEM: Can't allocate memory\n");
        }
    printf("#SYSTEM: Program Exit\n");
    exit(0);
    }

void readFile(FILE* pFile)
	{
	char input[LEN] = {0};
	rewind(pFile);
	while(fgets(input,sizeof(input),pFile) != NULL)
		{
		printf("Read: %s",input);
		if(strlen(input) == 1)
			{
			printf("WTF\n");
			break;
			}
		}
	}

/* Main Program */
int main(int argc, char* argv[])
    {
    char input[LEN] = {0};
    FILE* pOpen = NULL;
    if ((argc < 2) || (argc > 2))   /* Check name of input/output file */
        errorExit(1);
    pOpen = fopen(argv[1],"r");
    if(pOpen == NULL)
    	errorExit(2);
    while(1)
    	{
    	readFile(pOpen);
    	printf("Read or not?\n");
    	fgets(input,sizeof(input),stdin);
    	sscanf(input,"%s",input);
    	if(input[0] == 'Y')
    		continue;
    	else if (input[0] == 'N')
    		{
    		fclose(pOpen);
    		printf("BYE!\n");
    		exit(0);
    		}
    	else
    		printf("Wrong Input!\n");
    	}
    }