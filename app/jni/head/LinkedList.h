/**
 * 作者：chenda
 * 时间：2019/8/2:9:36
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_LINKEDLIST_H
#define CORENOTE_LINKEDLIST_H

#include <cstdlib>
#include <android/log.h>
#include "Iterator.h"
#include "log.h"

template <class T>
struct LinkedNode{
    T data;
    LinkedNode *next, *pre;
};

template <class T>
class LinkedList{
private:
    LinkedNode<T> *head;

public:
    class LLIterator : public Iterator<T>{
    public:
        LinkedNode<T> *head;
        LinkedNode<T> *current;
        LLIterator(const LinkedList<T> &list);
        bool hasNext();
        T next();
        void remove();
    };

    LinkedList();
    ~LinkedList();
    //在链表的表尾插入T &element
    int insert(const T &element);
    //获取游标
    LLIterator iterator(){
        return LinkedList::LLIterator(*this);
    }
};




template<class T>
LinkedList<T>::LinkedList(){
    LinkedNode<T> *node = new LinkedNode<T>();
    node->next = node;
    node->pre = node;
    this->head= node;
}

template<class T>
LinkedList<T>::~LinkedList() {
    LLIterator it = iterator();
    while (it.current !=head && it.hasNext()){
        it.remove();
    }
    delete head;
}

template<class T>
int LinkedList<T>::insert(const T &element) {
    LinkedNode<T> *node = new LinkedNode<T>();
    node->data = element;
    node->next = this->head;
    node->pre = this->head->pre;
    this->head->pre->next = node;
    this->head->pre = node;
    return 0;
}


template<class T>
LinkedList<T>::LLIterator::LLIterator(const LinkedList<T> &list) {
    this->head = this->current = list.head;
}

template<class T>
bool LinkedList<T>::LLIterator::hasNext() {
    return current->next!= this->head;
}

template<class T>
T LinkedList<T>::LLIterator::next() {
    this->current = this->current->next;
    return this->current->data;
}

template<class T>
void LinkedList<T>::LLIterator::remove() {
    if(current==head)
        return;
    LinkedNode<T> *tmp = current->pre;
    tmp->next = current->next;
    current->next->pre = tmp;
    delete current;
    current = tmp;
}

#endif //CORENOTE_LINKEDLIST_H
