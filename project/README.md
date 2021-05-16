REQUIREMENT LIST
-	Read a file from database that have all user data, friends list, pending friend list and keep in hash table about 1000  arrays. (If there are same position it will keep in tree.)
-	User data have E-mail, password, name, birthday, phone number, gender, status, friends and pending request.
-	In status will include text, owner status, time, and all comments.
-	In comment will include text, time, owner.
-	Connect user that are friends together and linked pending request into user data.
-	The system must allowed user to sign up, sign in or exit program. 
-	If user sign up, get input and validate information correct or not. If finished sign up, add to hash table.
-	If user sign in, get E-mail and Password from user. Then send E-mail to hash function and search in hash table. If found user data, let user login. If not, print not found message.
-	(1) When user login program will show sugget friend by see friend of friend relation. If user not have any friend, program will random in hash table to sugget friend.
-	Then print how many friends pending request are there.
-	After display suggest friend. Go through friend list, print one friend’s status and all comment.
-	Get command from user, there are command as below
o	`/c <text>` 	Comment current status
o	`/s <text>` 	Update new status to Simple Facebook
o	`/home`	Go to first status (It work like a button refresh)
o	`/help`	Show all command and display some instruction
o	`/next`	Go to next status
o	 `/pending`	Go to see who are request to be your friend in sample facebook
o	 `/profile`	See all user’s information.
o	`/logout`	Log out from facebook
o	`/find <e-mail>` 	Find user in simple facebook
After command `/pending` user can use only this command
o	`/acceptf`	Accept to be friend
o	`/denyf`	Deny to be friend
Or `/home`
After search friend, user can use only this command
o	 `/addfriend` 	Add friend that person to see his news
o	`/delfriend`  	Delete that friend
Or `/home`
-	For `/home`, It work like a refresh button in Real Facebook. It will random a new status to show to user and start at (1) again.
-	For `/help`, will show to user that first time login (and suggest this command when user input wrong command)
-	For `/next`, It will random friends to print status.
-	For `/pending`, It will show amount of friend request and show only one user and some data(name, gender, age). Then asked to accept or deny friends. But you can’t ignore to see next friend pending (You have to decide to be friend or not that user. Otherwise, ignore to  decide and go back to home)
-	When log out it will go back to ask sign up or sign in again.
-	When find friends, user have to find by E-mail only. If found, print that user profile and then program will check that both users are friend or not. If not, program will allow user to use only command `/addfriend`. But if yes, program will allow user to use only command `/delfriend`. Otherwise, user have to use `/home`.
OPTIONAL
-	Let user to like all status and print amount of a person who like that status
-	Let user to change name, change password or delete user after using command `/setting`
-	Display all user status that user have been post.
-	After search friend’s, user can see all that friend’s status.
-	Can ignore to see next pending friend.
-	Print amount of person who comments that status
-	Make hash table from constant number on dependent on amount of data

