/* Get E-mail and password. Then send E-mail to find data.
 * If found, check password correct or not.
 * Arguments:
 *      mail - E-mail that user input
 *      password - Password that want to check with E-mail
 * Return 1, if found user data and password correct.
 * Return 0, if found user data but password doesn't correct.
 * Return -1, if Not found user data. 
 */
int signIn(char *pMail, char *pPassword);

/* Used for read data from file.
 * Set system like user login to add data.
 * Argument:
 *      pUser - User that want to access sign in
 */
void accessSignIn(USER_T *pUser);

/* This function working with function in controlStatus.c.
 * It can Initial status, get status, go to next status
 * depends on select that input
 * Arguments:
 *      select - select what do you want to do about status
 *              1 for initial status, 2 for get status, 3 for go next status
 *      status - status that we want to return
 * Return 1, for success. Return 0, if don't have any friend or status to display.
 * Return -1, if can't allocate memory.
 */
int statusMenu(int select, STATUS_T **pStatus);

/* Add user that want to be friend to friend pending request.
 * Argument:
 *      pPending - User that want to add to be pending request.
 * Return 2, if pending user have been add friend to user already.
 * Return 1, add to pending request success.
 * Return 0, if Both are friend already or waited for accept friend.
 * Return -1, if can't allocate memory.
 */
int addPending(USER_T* pPending);

/* Delete user that we don't want to be friend in friend list or remove from
 * pending request.
 * Argument:
 *      pAdd - User that want to add to be friend
 * Return 4, if user that want to unfriend is sent pending request by user login.
 * Return 3, if user that want to unfriend is same as user login.
 * Return 2, if user that want to unfriend is in user's pending request.
 * Return 1, if delete success.
 * Return 0, if they're not friend.
 */
int unFriend(USER_T* pDel);

/* Add user that want to be friend into friend list of user that login.
 * Argument:
 *      pAdd - User that want to add to be friend.
 * Return 1, if success. Return 0, if pAdd and user that login are already friend.
 * Return -1, if can't allocate memory.
 */
int addFriend(USER_T* pAdd);

/* Update a new status into user data
 * Arguments:
 *      pText - Text that want to update
 *      date - Current time that user update
 *      select - Select to add to head or tail
 *               1 - for add to head (the newest status)
 *               2 - for add to tail (the oldest status)
 * Return new status back. But if can't allocate memory return NULL.
 */
STATUS_T* updateStatus(char *pText, int date[], int select);

/* Update a new status into user data
 * Arguments:
 *      pText - Text that want to update
 *      date - Current time that user update
 * Return new status back. But if can't allocate memory return NULL.
 */
COMMENT_T* updateComment(STATUS_T *pStatus, char *pText, int date[]);

/* See the data in pending linked list
 * Return user that add pending request to user and amount of friend pending
 * Argument:
 *      count - Return count how many friend
 * Return data in the first node of pending linked list
 */
USER_T* lookPending(int *count);

/* Accept the latest pending request to be friend of user
 * Return 1 if success. Return 0 if not have any pending request
 * Return -1 if can't allocate memory
 */
int acceptFriendPending();

/* Deny the latest pending request to be friend of user.
 * Return 1 if success. Return 0 if not have any pending request
 */
int denyFriendPending();

/* Find data from hash table.
 * Argument:
 *      pFind - E-mail of user that we want to find
 * Return address of user that we find.
 */
USER_T* findData(char *pFind);

/* Add data to hash table. If there is some collision it'll keep in tree
 * Argument:
 *      pNew - New data that we want to add.
  * Return 1 for success. Return 0 for same data. Return -1 for can't allocate.
 */
int addData(USER_T *pNew);

/* Return address of user that login back.
 */
USER_T* getUser();

/* Write data into file
 * Arguments:
 *      pFile - File that we want to write
 *      select - File that we select to write
 */
void writeFile(FILE *pFile, int select);

/* User log out from system. Set '_userLogin' to NULL.
 */
void signOut();

/* Find suggest friend of user that we want.
 * Argument:
 *      pSuggestF - Amount of suggest friend
 * Return suggest friend of user back.
 */
USER_T** suggestFriend(int *pSuggestF);