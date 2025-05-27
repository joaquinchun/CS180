import numpy as np
#
# def gerrymander(A,B):
#     n = len(A)
#     if n % 2 != 0:
#         return False
#     a_voters = np.sum(A)
#     b_voters = np.sum(B)
#     total = a_voters + b_voters
#
#     delta = A-B
#     delta_total = np.sum(delta)
#     offset = np.sum(np.abs(delta))
#     span = offset * 2 + 1
#     # dp[p][s] can p places sum to s
#     dp = [[False for _ in range(span)] for _ in range(n//2+1)]
#     # Current State
#     dp[0][offset] = True
#
#     # Loop Through each precinct
#     for i in range(n):
#         new_state = dp
#
#         # For every precinct we have seen
#         for p in range(min(i + 1,n//2)):
#             # For the possible sums of delts we can have
#             for s in range(span):
#                 # Given p precincts can we have sum s
#                 if dp[p][s]:
#                     new_sum = s + delta[i]
#                     #Boundary Check
#                     if p+1 < n//2 and new_sum >= 0 and new_sum < span:
#                         new_state[p+1][new_sum] = True
#     for s in range(span):
#         if dp[n//2][s]:
#             d1 = s - offset
#             d2 = delta_total - d1
#             if d1 > 0 and d2 > 0:
#                 return True
#             elif d1 < 0 and d2 < 0:
#                 return True
#     return False
#
#     For all Current States do where p < n/2:
#         get there sum arguments called old_sum
#         dp[p+1][sum + delta[p+1]]
#
#     for all states where p == n/2:
#         get the second value that is offset + delta[p]:
#         subtract the offset to get just the delta[p] value:
#         Take the larger total of A voter and B voters.
#         Subtract the larger from the smaller.
#         Subtract the delta[p] value from that different.
#         If the result is positive then it is possible to gerrymander
#
#
#
#
# A = np.array([55, 43, 60, 47])
# B = np.array([45, 57, 40, 53]
#
# def ge

def max_score(coins):
    dp = [[0 for _ in range(len(coins))] for _ in range(len(coins))]
    # Base Case
    for i in range(len(coins)):
        dp[i][i] = coins[i]
    # Base Case 2
    for i in range(len(coins)-1):
        dp[i][i+1] = max(coins[i], coins[i+1])

    for gap in range(2, len(coins)):
        for i in range(len(coins) - gap):
            j = i + gap
            # I pick coin[i] which means my opponent will pick
            # the coin that minimizes my next move
            option_i = coins[i] + min(dp[i+1][j-1] if i-1 <= j-1 else 0,
                                      dp[i+2][j] if i-2 <= j else 0)
            option_j = coins[j] + min(dp[i+1][j-1] if i-1 <= j-1 else 0,
                                      dp[i][j-2] if i <= j-2 else 0)
            dp[i][j] = max(option_i, option_j)
    return dp[0][len(coins)-1]


coin = np.array([5,100,3,1])
print(max_score(coin))