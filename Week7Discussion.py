import numpy as np
from win32con import NULLREGION


def divide_and_conquer(nums):
    # Return, total sum, max sum, prefix sum, suffix sum.
    if len(nums) == 0:
        return -1, -1, -1, -1
    elif len(nums) == 1:
        return nums[0], nums[0], nums[0], nums[0]
    mid = int(len(nums) / 2)
    left_total, left_max, left_prefix, left_suffix = divide_and_conquer(nums[:mid])
    right_total, right_max, right_prefix, right_suffix = divide_and_conquer(nums[mid:])
    total = left_total + right_total
    prefix = max(left_prefix, left_total + right_prefix)
    suffix = max(right_suffix, right_total + left_suffix)
    abs_max = max(total, left_max, right_max, left_suffix + right_prefix)
    abs_max = max(abs_max, prefix, suffix)
    return total, abs_max, prefix, suffix

def maxSubArrayDC(nums):
    total, abs_max, _ , _ = divide_and_conquer(nums)
    return max(abs_max, total)

def dynamic_programming(nums):
    if len(nums) == 0:
        return None
    elif len(nums) == 1:
        return nums[0]
    dp = [None] * len(nums)
    dp[0] = nums[0]
    maxSum = dp[0]
    for i in range(1, len(nums)):
        dp[i] = max(dp[i - 1] + nums[i], nums[i])
        maxSum = max(maxSum, dp[i])
    return maxSum


nums = list([5,4,-1,7,8])
max_sub_array = dynamic_programming(nums)
print(max_sub_array)
