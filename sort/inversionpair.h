//
// Created by xcm on 17/6/16.
//求逆序对的数量，暴力方法与归并方法
#include <iostream>

#ifndef SORT_INVERSIONPAIR_H
#define SORT_INVERSIONPAIR_H
//暴力求解逆序对的方法(brute force algorithm)
template <typename T>
void inversionPairBF(T arr[],int l,int r,long int *sum){
    for(int i=l;i<=r-1;i++)
        for(int j=i+1;j<=r;j++)
            if(arr[i]>arr[j])
                (*sum)++;       //括号必须有，因为++的优先级高于*
}

template <typename T>
long int inversionPairBF(T arr[],int l,int r){
    long int sum=0;
    for(int i=l;i<=r-1;i++)
        for(int j=i+1;j<=r;j++)
            if(arr[i]>arr[j])
                sum++;
    return sum;
}

//利用归并排序的求逆序对算法
//此方法对数组进行归并排序的过程中求解，会对原数组造成改变，因此需要对复制的数组进行操作
//利用传地址的方式，保证递归过程中总数量统计的正确性
//否则就要采用全局变量
template <typename T>
void inversionPairMS(T arr[],int l,int r,long int *sum){
    if(l>=r)return;
    int mid=l+(r-l)/2;          //采用此种方法可以有效避免溢出
    inversionPairMS(arr,l,mid,sum);     //先排序前一半
    inversionPairMS(arr,mid+1,r,sum);   //再排序后一半

    if(arr[mid]>arr[mid+1]){        //merge过程
        T aux[r-l+1];
        int r_aux=r-l,mid_aux=mid-l;

        for(int i=l;i<=r;i++)
            aux[i-l]=arr[i];
        //按从小到大顺序把aux中的数据放回arr中
        int i=0,j=mid_aux+1;
        for(int k=l;k<=r;k++){
            if(i>mid_aux){
                arr[k]=aux[j];
                j++;
            }
            else if(j>r_aux){
                arr[k]=aux[i];
                i++;
            }
                //此处要加上=，否则虽然不影响数组排序，但会影响逆序对的计算
                //会把相等的情况也计算到逆序对中
            else if(aux[i]<=aux[j]){
                arr[k]=aux[i];
                i++;
            }
            else{
                arr[k]=aux[j];
                j++;
                *sum+=(mid_aux-i+1);        //增加的逆序对数字统计
            }
        }

    }//end of merge
}

//采用传值的方式
template <typename T>
long int inversionPairMS(T arr[],int l,int r){
    long int sum=0,sum_pre=0,sum_next=0;
    if(l>=r)return sum;
    int mid=l+(r-l)/2;          //采用此种方法可以有效避免溢出
    sum_pre=inversionPairMS(arr,l,mid);     //先排序前一半
    sum_next=inversionPairMS(arr,mid+1,r);   //再排序后一半
    //if以内  是merge过程，把原来的子程序并入
    if(arr[mid]>arr[mid+1]){
        T aux[r-l+1];
        int r_aux=r-l,mid_aux=mid-l;

        for(int i=l;i<=r;i++)
            aux[i-l]=arr[i];
        //按从小到大顺序把aux中的数据放回arr中
        int i=0,j=mid_aux+1;
        for(int k=l;k<=r;k++){
            if(i>mid_aux){
                arr[k]=aux[j];
                j++;
            }
            else if(j>r_aux){
                arr[k]=aux[i];
                i++;
            }
                //此处要加上=，否则虽然不影响数组排序，但会影响逆序对的计算
                //会把相等的情况也计算到逆序对中
            else if(aux[i]<=aux[j]){
                arr[k]=aux[i];
                i++;
            }
            else{
                arr[k]=aux[j];
                j++;
                sum+=(mid_aux-i+1);        //增加的逆序对数字统计
            }
        }

    }//end of merge

    return sum+sum_pre+sum_next;
}

template <typename T>
void testInversionPairTime(string Name, void(*inversionPair)(T[],int,int,long int *),T arr[],int l,int r){
    long int sum=0;
    clock_t startTime=clock();
    inversionPair(arr,l,r,&sum);
    clock_t endTime=clock();
    cout<<Name<<" : "<<double(endTime-startTime)/CLOCKS_PER_SEC<<" S "<<endl;
    cout<<"The num of inversion pair is : "<<sum<<endl;
    return;
}


template <typename T>
void testInversionPairTime2(string Name, long int(*inversionPair)(T[],int,int),T arr[],int l,int r){
    long int sum=0;
    clock_t startTime=clock();
    sum=inversionPair(arr,l,r);
    clock_t endTime=clock();
    cout<<Name<<" : "<<double(endTime-startTime)/CLOCKS_PER_SEC<<" S "<<endl;
    cout<<"The num of inversion pair is : "<<sum<<endl;
    return;
}

#endif //SORT_INVERSIONPAIR_H
