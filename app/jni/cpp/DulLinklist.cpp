#include <cstdlib>
#include <cstring>
#include "DulLinklist.h"
 /**
 * 作者：chenda
 * 时间：2019/7/10:11:31
 * 邮箱：
 * 说明：
 */

//泛型双向链表 https://blog.csdn.net/ljianhui/article/details/18748657



static Node* newNode(int data_size){
    Node* node = (Node*)malloc(sizeof(struct node));
    if(node==NULL)
        return NULL;

    node->data = malloc(data_size);
    if(node->data==NULL){
        free(node);
        node=NULL;
        return NULL;
    }
    return node;
}

//初始化链表
int initList(List *list,int data_size){
    //头节点
    Node* head = (Node*)malloc(sizeof(struct node));
    if(head==NULL)
        return -1;
    head->data = NULL;
    head->pre = head;
    head->next = head;

    *list = (List)malloc(sizeof(struct list));
    if(*list==NULL){
        free(head);
        head = NULL;
        return -1;
    }

    (*list)->head = head;
    (*list)->data_size = data_size;
    (*list)->length = 0;

    return 0;
}


//把data的数据内容插入到链表的list末尾
//assign指定数据data间的赋值方法
int insertLast(List list, void *data, void (*assign)(void *, const void *)){
    if(list==NULL)
        return -1;

    Node* node = newNode(list->data_size);
    if(node==NULL)
        return -1;

    if(assign==NULL){
        memcpy(node->data,data,list->data_size);
    } else{
        assign(node->data,data);
    }

    node->pre = list->head->pre;
    node->next = list->head;

    list->head->pre->next = node;
    list->head->pre = node;

    list->length++;
    return 0;
}

Iterator getIterator(List list, int index){
    //节点下标从0开始，头节点不计入下标值
    if(list==NULL)
        return NULL;
    if(index<0 || index>list->length-1)
        return NULL;

    Iterator iterator = list->head;

    //如果index比长度的一半小，从前往后找
    if(index <= (list->length>>1)) {
        for(int i=0;i<=index;i++){
            iterator=iterator->next;
        }
    } else{
        for(int i=list->length-1;i<=index;i--){
            iterator=iterator->pre;
        }
    }
    return iterator;
}

int remove(List list, int index){
    if(list==NULL)
        return -1;
    if(index<0 || index>list->length-1)
        return -1;

    Iterator iterator = getIterator(list,index);
    Node *pre = iterator->pre;
    Node *next = iterator->next;
    pre->next = next;
    next->pre = pre;

    free(iterator);
    iterator=NULL;

    list->length--;
    return 0;
}

//查找链表startIndex到endIndex的最大值
//int (*large)(const void*,const void*) 定义data域大小比较的函数，返回1，代表参数值1大于参数值2；返回0，就是小于
int getMax(List list,int startIndex,int endIndex,int (*large)(const void*,const void*),void* const max){
    if(list==NULL)
        return -1;
    if(startIndex<0 || startIndex>list->length-1)
        return -1;
    if(endIndex<0 || endIndex>list->length-1)
        return -1;
    if(startIndex>endIndex)
        return -1;
    if(large==NULL)
        return -1;

    int maxIndex = startIndex;
    Iterator maxNode = getIterator(list,startIndex);
    Iterator tmp = maxNode;

    for(int i=startIndex+1;i<=endIndex;i++){
        tmp = tmp->next;
        if(large(tmp->data,maxNode->data)){
            maxNode = tmp;
            maxIndex = i;
        }
    }
    memcpy(max,maxNode->data,list->data_size);
    return maxIndex;
}

void* getData(Iterator iterator){
    return iterator->data;
}
