#include <queue>
#include <vector>
#include <pair>
#include <stdout>

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

struct Index
{
    int row, col;
    Index(int r, int c) : row(r), col(c) {}
    bool operator==(const Index &other) const
    {
        return row == other.row && col == other.col;
    }
};

struct IndexHash
{
    size_t operator()(const Index &index) const
    {
        return (static_cast<uint64_t>(index.row) << 32) | static_cast<uint64_t>(index.col);
    }
};

int days_rotten(std::vector<std::vector<int>> orange_matrix)
{
    std::queue<*Index> next_day;
    std::unordered_map<Index, int, IndexHash> oranges;
    int row,col,num_rotten = 0, days = 0;
    Index *index = nullptr;
    for (row = 0; row < orange_matrix.size(); ++row)
        for (col = 0; col < orange_matrix[row].size(); ++col)
        {
            if (orange_matrix[row][col] == 0)
                continue;
            index = new Index(row, col);
            if (orange_matrix[row][col] > 1)
                next_day.push(index);
            oranges[*index] = orange_matrix[row][col];
        }
    
    
    while (!next_day.empty())
    {

    }
}
