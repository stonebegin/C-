/*************************************************************************
    > File Name: Binary_search.cpp
    > Author: stonebegin
    > Mail: stonebegin@sina.com 
    > Created Time: 2019年04月24日 星期三 20时52分51秒
 ************************************************************************/
#include<iostream>
#include<vector>

/*
 Binary Search:
 在一个有序数组中查找关键字x的位置时，首先将x与数组中间项进行对比，如果相等，则算法完成。
 如果不等，则将数组划分成两个子数组，一个子数组中包含中间项左侧的所有element，另一个子数组包含其右侧所有element。
 如果x小于中间项，则将这一过程再应用于左侧子数组，否则，将其应用于右侧子数组，如此重复，直到找出x，或者最终确认x不在数组中。
 时间复杂度O(logn)
 */

std::vector<int> arr = {11, 12, 14, 16, 18, 20, 21, 24, 25};
int target = 18;

//递归形式
int Binary_Search(int left, int right){
	int mid;
	if(left > right)
		return 0;
	else{
		mid = (left + right) / 2;
		if(arr[mid] == target)
			return mid;
		else if(target > arr[mid])
			return Binary_Search(mid+1, right);
		else
			return Binary_Search(left, mid-1);
	}
}

//非递归形式
int binary_search(){
	int low = 0; high = (int)arr.size();
	int mid;
	while(low <= high){
		mid = (low + high) / 2;
		if(x == arr[mid]) return mid;
		else if(x < arr[mid]) high = mid - 1;
		else low = mid + 1;
	}
	return -1;
}

int main(){
	int len = arr.size();
	std::cout << Binary_Search(0, len-1) << std::endl;
	return 0;
}
