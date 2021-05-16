/* Get the date to day and current time.
 * ARGUMENT:
 *     date - Date that return [0] - day, [1] - month, [2] - year, [3] - hour, [4] - minute.
 */
void dateToday(int date[]);

/* Validate and check command  which type of command is.
 * Arguments:
 *      pCheck - String that we want to check.
 *      pReturn -  String that we want to return
 * Return type of enum command.
 */
COMMAND_TYPE checkCommand(char *pCheck, char *pReturn);

/* Validate a mail of user.
 * Argument:
 *     pString - Keep mail from user that we want to validate
 * Return 0, if the mail is invalid.
 * Return 1, if the mail is valid.
 */
int validateMail(char *pString);

/* Validate phone number of user.
 * Argument:
 *     pString - Keep phone number from a user that we want to validate
 * Return 1, if phone number is correct.
 * Return 2, if phone number is not format.
 *     - The length of phone number is 10
 *     - The first character is not 0
 * Return 3, if phone number is not digit.
 * Return 4, if phone number is not Thai number.
 * (Thai phone number starts with 066 067 069 08 and 09) 
 */
int validatePhone(char *pString);

/* Validate name of user.
 * Argument:
 *     pString - Keep name of user that we want to validate
 * Return 0, if name of user is incorrect.
 * Return 1, if name of user is correct.
 */
int validateName(char *pString);

/* Check day, month, year and time that they exist or not.
 * Argument:
 *     date[] - date of date
 * Return 0, if date is incorrect.
 * Return 1, if date is correct.
 */
int validateBirthDate(int date[]);

/* Validate password of user.
 * Argument:
 *      pString - Keep password that we want to validate
 * Return 1, if password is valid.
 * Return 2, if the length of password is too long.
 * Return 3, if user get a special symbol.
 */
int validatePassword(char *pString);