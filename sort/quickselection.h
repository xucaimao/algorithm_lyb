//
// Created by xcm on 17/6/19.
//找出一个数组按从小到大顺序的第k个元素
//暴力求解的思路是先排序
//优化的方法是利用快速排序的定义，通过条件判断，减少排序的运算量

#ifndef SORT_QUICKSELECTION_H
#define SORT_QUICKSELECTION_H

#include "mySort.h"

//需要用到shellsort 和 isSorted 两个外部函数
#include <ctime>

//暴力求解快速选择问题(brute force algorithm)
template <typename T>
T quickSelectionBF(T arr[],int n,int k){
    quickSort(arr,n);
    return arr[k-1];
}


//双路快速排序
//对数组arr[l...r]部分进行partition操作
//返回p,使得arr[l...p-1]<arr[p];arr[p+1...r]>arr[p]
template <typename T>
int __partitionQM(T arr[],int l,int r){
    swap( arr[l],arr[rand()%(r-l+1)+l] );//此处写成l-r+1,一个很大的坑
    T v=arr[l];
    //arr[l+1...i) <=v; arr(j...r] >=v
    int i=l+1,j=r;
    while(true){
        while(i<=r && arr[i]<v) i++;
        while(j>=l+1 && arr[j]>v) j--;
        if(i>j) break;
        swap(arr[i],arr[j]);
        i++;
        j--;
    }
    swap(arr[l],arr[j]);
    return j;
}

template <typename T>
void __quickSortQM(T arr[],int l,int r,int k){
    if(r-l<=15){
        insertionSort(arr,l,r);
        return;
    }

    int p=__partitionQM(arr,l,r);
    if(p==k) return;
        //一开始在这里逻辑搞错了
        //p>k，说明所要找的元素k在p的左半端
        //通过这些判断，减少了排序的运算量，达到节约时间的目的
    else if(p>k)
        __quickSortQM(arr,l,p-1,k);
    else
        __quickSortQM(arr,p+1,r,k);

}

template <typename T>
T quickSelectionQM(T arr[],int n,int k){
    srand(time(NULL));
    //此处的k-1表示数组的第k个元素
    __quickSortQM(arr,0,n-1,k-1);
    return arr[k-1];
}


template <typename T>
void testQuickSelectionTime(string Name,T(*SelectFunction)(T[],int,int),T arr[],int n,int k){

    clock_t startTime=clock();
    T dat=SelectFunction(arr,n,k);
    clock_t endTime=clock();
    cout<<Name<<" time is : "<<double(endTime-startTime)/CLOCKS_PER_SEC<<" S "<<endl;
    cout<<"the data of NO. "<<k<<" is : "<<dat<<endl;
    return;
}


#endif //SORT_QUICKSELECTION_H
