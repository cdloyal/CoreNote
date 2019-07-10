#include <cstdlib>
#include <time.h>
#include "Sqlist.h"
 /**
 * 作者：chenda
 * 时间：2019/6/18:13:39
 * 邮箱：
 * 说明：数据结构的概念
 */

//数据结构是相互之间存在一种或者多种特定关系的数据元素的集合

//逻辑结构:数据对象中数据元素之间的相互关系
//集合结构（元素间平等）、线性结构（一对一关系）、树形结构（一对多层次关系）、图形结构（多对多）

//物理结构：数据的逻辑结构在计算机的存储形式
//顺序存储结构：把数据元素存储在地址连续的存储单元里。删除、插入元素不方便
//链式存储结构：数据存储的任意的存储单元。需要指针存放数据元素的地址，通过地址找到相应元素

//算法时间复杂度
//T(n)=O(f(n)),f(n)是问题规模n的某个函数，随问题规模n的增大，算法执行时间的增长率和f(n)的增长率相同
//0(1)      常数阶     12
//O(n)      线性阶     2n+3
//O(n^2)    平方阶     n*(n+1)/2
//O(logn)   对数阶     int c=1;while(c<n){c=c*2};  ==> 2^x=n ==> x=logn
//O(1)<O(logn)<O(n)<O(nlogn)<O(n^2)<O(n^3)<O(2^n)<O(n!)<O(n^n)

//算法的空间复杂度
//S(n)=O(f(n)),f(n)是占存储空间n的某个函数，

//前驱后继

//线性表的顺序存储结构
/**
 *  #define MAXSIZE 20
 *  typedef int ElemType;
 *  typedef struct{
 *      int length;
 *      ElemType data[MAXSIZE];
 *  }sqList;
 **/
//我们数数从1开始，数组下标从0开始，于是线性表的第i个元素存储在第i-1位置
//存储算法，时间复杂度O(1)，通过位置存储值
//查找算法，时间复杂度O(1)，通过位置返回值
//插入算法，当插入位置n时，需要移动len-n次，时间复杂度0(n)
//删除算法，时间复杂度0(n)
Status sqlistInit(SqList *list){
    list->length=0;
    return OK;
}
Status sqlistGet(SqList *list, int i, ElemType *e){
    if(list== nullptr || list->length<0 )
        return ERROR;
    if( i<1 || i>list->length)
        return ERROR;

    *e=list->data[i-1];
    return OK;
}
Status sqlistInsert(SqList *list, int i, ElemType e){
    if(list== nullptr || list->length>=sizeof((list->data))/ sizeof(ElemType))
        return ERROR;
    if( i<1 || i>list->length+1 )
        return ERROR;

    if(i<list->length+1){
        for(int j=list->length-1;j>=i-1;j--){
            list->data[j+1]=list->data[j];
        }
    }
    list->data[i-1]=e;
    list->length++;
    return OK;
}
Status sqlistDelete(SqList *list, int i, ElemType *e){
    if(list== nullptr || list->length<1)
        return ERROR;
    if( i<1 || i>list->length )
        return ERROR;

    *e = list->data[i-1];
    for(int j=i-1;j<list->length-1;j++){
        list->data[j]=list->data[j+1];
    }
    list->length--;
    return OK;
}

