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

def main():
 test_triangle()

if __name__ == "__main__":
    main()