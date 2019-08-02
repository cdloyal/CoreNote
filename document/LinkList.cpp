#include <cstdlib>
#include <Linklist.h>


#include "Linklist.h"

/**
 * 作者：chenda
 * 时间：2019/8/1:16:31
 * 邮箱：
 * 说明：
 */


template <class T>
LinkedList<T>::LinkedList() {
    LinkedNode<T> *node = new LinkedNode<T>();
    node->next = NULL;
    this->start= node;
}
template <class T>
LinkedList<T>::~LinkedList() {

}

template<class T>
int LinkedList<T>::insert(const T &element) {
    LinkedNode<T> *node = new LinkedNode<T>();
    node->data = element;
    node->next = this->start->next;
    this->start->next = node;
    return 0;
}


template<class T>
LinkedList<T>::LLIterator::LLIterator() {
    this->current = start;

}




template<class T>
bool LinkedList<T>::LLIterator::hasNext() {
    return current->next!=NULL;
}

template<class T>
T LinkedList<T>::LLIterator::next() {
    this->current = this->current->next;
    return this->current->data;
}

template<class T>
void LinkedList<T>::LLIterator::remove() {

}
