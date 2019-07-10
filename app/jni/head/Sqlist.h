/**
 * 作者：chenda
 * 时间：2019/6/18:13:46
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_SQLIST_H
#define CORENOTE_SQLIST_H


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


#endif
