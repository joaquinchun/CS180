#include <vector>
#include <queue>
#include <iostream>

// Medium Heap DS creation
// Just need to implement push & find medium
class medium_heap
{
    private:
        // Max heap is default
        // Max heap for the smaller vals
        std::priority_queue<int> left; 
        // Min heap syntax
        // Min heap for larger vals
        std::priority_queue<int, std::vector<int>, std::greater<int>> right;

    public:
        medium_heap() {}
        void push(int val)
        {
            if (left.empty() || val <= left.top()) {
                left.push(val);
            } else {
                right.push(val);
            }
        
            if (left.size() > right.size() + 1) {
                right.push(left.top());
                left.pop();
            } else if (right.size() > left.size()) {
                left.push(right.top());
                right.pop();
            }
        }
        double find_medium()
        {
            if(left.size() == right.size())
                return (left.top() + right.top()) / 2.0;
            else
                return left.size() > right.size() ? left.top() : right.top();
        }
};

// Given a sorted array A of n distinct integers in increasing order, design an algorithm to determine
// if there exists an index i such that A[i] = i. The algorithm should run in O(logn) time.
int indexVal(std::vector<int> sorted)
{
    if (sorted.empty())
        return -1;
    size_t lower = 0, upper = sorted.size(), curr;
    curr = sorted.size()/2;
    while (lower != upper)
    {
        // If the Current number is greater than index the rest of the numbers will be greater than the index
        // This is becuase there are no repeats. 
        // And vice Versa
        if (sorted[curr] == curr)
            return curr;
        else if (sorted[curr] < curr)
        {
            lower = curr;
            curr += (upper - curr + 1) / 2;
        }
        else
        {
            upper = curr;
            curr -= (curr - lower + 1) / 2;
        }
    }
    return -1;
}

int main()
{
    std::vector<int> sorted = {-4,-3,3,5,7,8,20,44};
    std::cout << indexVal(sorted) << std::endl;
    return 0;
}