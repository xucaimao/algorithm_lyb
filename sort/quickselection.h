//
// Created by xcm on 17/6/16.
//

#ifndef SORT_QUICKSELECTION_H
#define SORT_QUICKSELECTION_H

#include "mySort.h"
#include "sortHelper.h"
//需要用到shellsort 和 isSorted 两个外部函数
#include <ctime>

//暴力求解快速选择问题(brute force algorithm)
template <typename T>
T quickSelectionBF(T arr[],int n,int k){
    shellSort(arr,n);
    return arr[k-1];
}


//双路快速排序
template <typename T>
int __partitionQM(T arr[],int l,int r){
    swap( arr[l],arr[rand()%(l-r+1)+l] );
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
    if(l>=r)
        return;

    int p=__partitionQM(arr,l,r);
    if(p==k) return;
    else if(p<k)
        __quickSortQM(arr,l,p-1,k);
    else
        __quickSortQM(arr,p+1,r,k);

}

template <typename T>
T quickSelectionQM(T arr[],int n,int k){
    srand(time(NULL));
    __quickSortQM(arr,0,n-1,k);
    return arr[k];
}


template <typename T>
void testQuickSelectionTime(string Name, void(*quickSelection)(T[],int,int),T arr[],int n,int k){
    clock_t startTime=clock();
    quickSelection(arr,n,k);
    clock_t endTime=clock();
    cout<<Name<<" : "<<double(endTime-startTime)/CLOCKS_PER_SEC<<" S "<<endl;
    return;
}


#endif //SORT_QUICKSELECTION_H
