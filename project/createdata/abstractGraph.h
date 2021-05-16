/* Find friend from linked list of friend. The key is E-mail.
 * Arguments:
 *   pHead - Head node of linked list.
 *   pFind - Node that we want to find by use Email of user.
 * If found, return address of node back. If not found, Return NULL.
 */
FRIENDLIST_T* findFriend(FRIENDLIST_T *pHead, char *pFind);

/* Add new node to head node of linked list of friend.
 * This function can use with pending friend request.
 * Arguments:
 *    pHead - Head node of linked list.
 * Return 1, if success. Return -1, If can't allocate memory.
 * Return 0, if pAdd is NULL.
 */
int pushFriend(FRIENDLIST_T **pHead, USER_T *pAdd);

/* Pop head node of linked list of friend and free node.
 * This function usually uses in pending request.
 * Arguments:
 *      pHead - Head node of linked list.
 * Return data in node. If 'pHead' doesn't have any data, Return NULL.
 */
USER_T* popFriend(FRIENDLIST_T **pHead);

/* See data head node of friend. But not free linked list
 * This function usually uses in pending request.
 * Arguments:
 *      pHead - Head node of linked list.
 * Return data in node. If 'pHead' doesn't have any data, Return NULL.
 */
USER_T* peekFriend(FRIENDLIST_T *pHead);

/* Count how many friend in linked list
 * This function can use with pending friend request.
 * Arguments:
 *      pHead - Head node of linked list.
 * Return data in node. If 'pHead' doesn't have any data, Return NULL.
 */
int countFriend(FRIENDLIST_T *pHead);

/* Delete friend node that we want to remove from linked list.
 * Arguments:
 *   pHead - Head node of linked list
 *   pDel - User that want to delete node of linked list of friend.
 * Return 1, If delete node success. Return 0, If can't found node.
 */
int deleteFriend(FRIENDLIST_T **pHead, USER_T *pDel);

/* Write friend relation into relation file
 */
void writeFriend(USER_T *pData, FILE *pFile);

/* Free linked list of friend and linked list of pending requst in user.
 * Argument:
 *      pData - Data that we want to delete friend linked list.
 */
void freeFriend(USER_T* pData);