/* This demo illustrates how binary search works.
 * It uses a fixed list of strings as the data 
 * which is assumed to be sorted.
 *
 *   Created by Sally Goldin, 17 March 2017 for CPE111
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5000

/* Binary search through a list of strings 
 *   target     - word we are looking for
 *   strings[]  - array of strings, assumed to be sorted in ascending order
 *   count      - number of items in the array
 *   pCompare   - return number of comparisons (for demonstration purposes)
 * Returns location in the array where the target was found
 *   or -1 if not found.
 */
int binarySearch(char* target, char* strings[],int count, int* pCompare)
{
  int found = -1;
  int start = 0;
  int end = count - 1;
  int mid;
  int compareResult = 0; 
  *pCompare = 0;
  while ((start <= end) && (found < 0))
     {
     mid = start + (end - start)/2;
     /* Look to see if the string in array begins with the target */
     compareResult = strncmp(target,strings[mid],strlen(target));
     *pCompare = *pCompare + 1;
     if (compareResult == 0)  /* match! */
        {
	found = mid;
        }
     else if (compareResult < 0) /* word is earlier than mid - look in first half of list */
        {
	end = mid-1;
        }
     else  /* word is later than mid - look in second half */
        {
	start = mid + 1;
        }
     }
  return found;
}


/* main initializes and reads the input file into an array of
 * pointers to chars. Then asks the user to enter strings to
 * search for. 
 */
int main()
{
  FILE* pFp = NULL;
  char * sortedStrings[MAX]; /* assume we know max # of strings */
  int stringCount = 0;        /* count number of actual strings */
  int i;
  char input[512];            /* buffer for reading */
  char word[256];             /* word for searching */
  pFp = fopen("wordlist.txt","r");
  if (pFp == NULL)
    {
    printf("Cannot open input file 'wordlist.txt' - exiting\n");
    exit(1);
    }
  while ((fgets(input,sizeof(input),pFp) != NULL) && (stringCount < MAX))
    {
    if (input[strlen(input)-1] =='\n')
        input[strlen(input)-1] = '\0';
    sortedStrings[stringCount] = strdup(input);
    if (sortedStrings[stringCount] == NULL)
        {
        printf("Memory allocation failure - exiting\n");
	exit(2);
	}
    stringCount++;
    }
  fclose(pFp);
  printf("Read %d words from the file\n",stringCount);
  while (1)   /* continue asking for words until user enters empty string */
    {
    int foundIndex;
    int comparisons;
    memset(input,0,sizeof(input));
    memset(word,0,sizeof(word));
    printf("Enter word to search for: ");
    fgets(input,sizeof(input),stdin);
    sscanf(input,"%s",word);
    if (strlen(word) == 0)
         break;
    /* otherwise */
    foundIndex = binarySearch(word,sortedStrings,stringCount,&comparisons);
    if (foundIndex < 0)
       {
       printf("Word '%s' not found after %d comparisons\n", word,comparisons);
       }
    else
       {
       printf("Word '%s' found in %d comparisons\n", word,comparisons);
       printf("%s\n\n",sortedStrings[foundIndex]);
       }
    }
  /* free strings, just to be totally correct */
  for (i=0; i < stringCount; i++)
    if (sortedStrings[i] != NULL)
      free(sortedStrings[i]);

 }
