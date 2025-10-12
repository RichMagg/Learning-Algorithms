#include <iostream>
#include <vector>

int partition(std::vector<int>& arr, int low, int high) 
{
	int pivot = arr[high];
	int i = low - 1;
	
	for (int j = low; j < high; ++j)
	{
		if (arr[j] <= pivot) 
		{
			++i;
			std::swap(arr[j], arr[i]);
		}
	}
	std::swap(arr[i + 1], arr[high]);
	return i+1;
}

void quicksort(std::vector<int>& arr, int low, int high) 
{
	if (arr.size() < 2 || low >= high) return;
	
	int pivot = partition(arr, low, high);
	quicksort(arr, low, pivot-1);
	quicksort(arr, pivot+1, high);
}

int main(int argc, char* argv[]) 
{
	std::vector<int> nums = 
	{
		30, 50, 80, 60, 44, 9, 11, 0
	};
	quicksort(nums, 0, nums.size()-1);
	
	for (auto n : nums) 
	{
		std::cout << n << " ";
	}
	return 0;
}