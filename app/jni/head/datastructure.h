/**
 * 作者：chenda
 * 时间：2019/6/18:13:46
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_DATASTRUCTURE_H
#define CORENOTE_DATASTRUCTURE_H


//线性表的顺序存储结构
#define SqList_MAXSIZE 20
typedef int ElemType;
typedef struct{
    int length;
    ElemType data[SqList_MAXSIZE];
}SqList;

//线性表的查找
#define OK 1
#define ERROR 0
typedef int Status;
Status sqlistInit(SqList *list);
Status sqlistGet(SqList *list, int i, ElemType *e);
Status sqlistInsert(SqList *list, int i, ElemType e);
Status sqlistDelete(SqList *list, int i, ElemType *e);


//线性表的链式存储结构,带头节点
typedef int NodeElemType;
typedef struct Node{
    NodeElemType data;
    struct Node* next;
}LinkList;
Status linklistCreateHead(LinkList *list,int n);
//Status linklistCreateTrail(LinkList *list,int n);
Status linklistCreateTrail(LinkList *list,int n);  //为什么用二级指针？因为函数内部molloc，使得形参的地址改变，
Status linklistClear(LinkList *list);
Status linklistGet(LinkList *list, int i, NodeElemType *e);
Status linklistInsert(LinkList *list, int i, NodeElemType e);
Status linklistDelete(LinkList *list, int i, NodeElemType *e);



#endif //CORENOTE_DATASTRUCTURE_H
