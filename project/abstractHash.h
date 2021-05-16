/* Insert a value into the hash table. Key is E-mail of user.
 * Argument:
 *      pPerson - Keep data that want to insert.
 * Return 1 for success. Return 0 for same data. Return -1 for can't allocate.
 */
int hashTableInsert(USER_T *pPerson);

/* Look up a data in the hash table.
 * Argument:
 *      pKey - Keep data(mail) that want to look up
 * If found it, return that data and return null if not found.
 */
USER_T* hashTableLookup(char *pKey);

/* This function return maximum bucket of array of hash table
 */
int hashTableBucketSize();

/* This function return root node of tree in hash table
 * Argument:
 *      position - position of array in hash table
 */
USERTREE_T* hashTableData(int position);

/* Taking a random data and return that data when function finishes.
 */
USER_T* randomFriendHash();