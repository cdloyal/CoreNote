#include <cstdlib>
#include <time.h>
#include "Linklist_C.h"
 /**
 * 作者：chenda
 * 时间：2019/6/18:13:39
 * 邮箱：
 * 说明：数据结构的概念
 */

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

Status linklistCreateHead(LinkList *list,int n){
    LinkList *p;
    int i;
    list = (LinkList *)malloc(sizeof(LinkList));
    list->next=NULL;
    srand(time(0));     //初始化随机数种子
    for(i=0;i<n;i++){
        p = (LinkList* )malloc(sizeof(LinkList));
        p->data=rand()%100+1;   //随机产生100以内的数字
        p->next=list->next;
        list->next = p;
    }
    return OK;
}
Status linklistCreateTrail(LinkList *list,int n){
    LinkList *p, *trail;
    int i;
    trail = list;
    srand(time(0));     //初始化随机数种子
    for(i=0;i<n;i++){
        p = (LinkList* )malloc(sizeof(LinkList));
        p->data=rand()%100+1;   //随机产生100以内的数字
        trail->next = p;
        p->next=NULL;
        trail = p;
    }
    return OK;
}
Status linklistClear(LinkList *list){
    LinkList *p,*q;

    if(list==NULL)
        return OK;

    p=list->next;
    while (p!=NULL){
        q=p;
        p=p->next;
        free(q);
    }

    list->next=NULL;
    return OK;
}
Status linklistGet(LinkList *list, int i, NodeElemType *e){
    LinkList *p;
    if(list==NULL)
        return ERROR;
    if(i<1)
        return ERROR;
    p = list;         //带头节点
    for(int j=0;j<i;j++){
        if(p==NULL){
            return ERROR;
        }
        p = p->next;
    }
    if(p==NULL){
        return ERROR;
    }
    *e = p->data;
    return OK;
}

Status linklistInsert(LinkList *list, int i, NodeElemType e){
    LinkList *p,*q;
    if(list==NULL)
        return ERROR;
    if(i<1)
        return ERROR;
    q = (LinkList* )malloc(sizeof(LinkList));
    if(q==NULL)
        return ERROR;

    p = list;         //带头节点
    for(int j=0;j<i-1;j++){
        if(p==NULL){
            return ERROR;
        }
        p = p->next;
    }
    if(p==NULL){
        return ERROR;
    }
    q->data = e;
    q->next = p->next;
    p->next = q;
    return OK;
}
Status linklistDelete(LinkList *list, int i, NodeElemType *e){
    LinkList *p,*q;
    if(list==NULL)
        return ERROR;
    if(i<1)
        return ERROR;

    p = list;         //带头节点
    for(int j=1;j<=i-1;j++){
        if(p==NULL){
            return ERROR;
        }
        p = p->next;
    }
    if(p==NULL){
        return ERROR;
    }
    q=p->next;
    if(q==NULL){
        return ERROR;
    }
    p->next=q->next;
    *e = q->data;
    free(q);
    return OK;
}

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
