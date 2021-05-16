typedef struct _comment
	{
	USER_T *owner;				/* A person who comment a status */
	char text[100];
	int date[3];
	struct _comment *pNext;	 	/* Next node of comment */
	}COMMENT_T;

/* Linked list of a user */
typedef struct _userTree
	{
	USER_T *pData;				/* Address of data */
	int level;					/* Level of tree */
	struct _userTree *pLeft;	/* Left Child node */
	struct _userTree *pRight;	/* Right Child node */
	}USERTREE_T;

typedef struct _status
	{
	USER_T *owner;			/* Address of person who update status */
	char text[100];			/* Text status */
	int date[3];			/* Date of status */
	int countLike;			/* Amount of like */
	USERTREE_T *pLike;		/* Linked list of a person who like */
	COMMENT_T *pHead;		/* Head node of a person who comment */
	COMMENT_T *pTail;		/* Tail node of a person who comment */
	struct _status *pNext;	/* Next node of status */
	}STATUS_T;

/* This pNext in this structure use only in hash table */
typedef struct _user
	{
	char mail[100];			/* E-mail,  the main important hash */
	char password[100];		
	char name[100];			
	int dateBirth[3];
	int phone;
	int gender;
	STATUS_T *pStatus;
	USERTREE_T *pFriend;	/* Linked list of a person who're friend */
	USERSLIST_T * pRequest;
	/*struct _user *pNext;	   Next node of linked list in hash table */
	}USER_T;

/* Linked list of a user */
typedef struct _userList
	{
	USER_T *pData;				/* Address of data */
	struct _userList *pNext;	/* Next node */
	}USERLIST_T;
