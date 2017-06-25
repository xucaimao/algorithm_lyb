//
// Created by xcm on 17/6/25.
//

#ifndef BST_BINARYSEARCH_H
#define BST_BINARYSEARCH_H

#include <iostream>
using namespace std;


//二分查找法，在有n个元素的有序数组arr中，查找元素target
//如果找到，返回元素在数组中的索引(下标)；否则返回-1
//如果存在多个重复元素的情况，返回的索引值不一定是第一个
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

//递归的二分查找法
template <typename T>
int binarySearch(T arr[],int l,int r,T target){
    if(l>r) return -1;
    int mid=l+(r-l)/2;
    if(target==arr[mid])
        return mid;
    if(target<arr[mid])
        return binarySearch(arr,l,mid-1,target);
    else
        return binarySearch(arr,mid+1,r,target);
}

//查找元素target的floor
template <typename T>
int floor(T arr[],int n,T target){
    int l=0,r=n-1;
    int p;
    while(l<=r){
        int mid=l+(r-l)/2;
        if(arr[mid]==target){
            //找到元素，往前找第一个
            p=mid;
            while(arr[p-1]==target) p--;
            return p;
        }
        if(target<arr[mid]){
            r=mid-1;
            p=r;
        }
        if(target>arr[mid]){
            l=mid+1;
            p=l;
        }
    }
    return p;
}

//查找元素target的ceil
template <typename T>
int ceil(T arr[],int n,T target){
    int l=0,r=n-1;
    int p;
    while(l<=r){
        int mid=l+(r-l)/2;
        if(arr[mid]==target){
            //找到元素，往后找最后一个
            p=mid;
            while(arr[p+1]==target) p++;
            return p;
        }
        if(target<arr[mid]){
            r=mid-1;
            p=mid;
        }
        if(target>arr[mid]){
            l=mid+1;
            p=l;
        }
    }
    return p;
}

void binarySearch_test(){
    int arr[]={2,5,7,8,8,8,9,11,15,15,15,17,21,22,25,26,29,29,29,36};
    //        {0,1,2,3,4,5,6,7, 8, 9, 10,11,12,13,14,15,16,17,18,19}
    int n=20;
    int target;
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    while(cin>>target && target!=-1){
        int t=binarySearch(arr,0,19,target);
        cout << "The element [ "<<target <<" ] position is ";
        if(t==-1)
            cout<<"not exist!"<<endl;
        else
            cout<<t<<"."<<endl;
    }
}

void floor_test(){
    int arr[]={2,5,7,8,8,8,9,11,15,15,15,17,21,22,25,26,29,29,29,36};
    //        {0,1,2,3,4,5,6,7, 8, 9, 10,11,12,13,14,15,16,17,18,19}
    int n=20;
    int target;
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    while(cin>>target && target!=-1){
        int t=floor(arr,20,target);
        cout << "The floor of element [ "<<target <<" ] is ";
        cout<<t<<"."<<endl;
    }
}

void ceil_test(){
    int arr[]={2,5,7,8,8,8,9,11,15,15,15,17,21,22,25,26,29,29,29,36};
    //        {0,1,2,3,4,5,6,7, 8, 9, 10,11,12,13,14,15,16,17,18,19}
    int n=20;
    int target;
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    while(cin>>target && target!=-1){
        int t=ceil(arr,20,target);
        cout << "The ceil of element [ "<<target <<" ] is ";
        cout<<t<<"."<<endl;
    }
}



#endif //BST_BINARYSEARCH_H
