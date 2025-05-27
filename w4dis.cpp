#include <vector>
#include <string>
#include <iostream>
#include <climits>

int min_bills(int value, const int denominations[], int size)
{
    // Assuming denominations is valid
    int note = size - 1;
    int count = 0;
    while (value != 0 && note >= 0)
    {
        if (value - denominations[note] >= 0)
        {
            value -= denominations[note];
            count++;
            continue;
        }
        else
            --note;
    }
    return (value != 0 || note < 0) ? -1 : count;
}

void test_min_bills()
{
    int input = 25;
    const int denominations[] = {1,2,5,10};
    int count = min_bills(input, denominations, static_cast<int>(sizeof(denominations)/sizeof(denominations[0])));
    if (count == 3)
        std::cout << "Passed" << std::endl;
    else 
        std::cout << "Failed" << std::endl;
    return;
}

// Correctly Returns True/False but alogithm would have to be different to return indicies
bool tripple_indicies(std::vector<int> nums)
{
    int min1 = INT_MAX, min2 = INT_MAX; //C1,C2
    for (int num : nums) // Runs N times
        if (num <= min1) //C3
            min1 = num; // C4
        else if (num <= min2) //C5
            min2 = num; //C6
        else //C7
            return true; // C8
    return false; //C9
}

void test_tripple_indicies()
{
    std::vector<int> nums = {2,1,5,0,4,6};
    if (tripple_indicies(nums))
        std::cout << "Passed" << std::endl;
    else 
        std::cout << "Failed" << std::endl;
    return;
}

int binary_string_cost(std::string s)
{
    // The largest reduction of cost we can get is 2
    // No matter the length of each 0 or 1 the seq 0101 or 1010
    // Will produce the max ammount of saving. 
    // So if swiches = 2 we can save 1 and if swiches >= 3 we can save 2.
    if (s.length() <= 1)
        return s.length();
    char last = s[0];
    int switches = 0;
    int cost = 0;
    for (char curr :  s)
    {
        if (curr == last)
            ++cost;
        else
        {
            ++switches;
            cost += 2;
        }
        last = curr;
    }
    if (switches > 2)
        cost -= 2;
    else if (switches == 2)
        --cost;
    return cost;
}

void test_binary_string_cost()
{
    std::cout << binary_string_cost("0110") << std::endl;
    std::cout << binary_string_cost("0101") << std::endl;
    std::cout << binary_string_cost("0100") << std::endl;
    std::cout << binary_string_cost("00000") << std::endl;
}

int main()
{
    test_min_bills();
    test_tripple_indicies();
    test_binary_string_cost();
    return 0;
}