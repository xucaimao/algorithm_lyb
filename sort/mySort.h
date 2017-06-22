//
// Created by Administrator on 2017/6/12.
//

#ifndef SORT_MYSORT_H
#define SORT_MYSORT_H

#include <iostream>
#include <ctime>
#include "maxheap.h"

using namespace std;

//对n个元素的数组arr进行选择法排序
template <typename T>
void selectionSort(T arr[],int n){
    for(int i=0;i<n-1;i++){
        //查找最小元素的位置
        int min=i;
        for(int j=i+1;j<n;j++)
            if(arr[j]<arr[min]) min=j;
        swap(arr[i],arr[min]);
    }

}

//对arr[l...r]进行插入法排序
//插入法排序
template <typename T>
void insertionSort(T arr[],int l,int r){
    for(int i=l+1;i<=r;i++){
        T t=arr[i];
        int j;
        for(j=i;j>l;j--){
            if(arr[j-1]>t)
                arr[j]=arr[j-1];
            else break;
        }
        arr[j]=t;
    }
}

//对n个元素的数组arr进行插入法排序
template <typename T>
void insertionSort2(T arr[],int n){
    for(int i=1;i<n;i++){                   //从第二个元素开始，比较该元素与前一元素的大小
        T t=arr[i];
        int j;
        for( j=i;j>0;j--){                  //
            if(arr[j-1]>t)                  //如果前面的元素大，则后移
                arr[j]=arr[j-1];
            else break;
        }
        arr[j]=t;
    }
}

//冒泡排序
template <typename T>
void bubbleSort(T arr[],int n){
    int swaptime;
    for(int i=n;i>0;i--){       //在[0,n-1]区间内进行比较，n递减
        swaptime=0;
        for(int j=1;j<i;j++)
            if(arr[j-1]>arr[j]){
                swap(arr[j-1],arr[j]);
                swaptime++;
            }
        if(swaptime==0)break;   //一次循环后没有发生数据交换，说明数据已经有序，提前结束循环
    }
}

//希尔排序.实质上是一种先对数据进行分组
//再对分组后的数据进行插入排序的方法
template <typename T>
void shellSort(T arr[],int n){
    //int tm=0;
    int step=n/2;                           //初始化步幅(组数)
    while(step>=1){                         //按步幅(组)进行一趟排序
        for(int s=0;s<step;s++){            //在组内进行插入排序
            for(int i=s+step;i<n;i+=step){  //组内第二个元素开始
                T t=arr[i];
                int j;
                for(j=i;j>s;j-=step){       //j>s边界的确定，是个坑。s就是本组数据的首地址
                    if(arr[j-step]>t)
                        arr[j]=arr[j-step]; //大的元素后移
                    else break;
                }
                arr[j]=t;                   //找到位置插入
            }
        }
        step/=2;
        //cout<<"result "<<++tm<<" : ";
        //for(int i=0;i<n;i++)cout<<arr[i]<<" ";
        //cout<<endl;
    }
}

//归并排序
//前后两半进行归并,两个数组下标的对应关系是重点和难点
template <typename T>
void __merge(T arr[],int l,int mid,int r){
    T aux[r-l+1];                       //新开的辅助数组
    int r_aux=r-l,mid_aux=mid-l;        //计算辅助数组的右边界及中点,左边界就是0

    for(int i=l;i<=r;i++)
        aux[i-l]=arr[i];                //arr[l...r]拷贝到aux[0..r-l]
    //按从小到大顺序把aux中的数据放回arr中
    int i=0,j=mid_aux+1;                //i,j是指向辅助数组前段和后段当前元素的指针
    for(int k=l;k<=r;k++){              //k是指向原始数组待插入元素位置的指针
        if(i>mid_aux){                  //先判断i和j取值的合法性
            arr[k]=aux[j];
            j++;
        }
        else if(j>r_aux){
            arr[k]=aux[i];
            i++;
        }
        else if(aux[i]<aux[j]){
            arr[k]=aux[i];              //小的先放回原数组
            i++;
        }
        else{
            arr[k]=aux[j];
            j++;
        }
    }

}

//递归的归并排序，对arr[l...r]区间的元素进行排序
template <typename T>
void __mergeSort(T arr[],int l,int r){
    if(l>=r)return;

    //int mid=(l+r)/2;            //计算中点，有可能出现溢出
    int mid=l+(r-l)/2;          //采用此种方法可以有效避免溢出
    __mergeSort(arr,l,mid);     //先排序前一半
    __mergeSort(arr,mid+1,r);   //再排序后一半
    //归并排序的定义会保证此时数组的前半和后半都是分别有序的
    //所以当arr[mid]<=arr[mid+1]时，就说明前半的最大值已经比后半的最小值还要小，
    // 也就是说整个数组已经是有序的了，不需要再进行归并的操作了
    if(arr[mid]>arr[mid+1])     //此处是第一个优化
        __merge(arr,l,mid,r);   //对排好序的两半进行归并
}
//归并排序的用户接口函数
template <typename T>
void mergeSort(T arr[],int n){
    __mergeSort(arr,0,n-1);
}

//自底向上的归并
template <typename T>
void mergeSortBU(T arr[],int n){
    for(int sz=1;sz<n;sz*=2){          //数据组的大小，1*2、2*2、4*2、8*2...直至整个数组的大小n
        for(int i=0;i+sz<n;i=i+2*sz)    //各数据组的起始位置
            //将每个数据组分成两半，再对前半段arr[i...i+sz-1]和后半段arr[i+sz...i+2*sz-1]进行归并
            //sz<n及i+sz<n都是为了确保数组后半段存在，即数组后半段最少存在一个元素，否则归并的定义就不对了
            if(arr[i+sz-1]>arr[i+sz])
                __merge(arr,i,i+sz-1,min(i+2*sz-1,n-1) );
            //min函数限定后半段的范围，不能超过数组的边界
    }
}


//对数组arr[l...r]部分进行partition操作
//返回p,使得arr[l...p-1]<arr[p];arr[p+1...r]>arr[p]
template <typename T>
int __partition(T arr[],int l,int r){
    //采用随机化方案
    swap(arr[l],arr[rand()%(r-l+1)+l]);

    T v=arr[l];

    //arr[l+1...j]<v arr[j+1...i)>v
    int j=l;
    //设置j=l,则arr[l+1...j]<v也就是arr[l+1...l]<v是空集
    //arr[j+1...i]>v也就是arr[l+1...l+1)>v也是空集
    for(int i=l+1;i<=r;i++){
        if(arr[i]<v){       //下面两句可以改成swap(arr[++j],arr[i])
            swap(arr[j+1],arr[i]);
            j++;
        }
    }
    swap(arr[l],arr[j]);
    return j;
}

//双路
//对数组arr[l...r]部分进行partition操作
//返回p,使得arr[l...p-1]<arr[p];arr[p+1...r]>arr[p]
template <typename T>
int __partition2(T arr[],int l,int r){
    swap( arr[l],arr[rand()%(r-l+1)+l] );//发现一个bug,原来写成（l-r+1）
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
void __quickSort(T arr[],int l,int r){
    if(r-l<=15){
        insertionSort(arr,l,r);
        return;
    }
    int p=__partition2(arr,l,r);
    __quickSort(arr,l,p-1);
    __quickSort(arr,p+1,r);

}

template <typename T>
void quickSort(T arr[],int n){
    srand(time(NULL));
    __quickSort(arr,0,n-1);
}



//三路快速排序arr[l...r]
//将arr[l...r]分成 <v; ==v; >v 三部分
//之后递归对<v ; >v 两部分继续进行三路快速排序
template <typename T>
void __quickSort3Way(T arr[],int l,int r){
    if(r-l<=15){
        insertionSort(arr,l,r);
        return;
    }
    //partition
    swap( arr[l],arr[rand()%(l-r+1)+l] );
    T v=arr[l];

    int lt=l;           //arr[l+1...lt]<v 初始为空集
    int gt=r+1;         //arr[gt...r]>v 初始为空集
    int i=l+1;          //arr[lt+1...i-1]==v 初始为空
    while(i<gt){
        if(arr[i]<v){
            swap(arr[i],arr[lt+1]);
            lt++;
            i++;
        }
        else if(arr[i]>v){
            swap(arr[i],arr[gt-1]);
            gt--;
        }
        else
            i++;
    }
    swap(arr[l],arr[lt]);
    //partition end
    __quickSort3Way(arr,l,lt-1);
    __quickSort3Way(arr,gt,r);
}

template <typename T>
void quickSort3Way(T arr[],int n){
    srand(time(NULL));
    __quickSort3Way(arr,0,n-1);
}

//堆排序--插入元素法
template <typename T>
void heapSort(T arr[],int n){
    MaxHeap<T> maxheap=MaxHeap<T>(n);
    for(int i=0;i<n;i++)
        maxheap.insert2(arr[i]);
    for(int i=n-1;i>=0;i--)
        arr[i]=maxheap.getMax2();
}

//堆排序--heapify方法
template <typename T>
void heapSort2(T arr[],int n){
    MaxHeap<T> maxheap=MaxHeap<T>(arr,n);
    for(int i=n-1;i>=0;i--)
        arr[i]=maxheap.getMax2();
}


//对有n个元素的数组arr的第k个元素，执行shiftDown操作(小元素下移)
template <typename T>
void __shiftDown(T arr[],int n,int k){
    while(2*k+1 < n){//左孩子存在
        int j=2*k+1;//j初始指向左孩子
        if(j+1 < n && arr[j]<arr[j+1])//右孩子存在且右孩子大于左孩子
            j+=1;   //j指向右孩子
        if(arr[k]>=arr[j])//父节点大于孩子节点
            break;
        swap(arr[k],arr[j]);
        k=j;
    }
}

//原地堆(最大堆)排序
template <typename T>
void heapSort3(T arr[],int n){
    //heapfy,构建一个堆
    for(int i=(n-1)/2;i>=0;i--)
        __shiftDown(arr,n,i);

    for(int i=n;i>=1;i--){
        //堆中的最大元素arr[0]与最末元素arr[n-1]进行交换
        //堆的长度越来越短，后端有序的数组越来越长
        swap(arr[0],arr[i-1]);
        //对前n-1个元素的堆，执行shiftDown操作
        __shiftDown(arr,i-1,0);
    }

}


#endif //SORT_MYSORT_H
