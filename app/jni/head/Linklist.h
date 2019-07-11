/**
 * 作者：chenda
 * 时间：2019/6/18:13:46
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_LINKLIST_H
#define CORENOTE_LINKLIST_H


typedef int ElemType;

#define OK 1
#define ERROR 0
typedef int Status;


//线性表的链式存储结构,带头节点
typedef int NodeElemType;
typedef struct LinkNode{
    NodeElemType data;
    struct LinkNode* next;
}LinkList;
Status linklistCreateHead(LinkList *list,int n);
//Status linklistCreateTrail(LinkList *list,int n);
Status linklistCreateTrail(LinkList *list,int n);  //为什么用二级指针？因为函数内部molloc，使得形参的地址改变，
Status linklistClear(LinkList *list);
Status linklistGet(LinkList *list, int i, NodeElemType *e);
Status linklistInsert(LinkList *list, int i, NodeElemType e);
Status linklistDelete(LinkList *list, int i, NodeElemType *e);



#endif