#include <jni.h>
#include "log.h"
#include "datastructure.h"
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
Status initSqList(SqList* list){
    list->length=0;
    return OK;
}
Status GetElem(SqList* list,int i,ElemType* e){
    if(list== nullptr || list->length<0 )
        return ERROR;
    if( i<1 || i>list->length)
        return ERROR;

    *e=list->data[i-1];
    return OK;
}
Status insertElem(SqList* list,int i,ElemType e){
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
Status deleteElem(SqList* list,int i,ElemType* e){
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

//线性表的链式存储结构
//节点：数据域和指针域
//头节点：链表的第一个节点；

//单链表
/**
 *  typedef struct Node{
 *      ElemType data;
 *      struct Node* next;
 *  }Node;
 *
 *  typedef struct Node *LinkList;  //LinkList是指向链表的头节点，LinkList->next指向链表的第一个节点
 * */
//  头指针--> |head--> a1|addr1--> a2|addr2-->......-->an|NULL
//  头指针--> |NULL        空链表
//存储和查找算法,当查找位置n时，指针需要移动n次，时间复杂度0(n)
//插入和删除算法，在节点p和q之间插入s，查找到p和q节点，s->next=q,p->next=s就可以了，插入和删除时间复杂度0(1)
//整表创建，头部插入、尾部插入
//整表删除，将下一节点赋值给q，释放p，q赋值给p

//关于线性表的一些简单应用  http://www.cnblogs.com/zydark/p/7778131.html

//静态链表：用数组描述的链表,在一些低级语言没有指针链表的实现方式
//数组的每个数据元素由数据域data和游标cur组成
/**
 * #define MAXSIZE 1000
 * typedef struct {
 *     ElemType data;
 *     int cur;
 * }Component,StaticLinkList[MAXSIZE];
 * */

extern "C"
JNIEXPORT jint JNICALL
Java_cd_note_others_DataStructure_test(JNIEnv *env, jclass type) {

    LOGD("线性表顺序存储结构");
    ElemType e;
    SqList sqList;
    initSqList(&sqList);
    LOGD("sqList.length=%d,sqList.data[0]=%d",sqList.length,sqList.data[0]);
    int ret = insertElem(&sqList,1,1);
    ret = GetElem(&sqList,1,&e);
    LOGD("sqList.length=%d,GetElem(&sqList,1,&e)=%d",sqList.length,e);
    ret = insertElem(&sqList,1,2);
    ret = GetElem(&sqList,1,&e);
    LOGD("sqList.length=%d,GetElem(&sqList,1,&e)=%d",sqList.length,e);
    ret = deleteElem(&sqList,1,&e);
    LOGD("sqList.length=%d,deleteElem(&sqList,1,&e)=%d",sqList.length,e);
    ret = GetElem(&sqList,1,&e);
    LOGD("sqList.length=%d,GetElem(&sqList,1,&e)=%d",sqList.length,e);
    ret = deleteElem(&sqList,1,&e);
    LOGD("sqList.length=%d,deleteElem(&sqList,1,&e)=%d",sqList.length,e);

    return 0;

}