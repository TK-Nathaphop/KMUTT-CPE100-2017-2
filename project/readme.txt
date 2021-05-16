***************** readme.txt ********************

Program : simpleFacebook
Group : Run Every Verb
Team member:
Chawakorn Boonrin (Bright)				60070503415
Nathaphop Sundarabhogin (Kla)			60070503420
Natthawat Tungruethaipak (Tong)			60070503426
Setthawut Leelawatthanapanit (SAAB) 	60070503466

***************************************************

simpleFacebook
This program working like a social network name Facebook.

********************** About database file **********************
There are some data file that we include in zip file.
These are name of 3 data files.
-profileFB.dat  (Binary File)
-relationFB.txt (Text File)
-statusFB.txt  (Text File)

We have attached 'profileData.txt' for data in 'profileFB.dat'.

********************** How this program work **********************

When start program, it'll read data files first.
First, it'll read profile file to get all of information of user
Second, read relation file to get friend and pending request
Third, read status file to get status and comment of each user.

After read file and get all of data, it will display and ask user 3 menus.
===== 1) Register =====
Program can register Simple Facebook and validate information to get valid format.
The main key (it act like ID) is E-mail.

===== 2) Sign in =====
Let user to sign in Simple Facebook with E-mail and password.

After user sign in into Simple Facebook it'll suggest friend.
This suggest friend will find friend of friend first.
If user not have any friend or not have any friend of friend.
It'll random in data to suggest.

If user have friend it'll display status, comment.
But if not, it'll display that don't have any status.

Then program will ask user for command.
/help - Display how to use and all command
/s <text> - Update status (This command must follow with text)
/c <text> - Update comment to current status (This command must follow with text)
/next -  See next status
/pending - See all pending request that want to be friend
/profile - Display profile of user that sign in
/find <E-mail> - Find another user with E-mail
/home - Refresh status and display suggest friend again
/signout - Sign out from Simple Facebook

After find user it'll let you use only these 4 commands.
/addfriend - to send pending request to user that we find
/unfriend - to unfriend/unsend pending request to user that we find
Otherwise, /help or /home

After use command /pending it'll show the lastest friend that send you a pending request
and ask you only 'Y' for accept to be friend, 'N' for deny to be friend or hit <CR> to cancel

===== 3) Exit =====
This program will ask for sure again before exit

Before exit, program will write all of data in program
into data file and free data after write.

********************** Some minor problems **********************

-This program decide status to display with the newest status that just update
But if you update status immediately with the same hour and same minute of status.
Sometimes it has a minor problem display not the newest status.

-Pending request that another user send to user.
After you closed program and open again, It'll rearrange from the newest to oldest and oldest to newest.
