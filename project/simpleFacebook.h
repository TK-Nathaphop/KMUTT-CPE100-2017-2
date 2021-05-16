#define LEN 128
#define LONGLEN 500

/* Enum for type of unbalance tree kinds */
typedef enum
    {
    G_MALE = 1,     /* for male gender */
    G_FEMALE        /* for female gender */
    }GENDER_TYPE;

/* Enum for type of command */
typedef enum
    {
    C_ERROR = 0,      /* Error command */
    C_STATUS,         /* Update status */
    C_COMMENT,        /* Comment current status */
    C_FIND,           /* Go home */
    C_HOME,           /* Help, print all command */
    C_HELP,           /* Go to next status */
    C_NEXT,           /* See friend pending request */
    C_PENDING,        /* See user's profile */
    C_PROFILE,        /* Logout from Simple Facebook */
    C_SIGNOUT,        /* Find friend */
    C_ACCEPTF,        /* Add friend after find friend */
    C_DENYF,          /* Delete friend after find friend */
    C_ADDFRIEND,      /* Accept friend after see pending request */
    C_UNFRIEND        /* Deny friend after see pending request */
    } COMMAND_TYPE;

/* Linked list of friends of user */
typedef struct _friendList
    {
    void *pData;                /* Address of data */
    struct _friendList *pNext;  /* Next node */
    }FRIENDLIST_T;

typedef struct _comment
    {
    void *owner;                /* A person who comment a sttus */
    char text[LONGLEN];
    int date[5];
    struct _comment *pNext;     /* Next node of comment */
    }COMMENT_T;

typedef struct _status
    {
    void *owner;            /* Address of person who update status */
    char text[LONGLEN];     /* Text status */
    int date[5];            /* Date of status [0] - day, [1] - month, [2] - year
                             * [3] - hour, [4] - minute
                             */
    COMMENT_T *pHeadC;      /* Head node of a person who comment */
    COMMENT_T *pTailC;      /* Tail node of a person who comment */
    struct _status *pNext;  /* Next node of status */
    }STATUS_T;

/* Data of each user */
typedef struct _user
    {
    char mail[LEN];         /* E-mail, the key of hash */
    char password[LEN];
    char name[LEN];         
    char phone[15];
    GENDER_TYPE gender;     /* G_MALE for male, G_FEMALE for female */
    int dateBirth[3];       /* [0] - day, [1] - month, [2] - year */
    int friends;            /* Amount of friends */
    FRIENDLIST_T *pHeadF;   /* Linked list of persons who're friend */
    FRIENDLIST_T *pHeadP;   /* Linked list of pending request */
    STATUS_T *pHeadS;       /* Head node of status */
    STATUS_T *pTailS;       /* Tail node of status */
    }USER_T;

/* Tree of a user */
typedef struct _userTree
    {
    USER_T *pData;              /* Address of data */
    int height;                 /* Height of node */
    struct _userTree *pLeft;    /* Left Child node */
    struct _userTree *pRight;   /* Right Child node */
    }USERTREE_T;
