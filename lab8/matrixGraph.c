/******************************************************************************
 *
 *  matrixGraph.c
 *
 *      Implements an abstractGraph using adjacency matrix.
 *      This is a 2 array with array of vertices and 2D array of edges. 2D array of
 *      edges, first array represent for 'From Vertex' and second array represent
 *      for 'To Vertex'.
 *
 *      Key values are strings and are copied when vertices are inserted into
 *      the graph. Every vertex has a void* pointer to additional data which
 *      is simply stored. 
 *
 *          Created by Nathaphop Sundarabhogin ID 60070503420
 *          22 March 2018
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractGraph.h"

#define WHITE 0
#define GRAY  1
#define BLACK 2

char * colorName[] = {"WHITE", "GRAY", "BLACK"};

/* List items for the main vertex list.*/
typedef struct _vertex
    {
    char * key;               /* key for this vertex */
    void * data;              /* additional data for this vertex */
    int color;                /* used to mark nodes as visited */
    }  VERTEX_T;

VERTEX_T * _vertices = NULL;  /* Array of vertices */  
int ** _edges = NULL;         /* 2D array of edges */  
int _maxVert = 0;             /* Max amount of vertex */
int bGraphDirected = 0;       /* if true, this is a directed graph */


/** Private functions */

/* Finds the vertex that holds the passed key
 * (if any) and returns a pointer to that vertex.
 * Arguments
 *       key    -  Key we are looking for
 * Returns position of vertices array that we looking foor
 * Return -1, when not found.       
 */
int findVertexByKey(char* key) 
    {
    int i = 0;              /*Count loop */
    int position = -1;      /* Position of array that we want to know */
    for(i = 0; (i < _maxVert) && (_vertices != NULL); i++)
        {
        if ((_vertices[i].key != NULL) && (strcmp(_vertices[i].key,key) == 0))
            {
            position = i;
            break;
            }
        }
    return position;
    }

/* Count adjacent vertices to a vertex.
 * Argument
 *    pVertex   -   Vertex whose adjacent nodes we want to count
 * Returns integer value for count (could be zero)
 */
int countAdjacent(int position)
    {
    int count = 0;  /* Count how many adjacent */
    int i = 0;      /* Loop */
    for (i = 0; i < _maxVert; i++)
        {
        if(_edges[position][i] == 1)
            count++;
        }
    return count;
    }

/* Set all vertices to the passed color.
 * Argument
 *    A color constant
 */
void colorAll(int color)
{
    int i = 0;  /* Count loop */
    if(_vertices != NULL)
        for(i = 0; i<_maxVert ; i++)
            _vertices[i].color = WHITE;
}

/* Function to print the information about a vertex
 * Argument  
 *   pVertex   -   vertex we want to print
 */
void printVertexInfo(int position)
    {
    printf("== Vertex key |%s| - data |%s|\n",
            _vertices[position].key, _vertices[position].data);
    }


/********************************/
/** Public functions start here */
/********************************/

/* Initialize or reintialize the graph.
 * Argument 
 *    maxVertices  - how many vertices can this graph
 *                   handle.
 *    bDirected    - If true this is a directed graph.
 *                   Otherwise undirected.
 * Returns 1 unless there is a memory allocation error,
 * in which case it returns zero.
 */
int initGraph(int maxVertices, int bDirected)
    {
    int i = 0;      /* Count loop */
    clearGraph();
    _vertices = (VERTEX_T*) calloc(maxVertices, sizeof(VERTEX_T));
    /* Create 2D Array of edges */
    _edges = (int**) calloc(maxVertices, sizeof(int*));
    for(i = 0; (i < maxVertices) && (_edges != NULL); i++)
        {
        _edges[i] = (int*)calloc(maxVertices, sizeof(int));
        if(_edges[i] == NULL)
            return 0;
        }
    /* Memory allocation error */
    if ((_edges == NULL) || (_vertices == NULL))
        return 0;
    bGraphDirected = bDirected;
    _maxVert = maxVertices;
    return 1; /* If can allocate memory, return 1 */
    }


/* Free all memory associated with the graph and
 * reset all parameters.
 */
void clearGraph()
    {
    int i = 0;      /* Count loop */
    if ((_vertices != NULL) && (_edges != NULL))
        {
        for (i = 0; (i < _maxVert); i++)
            {
            if(_vertices[i].key != NULL)
                free(_vertices[i].key);
            if(_vertices[i].data != NULL)
                free(_vertices[i].data);
            if(_edges[i] != NULL)
                free(_edges[i]);
            }
        free(_vertices);
        free(_edges);
        _vertices = NULL;
        _edges = NULL;
        }
    }

/* Add a vertex into the graph.
 * Arguments
 *     key   -   Key value or label for the 
 _maxVert = maxVertices  vertex
 *     pData -   Additional information that can
 *               be associated with the vertex.
 * Returns 1 unless there is an error, in which case
 * it returns a 0. An error could mean a memory allocation 
 * error or running out of space, depending on how the 
 * graph is implemented. Returns -1 if the caller tries
 * to add a vertex with a key that matches a vertex
 * already in the graph.
 */
int addVertex(char* key, void* pData)
    {
    int bOk = 1;
    int position = findVertexByKey(key);    /* Find and get position */
    int i = 0;                              /* Count loop */
    char * pKeyval = NULL;                  /* Keep key */
    if (position != -1)  /* key is already in the graph */
       bOk = -1;
    else
        {
        pKeyval = strdup(key);
        if ((pKeyval == NULL) || (_vertices == NULL) || (_edges == NULL))
            bOk = 0;  /* allocation error */
        else
            {
            /* Loop find position that doesn't have data */
            for(i = 0; i < _maxVert; i++)
                {
                if (_vertices[i].key == NULL)
                    {
                    _vertices[i].key = pKeyval;
                    _vertices[i].data = pData;
                    break;
                    }
                else if ((i+1) == _maxVert) /* Out of space */
                    bOk = 0;
                }
            }
        }
    return bOk;
    }


/* Remove a vertex from the graph.
 * Arguments
 *     key   -   Key value or label for the 
 *               vertex to remove
 * Returns a pointer to the data stored at that
 * vertex, or NULL if the vertex could not be 
 * found.
 */
void * removeVertex(char* key)
    {
    int i = 0;           /* Count loop */
    void * pData = NULL; /* data to return */
    int position = findVertexByKey(key);
    if (position == -1)
        return NULL; 
    else
        {
        pData = _vertices[position].data;
        /* Loop delete all edges that have relation with */
        for(i = 0; i < _maxVert; i++)
            {
            _edges[i][position] = 0;
            _edges[position][i] = 0;
            }
        free(_vertices[position].key);
        _vertices[position].key = NULL;
        _vertices[position].data = NULL;
        } 
    return pData;
    }


/* Add an edge between two vertices
 * Arguments
 *    key1  -  Key for the first vertex in the edge
 *    key2  -  Key for the second vertex
 * Returns 1 if successful, 0 if failed due to
 * memory allocation error, or if either vertex
 * is not found. Returns -1 if an edge already
 * exists in this direction.
 */
int addEdge(char* key1, char* key2)
    {
    int bOk = 1;                            /* Return value */
    int fromVtx = findVertexByKey(key1);    /* Position of from vertex */
    int toVtx = findVertexByKey(key2);      /* Position of to vertex */
    if ((fromVtx == -1) || (toVtx == -1))
        bOk = 0;
    else if (_edges[fromVtx][toVtx] == 1)
        bOk = -1;
    else
        {
        if (bGraphDirected) /* Directed Graph */
            _edges[fromVtx][toVtx] = 1;
        else if(!bGraphDirected)    /* Undirect graph */
            {
            _edges[fromVtx][toVtx] = 1;
            _edges[toVtx][fromVtx] = 1;
            }
        }
    return bOk;
    }

/* Remove an edge between two vertices
 * Arguments
 *    key1  -  Key for the first vertex in the edge
 *    key2  -  Key for the second vertex
 * Returns 1 if successful, 0 if failed 
 * because either vertex is not found or there
 * is no edge between these items.
 */
int removeEdge(char* key1, char* key2)
    {
    int bOk = 1;                            /* Return value */
    int fromVtx = findVertexByKey(key1);    /* Position of from vertex */
    int toVtx = findVertexByKey(key2);      /* Position of to vertex */
    if ((fromVtx == -1) || (toVtx == -1))
        bOk = 0;
    else if (_edges[fromVtx][toVtx] == 0)   /* This case for doesn't have edge */
        bOk = -1;
    else
        {
        if (bGraphDirected) /* Directed Graph */
            _edges[fromVtx][toVtx] = 0;
        else if(!bGraphDirected)    /* Undirect graph */
            {
            _edges[fromVtx][toVtx] = 0;
            _edges[toVtx][fromVtx] = 0;
            }
        }
    return bOk;
    }

/* Find a vertex and return its data
 * Arguments
 *    key  -  Key for the vertex to find
 * Returns the data for the vertex or NULL
 * if not found.
 */
void* findVertex(char* key)
    {
    void *pData = NULL;
    int position = findVertexByKey(key);
    if(position != -1)
        pData = _vertices[position].data;
    return pData;
    }

/* Return an array of copies of the keys for all nodes
 * adjacent to a node. The array and its
 * contents should be freed by the caller when it 
 * is no longer needed.
 * Arguments
 *    key   -  Key for the node whose adjacents we want
 *    pCount - Return number of elements in the array
 * Returns array of char* which are the keys of adjacent
 * nodes. Returns number of adjacent vertices in pCount.
 * If pCount holds -1, the vertex does not exist.
 */
char** getAdjacentVertices(char* key, int* pCount)
    {
    char** keyArray = NULL;              /* Keep array of adjacent */
    int position = findVertexByKey(key); /* Get position that want to know */
    int i = 0;                           /* Count loop */
    int keep = 0;                        /* Count how many item keep in array */
    if (position != -1)
        {
        *pCount = countAdjacent(position);   /* Count how many adjacent */
        if (*pCount > 0)
            {
            keyArray = (char**) calloc(*pCount, sizeof(char*));
            if (keyArray != NULL)
                {
                for(i = 0; i < _maxVert; i++)
                    {
                    if(_edges[position][i] == 1)    /* If it have edge */
                        {
                        keyArray[keep] = strdup(_vertices[i].key);
                        if(keyArray[keep] == NULL)
                            *pCount = -2;
                        keep++;
                        }
                    }
                }
            } 
        } 
    else
       *pCount = -1;
    return keyArray;
    }

/* Print out all the nodes reachable from a node by a 
 * breadth-first search.
 * Arguments
 *   startKey   -  Key for start vertex
 * Returns 1 if successful, -1 if the vertex does not exist.
 */
int printBreadthFirst(char* startKey)
    {
    int retval = 1;                             /* Return Value */
    int i = 0;                                  /* Count loop */
    int position = findVertexByKey(startKey);   /* Position of array */
    if ((_vertices == NULL) || (position == -1))
        retval = -1;
    else
        {
        for (i = 0; i < _maxVert; i++)  /* Loop check each edges */
            {
            if (_edges[position][i] == 1)
                printVertexInfo(i);
            }
        }
    return retval;
    }

/* Print out all the nodes by a depth-first search.
 */
void printDepthFirst()
    {
    int i = 0;      /* Count loop */
    int j = 0;      /* Count loop */
    int check = 0;  /* Check for print new traversal */
    if (_vertices == NULL)  /* If doesn't have any data */
        {
        printf("The graph is empty\n");
        }
    else
        {
        colorAll(WHITE);
        /* Loop check edges in matrix and print */
        for(i = 0; i < _maxVert; i++)
            {
            for (j = 0; j < _maxVert; j++)
                {
                if(_edges[i][j] == 1)   /* If it have edges print */
                    {
                    if (check == 0)     /* print for each 'From Travesal' */ 
                        {
                        printf("\nStarting new traversal from |%s|\n",
                        _vertices[i].key);
                        check = 1;
                        }
                    _vertices[j].color = GRAY;
                    printVertexInfo(j);
                    }
                }
            check = 0;
            }
        }
    }


/* Return information as to whether two vertices are
 * connected by a path.
 * Arguments
 *    key1 -  Key for the start vertex 
 *    key2 -  Key for the second vertex to check 
 * Returns 1 if the two vertices are connected, 0 if they
 * are not. Returns -1 if either vertex does not exist.
 */
int isReachable(char* key1, char* key2);