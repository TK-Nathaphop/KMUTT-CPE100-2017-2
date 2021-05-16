/* strtok example */
#include <stdio.h>
#include <string.h>

int main ()
    {
    char str[] ="- This, a sample string.";
    char * pch;
    int i = 0;
    printf ("Splitting string \"%s\" into tokens:\n",str);
    /* Loop print to know each address of 'str' */
    for (i=0;i<strlen(str);i++)
        {
        if (str[i] == '\0')
            printf("Address of \\0: %p\n",&str[i]);
        /* The last character of each word is SPACEBAR not \0 */
        if(str[i] == ' ')
            printf("Address of spacebar:%p\n",&str[i]);
        else    /* Otherwise it's character */
            printf("Address of %c: %p\n",str[i],&str[i]);
        }
    printf("\n");
    pch = strtok (str," ");
    while (pch != NULL)
      {
      for (i=0;i<strlen(pch)+1;i++)
        {
        if (pch[i] == '\0')
            printf("Address of \\0: %p\n",&pch[i]);
        /* The last character of each word is SPACEBAR not \0 */
        else if(pch[i] == ' ')
            printf("Address of spacebar:%p\n",&pch[i]);
        else    /* Otherwise it's character */
            printf("Address of %c: %p\n",pch[i],&pch[i]);
        }
      pch = strtok (NULL, " ,.-");
      }
    printf("Finished:%s\n",str);
    return 0;
    }