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
    int size;
    class LLIterator : public Iterator<T>{
    public:
        LinkedNode<T> *current;
        LinkedList<T> *list;
        LLIterator(LinkedList<T> *list);
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
        return LinkedList::LLIterator(this);
    }
    /*
    * Description:     linklist转array
    * Input:           array   输出
    * Return:          int     >=0成功返回array得实际长度，<失败
    */
    int toArray(T *&array);
};




template<class T>
LinkedList<T>::LinkedList(){
    LinkedNode<T> *node = new LinkedNode<T>();
    node->next = node;
    node->pre = node;
    size = 0;
    this->head= node;
}

template<class T>
LinkedList<T>::~LinkedList() {
    LLIterator it = iterator();
    while (it.hasNext()){
        it.next();
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
    size++;
    return 0;
}

template<class T>
int LinkedList<T>::toArray(T *&array) {
    if(size==0){
        LOGD("error toArray() LinkedList size 0");
        return -1;
    }
    array = (T *)malloc(sizeof(T)*size);
    if(array==NULL){
        LOGD("error toArray() malloc array overflow");
        return -1;
    }
    int i=0;
    LLIterator it = iterator();
    while (it.hasNext()){
        array[i++]=it.next();
    }
    return size;
}



template<class T>
LinkedList<T>::LLIterator::LLIterator(LinkedList<T> *list) {
    this->list=list;
    this->current = list->head;
}

template<class T>
bool LinkedList<T>::LLIterator::hasNext() {
    return current->next!= list->head;
}

template<class T>
T LinkedList<T>::LLIterator::next() {
    this->current = this->current->next;
    return this->current->data;
}

template<class T>
void LinkedList<T>::LLIterator::remove() {
    if(current==list->head)
        return;
    LinkedNode<T> *tmp = current->pre;
    tmp->next = current->next;
    current->next->pre = tmp;
    delete current;
    current = tmp;
    list->size--;
}

#endif //CORENOTE_LINKEDLIST_H
