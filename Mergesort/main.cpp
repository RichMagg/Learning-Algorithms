#include <iostream>
#include <vector>

int find_middle(std::vector<int>& arr, int low, int high)
{
	if (arr.size() < 2 || low >= high) return -1;
	return (low + high) / 2;
}

std::vector<int> merge_arrays(std::vector<int>& arr1, std::vector<int>& arr2) 
{
	std::vector<int> res = {};
	size_t i = 0, j = 0;
	
	while (i < arr1.size() && j < arr2.size())
	{
		if (arr1[i] < arr2[j])
		{
			res.push_back(arr1[i++]);
		}else 
		{
			res.push_back(arr2[j++]);
		}
	}
	
	while (i < arr1.size()) res.push_back(arr1[i++]);
	while (j < arr2.size()) res.push_back(arr2[j++]);
	
	return res;
}

std::vector<int> mergesort(std::vector<int>& arr, int low, int high)
{
	if (arr.size() < 2 || low >= high) return arr;
	
	int mid = find_middle(arr, low, high);
	std::vector<int> left(arr.begin(), arr.begin() + mid + 1);
	std::vector<int> right(arr.begin() + mid + 1, arr.end());
	
	left = mergesort(left, 0, left.size()-1);
	right = mergesort(right, 0, right.size()-1);
	
	return merge_arrays(left, right);
}

int main(int argc, char* argv[]) 
{
	std::vector<int> nums = { 10, 90, 30, 49, 90, -1 };
	
	nums = mergesort(nums, 0, nums.size()-1);
	
	for (const auto& n : nums) 
	{
		std::cout << n << std::endl;
	}
	return 0;
}