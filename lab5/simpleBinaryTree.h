/******************************************************************************
 *
 * simpleBinaryTree.h
 *
 * 		Functions and data structures for a simple binary
 * 		tree. This tree does not keep its data sorted. It simply
 * 		fills up the tree from left to right as new calls to
 * 		'insertItem' are made.
 *
 * 			Created by Nathaphop Sundarabhogin ID 60070503420
 *      	15th February 2018
 *
 *****************************************************************************/
#ifndef SIMPLEBINARYTREE_H
#define SIMPLEBINARYTREE_H

#define PREORDER      1
#define INORDER       2
#define POSTORDER     3


/* Structure representing a node in the tree */
typedef struct _node
	{
  	char* data;               /* pointer to the data represented by this node */ 
  	struct _node * left;      /* left child node in the tree */
  	struct _node * right;     /* right child node in the tree */
	} NODE_T;


/* Structure representing a tree */
typedef struct _tree
	{
  	NODE_T * root;            /* root of the tree */
  	int itemcount;            /* keep track of number of nodes in tree */
	} TREE_T;


/** Public functions **/

/* Create a new tree and return a pointer to that tree
 * This is a "handle". Other modules should never look at
 * or modify the contents of the structure. The calling 
 * module should call 'freeTree' when it no longer needs
 * the heap.
 * Returns pointer to allocated tree, or null if memory allocation fails 
 */
TREE_T * createTree();


/* Insert a new node into the correct location in the tree.
 * Simply puts it in the next available spot, filling the
 * current level from left to right.
 * Arguments
 *    pTree       - pointer
 *    pDataItem    - new data to be inserted in the tree 
 * Returns 1 for success, 0 if memory allocation error occurred.
 */
int insertItem(TREE_T * pTree, char* pDataItem);


/* Traverse the tree and free all the nodes
 * Then free the TREE_T object itself.
 * This needs to be a post order traversal
 */
void freeTree(TREE_T * pTree);


/* Traverse and print using the specified order
 * structure
 * Argument
 *   pTree   - public structure
 *   order   - code for traversal order (see constants above)
 */
void printTree(TREE_T * pTree, int order);

/* Traverse an existing tree and print the leaf node values
 * Argument
 * 	 pTree   Points to the tree to travers.
 */
void printLeafNodes(TREE_T* pTree);

/* Calculate the maximum depth of a tree.
 * Argument
 *   pTree - Points to the tree we want to process.
 * Returns the maximum depth of the tree (at least 1) or 0
 * if the tree has not been initialized.
 */
int calculateMaxDepth(TREE_T* pTree);

#endif