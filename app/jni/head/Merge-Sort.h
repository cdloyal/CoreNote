/**
 * 作者：chenda
 * 时间：2019/8/7:10:29
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_MERGE_SORT_H
#define CORENOTE_MERGE_SORT_H

#include <cstring>

template <class T>
void mergeSort(T *&array,int start,int end);
template <class T>
void merge(T *&array,int start,int middle,int end);


template <class T>
void merge(T *&array,int start,int middle,int end){
    //合并：合并两个已排序的子序列以产生已排序的答案
    //两个已排序的子序列

    if(start>=end)
        return;

    int leftLen = middle-start+1;
    int rightLen = end-middle;
    T *left = (T *)malloc((leftLen)* sizeof(T));
    T *right= (T *)malloc((rightLen)* sizeof(T));
//    T left[leftLen];
//    T right[rightLen];
    memcpy(left, array+start, (leftLen)* sizeof(T));
    memcpy(right,array+middle+1, (rightLen)* sizeof(T));

    int leftIndex=0;
    int rightIndex=0;
    int i=start;
    while(leftIndex<leftLen && rightIndex<rightLen){
        if(left[leftIndex]<=right[rightIndex]){
            array[i]=left[leftIndex];
            leftIndex++;
        } else {
            array[i]=right[rightIndex];
            rightIndex++;
        }
        i++;
    }

    while (leftIndex<leftLen){
        array[i]=left[leftIndex];
        i++;
        leftIndex++;
    }
    while (rightIndex<rightLen){
        array[i]=right[rightIndex];
        i++;
        rightIndex++;
    }
    free(left);
    free(right);
}

template <class T>
void mergeSort(T *&array,int start,int end){
    if(start>=end)  //分解的最后一层，序列只有1个元素，已排好序
        return;

    //分解：分解成两个序列
    int middle = start+(end-start)/2;   //防止溢出
    //解决：使用归并排序递归地排序两个子序列，得到两个排好序的子序列
    mergeSort(array,start,middle);
    mergeSort(array,middle+1,end);
    //合并：合并两个已排序的子序列以产生已排序的答案
    merge(array,start,middle,end);
}


#endif //CORENOTE_MERGE_SORT_H
