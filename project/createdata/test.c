#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleFacebook.h"
#include "validate.h"
#define LEN 128

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

int main()
    {
    char tagS[LEN] = {"STATUS"};          /* Tag print in front of file */
    char tagC[LEN] = {"COMMENT"};         /* Tag print in front of file */
    char mail[LEN] = {0};
    char input[LEN] = {0};
    USER_T *pData = NULL;
    printf("Size of STATUS: %d\n",sizeof(tagS));
    printf("Size of COMMENT: %d\n",sizeof(tagC));
    printf("Size of mail: %d\n", sizeof(mail));
    printf("Size of STATUS_T: %d\n",sizeof(STATUS_T));
    printf("Size of COMMENT_T: %d\n",sizeof(COMMENT_T));
    pData = (USER_T*)calloc(1,sizeof(USER_T));
    if(pData == NULL)
        {
        printf("ERROR\n");
        exit(0);
        }
    fgets(input,sizeof(input),stdin);
    sscanf(input,"%s",pData->mail);
    strcpy(mail,pData->mail);
    printf("pData->mail: %s\n",pData->mail);
    printf("mail: %s\n",mail);
    free(pData);
    }