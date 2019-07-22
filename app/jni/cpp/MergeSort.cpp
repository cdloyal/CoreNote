#include <jni.h>
#include <cstring>
#include "MergeSort.h"
//
// Created by chenda on 2019/6/23.
//

/**
 * 分治法：
 * 分解原问题为若干个子问题，这些子问题是原问题规模较小的实例
 * 解决这些子问题，递归求解各子问题。若子问题规模足够小，则直接求解。
 * 合并这些子问题的解成原问题的解。考虑规模最少合并成规模次少，规模次大合并成规模最大
 *
 * 归并排序属于分治法：
 *  输入：n个元素的序列（无序）
 *  输出：n个元素的有序序列
 *  递归的输入：n/b个元素的序列（无序）
 *  递归的输出：n/b个元素的有序序列
 *
 * 分解：分解待排序的n个元素的序列成各具n/2个元素的子序列，分解待排序的n/2个元素的序列成各具n/4个元素的子序列
 *       退出的条件，待排序的元素只剩1个，代表排好序
 * 解决：使用归并排序递归地排序两个子序列，得到两个排好序的子序列。若子序列长度为1时，代表已排好序
 * 合并：合并两个已排序的子序列以产生已排序的答案。考虑序列长度为1合成序列长度为2，规模次大合并成规模最大，
 *
 *
 *
 * 用自己的语言描述
 * 要用递归的方法排列n个元素的序列，既然要用递归，这个序列就要分解成m个序列，这m个序列递归的结果是排好序的序列
 * （原问题的解决依赖子问题的解决），要解决的是m个排好序的子序列怎么合并成排好序的原序列
 * 随着序列的分解
 *
 * 要做的是，决定怎么分解？分解待排序的n个元素的序列成各具n/2个元素的子序列
 *
 *                                ... 2 4 7 5  8 2 3 6 ...
 *                                   2475          8236
 *                                 24    75      82    36
 *                                2  4  7  5    8  2  3  6
 *                                 24    57      28    36
 *                                   2457          2368
 *                                    2 2 3 4 5 6 7 8
 *
 * MERGE_SORT(A,p,r)
 *  if p>=r
 *      return;
 *  else
 *      q = (p+r)/2                 O(1)
 *      MERGE_SORT(A,p,q)
 *      MERGE_SORT(A,q+1,r)
 *      MERGR(A,p,q,r)              O(n)
 *
 *
 * MERGR(A,p,q,r)
 *  n1 = q-p+1;
 *  n2 = r-q;
 *  for i=1 to n1
 *      L[i]=A[p+i-1]
 *  for i=1 to n2
 *      R[i]=A[q+i]
 *  i=1
 *  j=1
 *  for k=p to r
 *      if j<r && L[i] >= R[j]
 *          A[k]=R[j]
 *          j++
 *      else
 *          A[k]=L[i]
 *          i++
 *
 * 讨论算法运行时间：
 * 假设T(n)是规模为n的一个问题的运行时间
 *
 * 分治法：
 * 分解原问题为a个子问题，这些子问题是原问题规模较小的实例                      假设分解的时间D(n)
 * 解决这些子问题，递归求解各子问题。若子问题规模足够小(n<=c)，则直接求解。      解决每个子问题的规模为原来规模的1/b,，由a个子问题，a*T(n/b),当n<=c,T(n)=O(1)
 * 合并这些子问题的解成原问题的解                                              假设合并子问题的时间C(n)
 *
 *          O(1)            n<=c
 * T(n) =
 *          a*T(n/b)+D(n)+C(n)
 *
 *
 * 对于归并排序
 *          O(1)            n<=c
 * T(n) =                               ==>O(nlgn)      n是2的幂次方，最终分解成lgn+1层，每一层合并的时间O(n),假如系数是c，即cn，的cn(lgn+1)  ==>O(nlgn)
 *          2*T(n/2)+O(1)+O(n)
 *
 * 二分查找法：
 * 在序列{a1、a2、...、an},找到value
 * 分解：将序列分成
 * 解决：
 * 合并：
 *
 * BINARY_SEARCH(A,v,p,r)
 *  if(p>=r&&v!=A[p])
 *      return nil
 *
 *  middle = p+(p-r)/2;
 *  if(A[middle]>v){
 *      BINARY_SEARCH(A,v,middle+1,r)
 *  }else if(A[middle]<v){
 *      BINARY_SEARCH(A,v,p,middle-1)
 *  }else{
 *      return middle;
 *  }
 *
 *
 * */

void merge_sort(int* array,int start,int end){
    if(start>=end)  //分解的最后一层，序列只有1个元素，已排好序
        return;

    //分解：分解成两个序列
    int middle = start+(end-start)/2;   //防止溢出
    //解决：使用归并排序递归地排序两个子序列，得到两个排好序的子序列
    merge_sort(array,start,middle);
    merge_sort(array,middle+1,end);
    //合并：合并两个已排序的子序列以产生已排序的答案
    merger(array,start,middle,end);
}
void merger(int* array,int start,int middle,int end){
    //合并：合并两个已排序的子序列以产生已排序的答案
    //两个已排序的子序列
    int leftLen = middle-start+1;
    int rightLen = end-start;
    int left[leftLen];
    int right[rightLen];
    memcpy(left, array, (leftLen));
    memcpy(right,array+start+1, (rightLen));

    int leftIndex=0;
    int rightIndex=0;
    int i=0;
    while(leftIndex<leftLen && rightIndex<rightLen){
        if(left[leftIndex]<=right[rightIndex]){
            array[i]=left[leftIndex];
            leftIndex++;
        } else {
            array[i]=right[rightIndex];
            rightIndex++;
        }
    }

    while (leftIndex<leftLen){
        array[i]=left[leftIndex];
        i++;
        leftIndex++;
    }
    while (rightIndex<rightLen){
        array[i]=left[rightIndex];
        i++;
        rightIndex++;
    }



    /**
     * 函数增长
     *  theta(g(n)) = {f(n):存在正常量c1 c2和n0,使得对所有n>=n0，有0<=c1*g(n)<=f(n)<=c2*g(n)}
     *  假设f(n)=0.5n^2-3n = thrta(n^2) = theta(g(n))
     *  则存在正常量c1 c2和n0,使得对所有n>=n0，有0<=c1*n^2<=0.5n^2-3n<=c2*n^2
     *      c1<=0.5-3/n<=c2
     *      c1取比a小一些，c2取比a大一些，可以满足不等式，比如：
     *      假设c1=a/4,c2=7a/4 且n0=2*max(|b|/a,(|c|/a)^0.5)
     *
     *  渐进紧界
     *  f(n)=theta(g(n))    theta(g(n))是函数的集合，可以在这个集合找到f(n),且0<=c1*g(n)<=f(n)<=c2*g(n)
     *
     *  渐进上界
     *  O(g(n)) = {f(n):存在正常量c1 c2和n0,使得对所有n>=n0，有0<=f(n)<=c*g(n)}
     *  非渐进紧确上界     远离上界
     *  o(g(n))     2n=o(n^2)   3n^2 != o(n^2)
     *
     *  渐进下界        欧姆
     *  OHM(g(n)) = {f(n):存在正常量c1 c2和n0,使得对所有n>=n0，有f(n)>=c*g(n)}
     *  非渐进紧确下界
     *  w(g(n))
     *
     *
     *
     * */








}