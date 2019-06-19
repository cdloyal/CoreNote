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

//线性表的操作
#define OK 1
#define ERROR 0
typedef int Status;
Status initSqList(SqList* list);
Status GetElem(SqList* list,int i,ElemType* e);
Status insertElem(SqList* list,int i,ElemType e);
Status deleteElem(SqList* list,int i,ElemType* e);


#endif //CORENOTE_DATASTRUCTURE_H
