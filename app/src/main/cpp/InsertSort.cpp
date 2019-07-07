#include <jni.h>
#include <cstring>
#include "InsertSort.h"
//
// Created by chenda on 2019/6/23.
//


/**
 * 插入排序
 * 输入：n个数的一个序列{a1,a2,...,an}
 * 输出：输出一个序列的排序{a1',a2',...,an'}，满足a1'<a2'<...<an'
 * 循环插入不变式：
 * 假设A={5,2,6,4,3}
 * {5,2,6,4,3}, {2,5,6,4,3}, {2,5,6,4,3}, {2,4,5,6,3}, {2,3,4,5,6}
 * 下标j为正被插入的元素，在for循环每次迭代的开始，包含已经排序好了的子数组A[i..j-1]
 * j与数组A[i..j-1]比较插入，直到j=n
 *
 * INSERTIONSORT(A)
 *  for j= 2 to A.length
 *      key = A[j]
 *      i = j-1;
 *      while(i>0 && A[i]>key)  //插入
 *          A[i+1] = A[i]
 *          i--;
 *      A[i+1]=key;
 *
 *
 * 选择算法：
 * INSERTIONSORT(A)
 *  for i=1 to (A.length-1)         n
 *      key = i                     n-1
 *      for j=2 to A.length         (i->n)Ti        最差情况:每次最小值都再最后，(n-1)+(n-2)+..+1 +1= n(n-1)/2 +1;应该不分好快情况
 *          if A[j] < A[key]        (i->n)(Ti-1)
 *              key=j               (i->n)(Ti-1)    这三句简化 j = Find_Min(A,i,n)
 *      A[i]=A[key]                 n-1
 *
 * */


void insertSort(int *array, int size){
    if(array== nullptr)
        return ;
    for(int i=1;i<size;i++){
        int key = array[i];
        int j=i-1;
        while(j>=0 && array[j]>key){
            array[j+1]=array[j];
            j--;
        }
        array[j+1]=key;
    }
}

/**
 * 考虑把两个n位二进制数加起来的问题，这两个整数分别存储在两个
 * n元素组A和B中。这两个整数的和应按二进制形式存储在一个（n+1）
 * 元数组C中。
 * 输入：两个n元素组A和B
 * 输出：元素组A和B的和，并存储在C中
 *
 * BINARY_ADD(A,B,C)
 * flag=0;  //进位标记
 * key=0;
 * for i= 0 to n
 *  key = A[i] + B[i] + flag;
 *  C[i] = key mod 2;   //除余
 *  if key>1
 *      flag = 1
 *
 * C[i] = flag;
 * */
