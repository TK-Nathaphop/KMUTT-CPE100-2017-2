/* Clear terminal and print head of program
 */
void headUserInterface();

/* Remove 'new line' from last character out.
 * ARGUMENT: 
 *     string - String want to remove 'new line'.
 */
void cutLine(char *string);

/* Print all data of user.
 * Argument:
 *      pUser - User that want to print data.
 */
void printData(USER_T *pUser);

/**************************************/
void printComment(COMMENT_T *pComment);

/* Print status and all comment of that status.
 * Argument:
 *      pStatus - Status that we want to print.
 */
void printStatus(STATUS_T *pStatus);

/* Print that command input not correct.
 * Argument:
 *      error - type of error
 */
void printCommandError(int error);

/* Print instruction and command after user use command '/help'
 */
void printHelp();

/* Get select then print message that want to print before exit
 * Argument:
 *      error - Error case.
 */
void printError(int error);

/* Ask and validate e-mail (In progress)
 * Argument:
 *      pReturn - E-mail that we have to return
 * Return 1, if user input e-mail success.
 * Return 0, if user cancel to input e-mail.
 */
int askMail(char *pReturn);

/* Ask and validate password (In progress)
 * Argument:
 *      pReturn - password that we have to return
 * Return 1, if user input e-mail success.
 * Return 0, if user cancel to input e-mail.
 */
int askPassword(char *pReturn);

/* Ask and validate name (In progress)
 * Argument:
 *      pReturn - name that we have to return
 * Return 1, if user input e-mail success.
 * Return 0, if user cancel to input e-mail.
 */
int askName(char *pReturn);

/* Ask and validate phone (In progress)
 * Argument:
 *      pReturn - phone that we have to return
 * Return 1, if user input e-mail success.
 * Return 0, if user cancel to input e-mail.
 */
int askPhone(char *pReturn);

/* Ask and validate phone (In progress)
 * Argument:
 *      pReturn - Array of date that we have to return
 * Return 1, if user input e-mail success.
 * Return 0, if user cancel to input e-mail.
 */
int askBirthDate(int pReturn[]);

/* Ask and validate gender
 * Argument:
 *      pReturn - phone that we have to return
 * Return 1, if user input e-mail success.
 * Return 0, if user cancel to input e-mail.
 */
int askGender(GENDER_TYPE *pReturn);

/* Ask that user want to accept pending request to friend or not.
 * Return 1, if user answer 'y'. Return 2, if user answer 'n'.
 * Return 0, if user want to cancel.
 */
int askPending();

/* Ask and get command from user.
 * Argument:
 *      pReturn - phone that we have to return
 * Return type of command that user input and some command of Simple Facebook
 * that have to return string.
 */
COMMAND_TYPE askCommand(char *pReturn);

/* Print menu, ask user to select menu theb return menu that user select
 * Return 1-3. 1 for Register, 2 for Login, 3 for Exit.
 */
int askMenu();

/* Loop ask user that exit or not
 * If exit dump all data to file and free all data
 * Return 1, if user want to exit program. Return 0, if user don't exit.
 */
int askExit();