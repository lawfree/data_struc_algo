#include<iostream>
#include<vector>

using namespace std;

bool binarySearch_recur(vector<int> &sort_array, int begin, int end, int target){
    if(begin  >  end)
        return false;

    int mid = (begin + end) /2 ;                    // region not exesit
    if(target == sort_array[mid])
        return true;

    else if(target < sort_array[mid])
        return binarySearch_recur(sort_array,begin , mid -1 ,target);
    else if(target > sort_array[mid])
        return binarySearch_recur(sort_array, mid + 1,end , target);
}

bool binarySearch_circle(vector<int> &sort_array, int target){
    int begin = 0;
    int end = sort_array.size() -1 ;


    while (begin <= end) {
        int mid = (begin + end) / 2;
        if(target == sort_array[mid])
            return true;
        else if(target < sort_array[mid])
            end = mid - 1;
        else if(target > sort_array[mid])
            begin = mid + 1;
    }

    return false;
}

class Binsearch
{
public:
    Binsearch() {}


    /* 1. leetCode 35.
        给定一个排序数组nums(无重复元素)与目标值target,
        如果target在nums里出现,则返回target所在的下表,
        如果target在nums里未出现,则返回target应该插入的数组下标,
        使得将target插入数组nums后,数组仍有序.

    */
    int searchInsert(vector<int>& nums, int target) {
        int index = -1;
        int begin = 0;
        int end = nums.size()  - 1;

        while (begin <= end) {
            int mid = (begin + end) /2 ;
            if(target == nums[mid])
                return mid;
            else if(target < nums[mid] ){
                if( mid == 0 || target > nums[mid - 1] )
                    index =  mid;
                end = mid -1;
            }
            else if(target > nums[mid]){
                if(mid == nums.size() - 1  || target < nums[mid + 1])
                    index = mid + 1;
                begin = mid + 1;
            }
        }
        return index;
    }


    /*LeetCode 34.
        给定一个按照升序排列的整数数组 nums(有重复元素)，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
        你的算法时间复杂度必须是 O(log n) 级别。
        如果数组中不存在目标值，返回 [-1, -1]。

        示例 1:

        输入: nums = [5,7,7,8,8,10], target = 8
        输出: [3,4]

        示例 2:

        输入: nums = [5,7,7,8,8,10], target = 6
        输出: [-1,-1]
    */
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> result;
        result.push_back(left_bound(nums, target));
        result.push_back(right_bound(nums , target));
        return result;
    }

    int left_bound(vector<int>& nums , int target){
        int begin = 0;
        int end = nums.size() - 1;
        while (begin <= end) {
            int mid = (begin + end) /2 ;
            if(target == nums[mid]){
                if( mid == 0 || nums[mid - 1] < target)
                    return mid;
                end = mid - 1;
             }
            else if (target < nums[mid])
                end = mid -1;
            else if (target > nums[mid])
                begin = mid + 1;
        }
        return -1;
    }
    int right_bound(vector<int>& nums , int target){
        int begin = 0;
        int end = nums.size() - 1;
        while (begin <= end) {
            int mid = (begin + end) /2 ;
            if(target == nums[mid]){
                if( mid == nums.size() - 1 || nums[mid + 1] > target)
                    return mid;
                begin = mid + 1;
             }
            else if (target < nums[mid])
                end = mid -1;
            else if (target > nums[mid])
                begin = mid + 1;
        }
        return -1;
    }


    /*leetCode 33.
        给定一个排序数组nums(nums中无重复元素),且nums可能以某个未知下标旋转,给定目标值target,
        求target是否在nums中出现,若出现返回所在下标,未出现返回-1
    */
    int search(vector<int>& nums, int target) {

    }
};



int main(int argc, char *argv[])
{
    vector<int>  veci;
    veci.push_back(1);
    veci.push_back(3);
    veci.push_back(7);
    veci.push_back(8);
    veci.push_back(9);
    veci.push_back(12);
//    cout << binarySearch_recur(veci , 0 , veci.size()  , 112) << endl;

    Binsearch binsearch;

    /* 1. test searchInsert */
    vector<int> vec_test;
    for(int i =0 ; i< 12 ; i++)
        vec_test.push_back(i);

    for(int i = 0 ; i< vec_test.size() ; i++){
        cout << vec_test[i] << ":  " << binsearch.searchInsert(veci , vec_test[i]) << endl;
    }


    /* 2. test searchRange */
    for(int i = 0 ; i< vec_test.size() ; i++){
        cout << vec_test[i] << ":  " << binsearch.searchRange(veci, vec_test[i]).front() <<" , "<<  binsearch.searchRange(veci, vec_test[i]).back() << endl;
    }

    return 0;
}
