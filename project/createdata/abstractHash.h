/* Insert a value into the hash table. Key is E-mail of user.
 * ARGUMENT:
 *      pPerson - Keep data that wants to insert
 * Return 1 for success. Return 0 for same data. Return -1 for can't allocate.
 */
int hashtableInsert(USER_T *pPerson);

/* Look up a value in the hash table.
 * ARGUMENT: pKey - Keep data(mail) that want to look up
 * If found it, return that data and return null if not found.
 */
USER_T* hashTableLookup(char *pKey);

/* Free all of items into the table.
 */
void hashTableFree();

/* This function return maximum bucket of array of hash table
 */
int hashTableBucketSize();

/* This function return root node of tree in hash table
 * Argument:
 *      position - position of array in hash table
 */
USERTREE_T* hashTableData(int position);