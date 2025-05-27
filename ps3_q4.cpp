#include <queue>
#include <vector>
#include <unordered_map>
#include <iostream>

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

int add_to_next_day(const Index& index, const int& ROW_SIZE, const int& COL_SIZE,
    std::queue<Index*>& next_day, std::unordered_map<Index, int, IndexHash>& oranges)
{
    int count = 0;
    int row = index.row;
    int col = index.col;

    if (row - 1 >= 0) 
    {
        Index neighbor(row - 1, col);
        if (oranges.find(neighbor) != oranges.end() && oranges[neighbor] == 1) 
        {
            next_day.push(new Index(row - 1, col));
            oranges[neighbor] = 2; // Make fresh orange dirty
            ++count;
        }
    }
    if (row + 1 < ROW_SIZE) 
    {
        Index neighbor(row + 1, col);
        if (oranges.find(neighbor) != oranges.end() && oranges[neighbor] == 1) 
        {
            next_day.push(new Index(row + 1, col));
            oranges[neighbor] = 2; // Make fresh orange dirty
            ++count;
        }
    }
    if (col - 1 >= 0) 
    {
        Index neighbor(row, col - 1);
        if (oranges.find(neighbor) != oranges.end() && oranges[neighbor] == 1) 
        {
            next_day.push(new Index(row, col - 1));
            oranges[neighbor] = 2; // Make fresh orange dirty
            ++count;
        }
    }
    if (col + 1 < COL_SIZE) 
    {
        Index neighbor(row, col + 1);
        if (oranges.find(neighbor) != oranges.end() && oranges[neighbor] == 1) 
        {
            next_day.push(new Index(row, col + 1));
            oranges[neighbor] = 2; // Make fresh orange dirty
            ++count;
        }
    }
    return count;
}

int days_rotten(std::vector<std::vector<int>> orange_matrix)
{
    if (orange_matrix.empty() || orange_matrix[0].empty()) return 0;
    
    std::queue<Index*> current_day;
    std::unordered_map<Index, int, IndexHash> oranges;
    const int ROW_SIZE = orange_matrix.size();
    const int COL_SIZE = orange_matrix[0].size();
    int total_oranges = 0, processed_oranges = 0, days = 0;
    
    // Initialize oranges map and count
    for (int row = 0; row < ROW_SIZE; ++row) 
    {
        for (int col = 0; col < COL_SIZE; ++col) 
        {
            if (orange_matrix[row][col] == 0)
                continue;
            
            Index idx(row, col);
            oranges[idx] = orange_matrix[row][col];
            total_oranges++;
            
            if (orange_matrix[row][col] >= 2) 
            {
                current_day.push(new Index(row, col));
                if (orange_matrix[row][col] == 3)
                {
                    processed_oranges++; 
                }
            }
        }
    }
    
    if (total_oranges == 0) 
        return -1;
    if (processed_oranges == total_oranges) 
        return 0;

    while (!current_day.empty()) 
    {

        int size = current_day.size();
        bool infected_new = false;

        for (int i = 0; i < size; ++i) 
        {
            Index* index = current_day.front();
            current_day.pop();
            int new_infections = add_to_next_day(*index, ROW_SIZE, COL_SIZE, current_day, oranges);
            if (new_infections > 0) 
                infected_new = true;
            if (oranges[*index] == 2) 
            {
                oranges[*index] = 3;
                processed_oranges++;
            }   
            delete index;
        }
        days++; 
        // Haven't infected any new oranges & havent processed all oranges meaning return false
        if (!infected_new && current_day.empty() && processed_oranges < total_oranges)
            return -1;
    }
    return processed_oranges == total_oranges ? days : -1;
}

int main() {
    // Test cases
    std::vector<std::vector<std::vector<int>>> test_cases = {
        // Test Case 1: All oranges will rot
        {
            {1, 1, 0},
            {1, 3, 1},
            {0, 1, 1}
        },
        // Test Case 2: Cannot rot all oranges (isolated by empty cells)
        {
            {1, 0, 1},
            {0, 3, 0},
            {1, 0, 1}
        },
        // Test Case 3: Already all rotten
        {
            {3, 3, 3},
            {3, 3, 3},
            {3, 3, 3}
        },
        // Test Case 4: Mix of fresh, dirty and rotten
        {
            {1, 2, 1},
            {1, 3, 1},
            {1, 1, 1}
        },
        // Test Case 5: No oranges
        {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        }
    };
    
    for (int i = 0; i < test_cases.size(); i++) {
        int result = days_rotten(test_cases[i]);
        std::cout << "Test Case " << (i+1) << ": " << result << " days" << std::endl;
        
        // Print the matrix for clarity
        std::cout << "Matrix:" << std::endl;
        for (const auto& row : test_cases[i]) {
            for (int cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    
    return 0;
}