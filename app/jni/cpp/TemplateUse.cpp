/**
 * 作者：chenda
 * 时间：2019/8/1:11:32
 * 邮箱：
 * 说明：
 */





#include <cstdlib>
#include "TemplateUse.h"
template<class DT>
LinkedList<DT>::LinkedList()
{
    start = current = NULL;
}
template<class DT>
LinkedList<DT>::LinkedList(const LinkedList<DT> &aplist)
{
    deepCopy(aplist);
}
template<class DT>
LinkedList<DT>::~LinkedList()
{
    makeEmpty();
}
template<class DT>
LinkedList<DT>& LinkedList<DT>::operator =(const LinkedList<DT> &rlist)
{
    if(this == &rlist)
        return this;
    makeEmpty();
    deepCopy(rlist);
    return this;
}
//在链表的表头插入DT &element，插入后没有当前位置
template<class DT>
void LinkedList<DT>::insert(const DT &element)
{
    current = NULL;
    LDNode<DT> *NNode = new LDNode<DT>;
    NNode->info = element;
    NNode->next = start;
    start = NNode;
}
////在链表的尾部插入
template<class DT>
void LinkedList<DT>::insert_end(const DT &element)
{
    current = NULL;
    LDNode<DT> *NNode = new LDNode<DT>;
    NNode->info = element;
    NNode->next = NULL;
    LDNode<DT> *temp;
    DT item;
    if(start == NULL)
    {
        start = NNode;
        temp = start;
        return;
    }
    temp = start;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = NNode;
}
//把链表中的第一个元素存放在listEl中，并且把第一个元素的位置置为current
template<class DT>
bool LinkedList<DT>::first(DT &listEl)
{
    if(start == NULL)
        return false;
    current = start;
    listEl = start->info;
    return true;
}
//把链表中current的下个元素放在listEl中，current指向下一个元素
template<class DT>
bool LinkedList<DT>::getNext(DT &listEl)
{
    if(current == NULL)
        return false;
    if(current->next == NULL)
    {
        current = NULL;
        return false;
    }
    listEl = current->next->info;
    current = current->next;
    return true;
}
//如果找到elment，返回true,current在getNext()中设置
template<class DT>
bool LinkedList<DT>::find(const DT &element)
{
    DT item;
    if(!first(item))
        return false;  //检查是否为空
    do{
        if(item == element)
            return true;
    }while(getNext(item));
    return false;
}
template<class DT>
bool LinkedList<DT>::retrieve(DT &element)
{
    if(!find(element))
        return false;
    element = current->info;
    return true;
}
template<class DT>
bool LinkedList<DT>::replace(const DT &newElement)
{
    if(current == NULL)
        return false;
    current->info = newElement;
    return true;
}
template<class DT>
bool LinkedList<DT>::remove(DT &element)
{
    current = NULL;
    if(start == NULL)
        return false;
    LDNode<DT> *ptr = start;
    if(start->info == element)
    {
        element = start->info;
        start = ptr->next;
        delete ptr;
        return true;
    }
    while(ptr->next != NULL){
        if(ptr->next->info == element)
        {
            LDNode<DT> *tempptr = ptr->next;
            element = tempptr->info;
            ptr->next = tempptr->next;
            delete tempptr;
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}
template<class DT>
bool LinkedList<DT>::isEmpty() const
{
    return start == NULL;
}
template<class DT>
void LinkedList<DT>::makeEmpty()
{
    while(start != NULL)
    {
        current = start;
        start = start->next;
        delete current;
    }
    current = NULL;
}
template<class DT>
void LinkedList<DT>::deepCopy(const LinkedList<DT> &original)
{
    start = current = NULL;
    if(original.start == NULL)
        return;
    LDNode<DT> *copyptr = start = new LDNode<DT>;
    LDNode<DT> *originalptr = original.start;
    copyptr->info = originalptr->info;
    if(originalptr == original.current)
        current = copyptr;
    while(originalptr->next  != NULL)
    {
        copyptr->next = new LDNode<DT>;  //这一句有难度啊！
        originalptr = originalptr->next;
        copyptr = copyptr->next;
        copyptr->info = originalptr->info;
        if(originalptr == original.current)
            current = copyptr;
    }
    copyptr->next = NULL;
}
//#endif