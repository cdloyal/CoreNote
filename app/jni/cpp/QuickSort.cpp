#include "QuickSort.h"

/**
* 作者：chenda
* 时间：2019/7/18:15:36
* 邮箱：
* 说明：
*/

/**
 * 快速排序：
 * 输入：无序数组A[p...r]
 * 输出：有序数组A
 *
 * 分解：无序数组A[p...r]被分成A[p...q-1]和A[q+1...r]，其中A[p...q-1]的元素都小于A[q],A[q+1...r]的元素都大于A[q]
 * 解决：A[p...q-1]和A[q+1...r]递归调用快速排序。分解的退出条件p==r。
 * 归并：A[p...q-1]和A[q+1...r]递归调用快速排序，得到的是排好序的两序，
 *      由于A[p...q-1]的元素都小于A[q],A[q+1...r]的元素都大于A[q]，所以整个数组排好序。
 *
 * 现在的问题是：
 *     无序数组A[p...r]被分成A[p...q-1]和A[q+1...r]，其中A[p...q-1]的元素都小于A[q],A[q+1...r]的元素都大于A[q]
 *     输入：A[p...r]
 *     输出：A[p...r] q
 *     方法有很多：1、新建一个数组,随意取q，遍历原数组，A[k]>a[q]，放大新数组的大端，A[k]<=a[q]，放大新数组的小端，
 *                2、如果数组很大，新建数组不合适的话，书本图例
 *                q = PARTITION(A,p,r)
 *                     q=r;i=p-1;j=p;
 *                     j   p->r
 *                         if(A[j]<=A[q])
 *                             tmp=A[i+1];
 *                             A[i+1]=A[j];
 *                             A[j]=tmp
 *                             i++;
 *                         else
 *                             //nothing to do
 *                         j++;
 *                     return i;
 * */

int partitioin(int *array,int start,int end){
    int q=end,i=start-1,j=start,tmp;
    for (;j<=end;j++){
        if(array[j]<=array[q]){
            i++;
            tmp=array[i];
            array[i]=array[j];
            array[j]=tmp;
        }
    }
    return i;
}
void quickSort(int *array,int start,int end){
    if(start==end)
        return;

    int q = partitioin(array,start,end);
    if(q-1>=start)
        quickSort(array,start,q-1);
    if(q+1<=end)
        quickSort(array,q+1,end);
}