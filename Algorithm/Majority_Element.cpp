/*************************************************************************
    > File Name: Majority_Element.cpp
    > Author: stonebegin
    > Mail: stonebegin@sina.com 
    > Created Time: 2019年04月24日 星期三 22时31分19秒
 ************************************************************************/
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>

using namespace std;

class Solution {
private:
    int countInRange(vector<int>& nums, int num, int low, int high){
        int count = 0;
        for(int i=low; i<=high; i++)
            if(nums[i] == num)
                count++;
        return count;
    }
    
    int majorityElementRec(vector<int>& nums, int low, int high){
        //base case:the only element in an array of size 1 is the majority element
        if(low == high)
            return nums[low];
        //recurse on left and right havles of this sile
        int mid = (low - high) / 2 + low;
        int left = majorityElementRec(nums, low, mid);
        int right = majorityElementRec(nums, mid+1, high);
        
        //if the two halves agree on the majority element, return it
        if(left == right)
            return left;
        
        //otherwise, count each element and return the "winner"
        int leftCount = countInRange(nums, left, low, high);
        int rightCount = countInRange(nums, right, low, high);
        
        return leftCount > rightCount ? left : right;
    }
    
public:
    //Boyer-Moore Voting Algorithm
    int BMV_majorityElement(vector<int>& nums) {
        int count = 0;
        int candidate;
        
        for(int num : nums){
            if(count == 0)
                candidate = num;
            count += (num == candidate) ? 1 : -1;
        }
        
        return candidate;
    }
    
    int majorityElement(vector<int>& nums){
        return majorityElementRec(nums, 0, nums.size()-1);
    }
};

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

int main() {
    string line;
    while (getline(cin, line)) {
        vector<int> nums = stringToIntegerVector(line);
        
        int ret = Solution().majorityElement(nums);

        string out = to_string(ret);
        cout << out << endl;
    }
    return 0;
}
