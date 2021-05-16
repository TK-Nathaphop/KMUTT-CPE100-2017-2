/* Find data that we want from tree by using key (which key is e-mail).
 * Arguments:
 *      pCurrent - Current node of tree
 *      key - Key that we want to find
 * Return tree node that we want. 
 */
USERTREE_T* findDataTree(USERTREE_T *pCurrent, char* key);

/* Random get data in tree. Usually used for suggest friend.
 * Argument:
 *      pUser - Keep node of user that we want to start to take a random
 * Return the data that we random in tree.
 */
USER_T* randomFriendTree(USERTREE_T *pUser);

/* Add new node to tree.
 * Arguments:
 *      pRoot - Root node of tree
 *      pNew - New tree that want to add
 * Return 1 for success. Return 0 for same data.
 */
int addDataTree(USERTREE_T **pRoot, USERTREE_T *pNew);

/* Traverse a tree (post-order traversal).
 * Write all of friend in tree to relation file.
 * and free all of data.
 * ARGUMENTS: pCurrent - Node that we want to write
 *            pFile    - File that we want to write
 */
void writeFriendTree(USERTREE_T *pCurrent, FILE *pFile);

/* Traverse a tree (post-order traversal).
 * Write all of status and comment in tree to status file.
 * ARGUMENTS: pCurrent - Node that we want to write
 *            pFile    - File that we want to write
 */
void writeStatusTree(USERTREE_T *pCurrent, FILE *pFile);

/* Traverse a tree (post-order traversal).
 * Write all of profile in tree to profile file.
 * ARGUMENTS: pCurrent - Node that wew want to write
 *            pFile    - File that we want to write
 */
void writeProfileTree(USERTREE_T *pCurrent, FILE *pFile);

/* Free all data in tree.
 * Argument:
 *      pDelete - Subtree/node that we want to delete.
 */
void freeTree(USERTREE_T *pDelete);