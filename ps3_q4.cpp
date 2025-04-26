


/*************** The Quetion **********************************************************************
You are given a matrix of dimension M * N, where each cell in the matrix is initialized with values
0, 1, 2, or 3 which has the following meaning: ---- 0: This cell contains no orange. 1: Cell has a
fresh orange. 2: Cell has a dirty orange. 3: Cell has a rotten orange. The input matrix represents
the state of all cells at day 0.  The task is to find the first day all oranges become rotten. A
dirty or rotten orange at index (i, j) will make all neighboring fresh oranges dirty by the next
day. The neighbors of any cell are the cells directly above, below, to the left, and to the right
(assuming the neighbor is in the bounds of the matrix). All dirty oranges will become rotten by the
next day. If it is impossible to rot every orange then simply return -1
**************************************************************************************************/

/****************** My Idea **********************************************************************
- For every dirty/rotten cell do a BFS
- Keep track of the depth each layer being another day.
- Once all fresh oranges have been found, The greatest depth = the days.
- If the size of seen oranges == size of orange then all oranges are rotten
-   return depth + 1 (+1 for the day it needs to turn rotten)
- Else
-   return -1 a fresh tomamtoe is accessable 
**************************************************************************************************/