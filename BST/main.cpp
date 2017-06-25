#include <iostream>

//二分查找法，在有n个元素的有序数组arr中，查找元素target
//如果找到，返回元素在数组中的索引(下标)；否则返回-1
template <typename T>
int binarySearch(T arr[],int n,T target){
    //在arr[l...r]中查找target
    int l=0,r=n-1;
    while(l<=r){
        //l=r时，区间还有一个元素
        int mid=l+(r-l)/2;
        if(arr[mid]==target)
            return mid;

        if(target<arr[mid])
            //在arr[l...mid-1]中查找
            r=mid-1;
        else
            //在arr[mid+1...r]中查找
            l=mid+1;
    }
    return -1;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}