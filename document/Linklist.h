/**
 * 作者：chenda
 * 时间：2019/8/1:16:31
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_LINKLIST_H
#define CORENOTE_LINKLIST_H

#include "Iterator.h"

//https://bbs.csdn.net/topics/390983752?list=lz

template <class T>
struct LinkedNode{
    T data;
    struct LinkedNode* next;
};

template <class T>
class LinkedList{
private:
    static LinkedNode<T> *start;



public:
    LinkedList();
    ~LinkedList();

    friend class LLIterator;
    class LLIterator : public Iterator<T>{
    public:
        LinkedNode<T> *current;
        LLIterator();
        bool hasNext();
        T next();
        void remove();
    }it;

    //在链表的表头插入T &element
    int insert(const T &element);
    LLIterator iterator(){
        return LinkedList::LLIterator();
    }

};


#endif //CORENOTE_LINKLIST_H
