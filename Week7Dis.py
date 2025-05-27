import numpy as np

# TODO: Problem 1 Triangle

"""
Given a triangle array, return the minimum path sum from top to
bottom.
For each step, you may move to an adjacent number of the row below.
More formally, if you are on index i on the current row, you may move
to either index i or index i + 1 on the next row.
Example 1:
Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
 2
 3 4
6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11
(underlined above).
Example 2:
Input: triangle = [[-10]]
Output: -10
"""

# First idea is to treat this as a graph problem and to use Bellman-Ford Alg
# Thinking I could start from the top and adjust cost for cheapest path
# Or I could do the same and work up from the top

# First Idea is dp[r][i] = given row r the min cost to get to index i
import sys
def triangle_path(triangle):
 n = len(triangle)

 # Base Cases
 if n == 0:
  return None
 elif n == 1:
  return triangle[0][0]

 INT_MAX = sys.maxsize
 # Creating dp table
 # Note: Since I don't need to further back than 1 row I could just use
 # an in place dp array to save space
 dp = [[INT_MAX] * (i + 1) for i in range(n)]
 dp[0][0] = triangle[0][0]
 for row in range(1, n):
  len_row = len(triangle[row])
  for index in range(len_row):
   dp[row][index] = triangle[row][index] + min(dp[row - 1][index] if index < (len_row - 1) else INT_MAX
                                              ,dp[row - 1][index-1] if index > 0 else INT_MAX)
 return min(dp[-1])

def test_triangle():
 tri = [[2],[3,4],[6,5,7],[4,1,8,3]]
 print("Testing")
 print(triangle_path(tri))

# TODO Q2: Unique Binary Search Trees
"""
Find the number of structurally unique binary search trees (BSTs) that can be constructed with n nodes, each with unique values. 
Example 1: 
Input: n = 3 
Output: 5 
Example 2: 
Input: n = 1 
Output: 1 
"""

# First I want to check if there is a pattern
# bst(1) = 1, bst(2) = 2, bst(3) = 5, bst(4) = 14 (I was checking trees not BSTs same values though)
# When we have 1 node it can only be the root
# When we have 2 nodes either can be the root. The non root has one place it can go bst(2) = 2
# When we have 3 nodes. If  we pick either the min or max value the remaining two nodes can be placed in bst(2)
# different ways. so we have 2 * bst(2). If  we pick the root to be the median then theres only one way to put it.
# When we have 4 nodes. If we pick either of edge values as the root then the remaining 3 nodes form the bst(3).
# So those two nodes can give us 2 * 5 = 10 different cominations. Then if we pick one of the middle nodes it will
# have 2 larger/smaller and 1 the other. These 2 smaller/larger form a bst(2) tf we have 2 * 2 = 4

# bst(0) = 1
# bst(1) = bst(0) = 1 * 1
# bst(2) = bst(1) + bst(1)
# bst(3) = bst(2) + bast(1) + bst(2) = (1 * 2) + (1 * 1) + (1 * 2)
# bst(4) = bst(3) + bst(2) + bst(2) + bst(3) = (1 * 5) + (2 * 2) + (1 * 5)
# bst(5) = bst(4) + bst(3) + 2 * bst(2) + bst(3) + bst(4) = (1 * 14) + (1 * 5) + (2 * 2) + (1 * 5) + (1 * 14)

# dp[n] = sum(1 to n) of dp[i-1] * dp[n-i]

def unique_bst(n):
 dp = [1 for _ in range(n + 1)]
 for i in range(1, n + 1):
  dp[i] = sum(dp[j-1] * dp[i-j] for j in range(1,i+1))
 return dp[-1]

def test_unique_bst():
 for i in range(7):
  print(unique_bst(i))

def main():
 #test_triangle()
 test_unique_bst()


if __name__ == "__main__":
    main()
