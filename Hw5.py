def find_k(nums):
    lower = 0
    upper = len(nums) - 1
    while lower < upper:
        mid = (lower + upper) // 2
        if nums[mid] > nums[upper]:
            lower = mid + 1
        else:
            upper = mid
    return lower