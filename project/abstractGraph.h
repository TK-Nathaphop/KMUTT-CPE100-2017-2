
/* Find friend from linked list of friend which the key is E-mail.
 * Arguments:
 *   pHead - Head node of linked list.
 *   pFind - E-mail that we want to find.
 * If found, return address of linked list node back. If not found, Return NULL.
 */
FRIENDLIST_T* findFriend(FRIENDLIST_T *pHead, char *pFind);

/* Add new node to head node of linked list of friend.
 * This function can use with pending friend request.
 * Argument:
 *      pHead - Head node of linked list.
 * Return 1, if success.
 * Return -1, If can't allocate memory.
 * Return 0, if pAdd is NULL.
 */
int pushFriend(FRIENDLIST_T **pHead, USER_T *pAdd);

/* Pop head node of linked list of friend and free node.
 * This function usually uses in pending request.
 * Argument:
 *      pHead - Head node of linked list.
 * Return data in head node.
 * If head node doesn't have any data, Return NULL.
 */
USER_T* popFriend(FRIENDLIST_T **pHead);

/* See data of head node of linked list. But doesn't free node.
 * This function usually uses in pending request.
 * Argument:
 *      pHead - Head node of linked list.
 * Return data in head node.
 * If head node doesn't have any data, Return NULL.
 */
USER_T* peekFriend(FRIENDLIST_T *pHead);

/* Count how many friend in linked list
 * This function can use with pending friend request.
 * Argument:
 *      pHead - Head node of linked list.
 * Return amount of data in linked list.
 */
int countFriend(FRIENDLIST_T *pHead);

/* Delete friend node that we want to remove from linked list.
 * Arguments:
 *      pHead - Head node of linked list.
 *      pDel - User that want to delete node of linked list.
 * Return 1, If delete node success.
 * Return 0, If can't found node in linked list.
 */
int deleteFriend(FRIENDLIST_T **pHead, USER_T *pDel);

/* Write friend relation and pending request into relation file.
 * Arguments:
 *      pData - Data of user that want to write.
 *      pFile - File that want to write.
 */
void writeFriend(USER_T *pData, FILE *pFile);

/* Find friend of friends' user that we want by the maximum of users
 * that is suggested to user is 3.
 * Arguments:
 *     pUser    - Keep data that we want to find friend of friend
 *     pSuggest - Keep friend of friend of user that we want
 * Return 0, if that user does not have friends.
 * Return 1, if there is one friend.
 * Return 2, if there are two friends.
 * Return 3, if there are three friends.
 */
USER_T** findSuggestFriend(USER_T *pUser, int *pSuggestF);