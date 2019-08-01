/**
 * 作者：chenda
 * 时间：2019/8/1:16:31
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_LINKLIST_H
#define CORENOTE_LINKLIST_H

template <class T>
struct LinkNode{
    T data;
    struct LinkNode* next;
};

template <class T>
class LinkList{

    int linklistCreateHead(LinkList *list,int n);
//Status linklistCreateTrail(LinkList *list,int n);
    int linklistCreateTrail(LinkList *list,int n);  //为什么用二级指针？因为函数内部molloc，使得形参的地址改变，
    int linklistClear(LinkList *list);
    int linklistGet(LinkList *list, int i, T *e);
    int linklistInsert(LinkList *list, int i, T e);
    int linklistDelete(LinkList *list, int i, T *e);
};



#endif //CORENOTE_LINKLIST_H
