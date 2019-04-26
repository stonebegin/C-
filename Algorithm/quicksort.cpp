/*************************************************************************
    > File Name: quicksort.cpp
    > Author: stonebegin
    > Mail: stonebegin@sina.com 
    > Created Time: 2019年04月25日 星期四 20时40分06秒
 ************************************************************************/
#include<iostream>
#include<vector>

using namespace std;

vector<int> S = {15, 22, 13, 27, 12, 10, 20, 25};

void partition(int low, int high, int & pivotpoint){
	int i, j;
	int pivotitem = S[low];
	j = low;
	for(i = low + 1; i <= high; i++){
		if(S[i] < pivotitem){
			j++;
			int temp = S[i];
			S[i] = S[j];
			S[j] = temp;
		}
		cout << "i = " << i << ", j = " << j << endl;
	}
	pivotpoint = j;
	int temp = S[low];
	S[low] = S[pivotpoint];
	S[pivotpoint] = temp;
	for(i = 0; i < S.size(); i++){
		cout << S[i] << " ";
	}
	cout << endl;
}

void quicksort(int low, int high){
	int pivotpoint;
	if(high > low){
		partition(low, high, pivotpoint);
		quicksort(low, pivotpoint - 1);
		quicksort(pivotpoint + 1, high);
	}
}

int main(){
	quicksort(0, S.size() - 1);

	return 0;
}
