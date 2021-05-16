/* Return the lastest status back.
 * If not have status to display, return NULL.
 */
STATUS_T *getStatus();

/* Set lastest stauts to next status of linked list.
 * Then sorting status.
 */
void nextStatus();

/* Clear array of status and set amount of friend to 0.
 */
void clearStatus();

/* Free all status and comment in linked list
 * Arguments:
 *      pHead - Head node of status that we want to delete
 */
void freeStatus(STATUS_T *pHead);

/* Add new status into linked list status of user
 * Arguments:
 *      pUser - User that want to add a new status
 *      pNew - New status that want to add
 *      select - Select to add to head node or tail node of status
 *               1 - Add to head, 2- Add to tail
 */
void addStatus(USER_T *pUser, STATUS_T *pNew, int select);

/* Add new comment into linked list comment of status
 * Arguments:
 *      pUser - User that want to add a new status
 *      pNew - New status that want to add
 */
void addComment(STATUS_T* pStatus, COMMENT_T *pNew);

/* Intial array of stautus steady for display.
 * Get amount of friend and calloc array of status 
 * and get status from each friend.
 * Argument:
 *      pUser - User that we want to get status from friend list
 * Return 1, when get status success.
 * Return 0, if don't have any friend.
 * Return -1, if can't calloc array.
 */  
int initialStatus(USER_T *pUser);

/* Write status and comment into status file
 * Argument:
 *      pData - Data that we want to write down status into file
 *      pFile - File that we want to write
 */
void writeStatus(USER_T *pData, FILE *pFile);