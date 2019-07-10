/**
 * 作者：chenda
 * 时间：2019/7/10:13:26
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_DULLINKLIST_H
#define CORENOTE_DULLINKLIST_H

//泛型循环双链表，带头节点，节点下标从0开始，头节点不计入下标值

typedef struct node{
    void *data;     //数据域指针
    struct node *pre;
    struct node *next;
}Node;

struct list{
    struct node *head;
    int data_size;  //数据域所占内存大小
    int length;
};

//定义结点指针 node *为List类型的迭代器
typedef struct node *Iterator;

//List类型的定义
typedef struct list *List;

//初始化链表
int initList(List *list,int data_size);

//把data的数据内容插入到链表的list末尾
//assign指定数据data间的赋值方法
int insertLast(List list, void *data, void (*assign)(void *, const void *));

//返回index位置的迭代器
Iterator getIterator(List list, int index);

void* getData(Iterator iterator);

//删除index位置的元素
int remove(List list, int index);

//查找链表startIndex到endIndex的最大值
//int (*large)(const void*,const void*) 定义data域大小比较的函数，返回1，代表参数值1大于参数值2；返回0，就是小于
//返回最大值的下标
int getMax(List list,int startIndex,int endIndex,int (*large)(const void*,const void*),void* max);



#endif //CORENOTE_DULLINKLIST_H
