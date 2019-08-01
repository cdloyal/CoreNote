/**
 * 作者：chenda
 * 时间：2019/8/1:11:32
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_TEMPLATEUSE_H
#define CORENOTE_TEMPLATEUSE_H


//单向链表的实现
//查找、插入和移除某个元素、复制、清空单向链表的时间复杂度均为O(n)
//设计类时，应尽量减少类的成员函数之间的依赖关系
template<class DT>
struct LDNode
{
    DT info;
    LDNode<DT> *next;
};
template<class DT>
class LinkedList
{
public:
    LinkedList();
    LinkedList(const LinkedList<DT> &aplist);
    ~LinkedList();
    LinkedList<DT>& operator=(const LinkedList<DT> &rlist);
    void insert(const DT &element);  //在链表的头部之前插入
    void insert_end(const DT &element);  //在链表的尾部插入
    bool first(DT &listEl);     //得到对头的数据
    inline bool getNext(DT &listEl);   //得到当前指针所指的下一个数据
    bool find(const DT &element);    //查找一个数据
    bool retrieve(DT &element);       //检索一个数据
    bool replace(const DT &newElement);    //更改一个数据
    bool remove(DT &element);
    bool isEmpty() const;
    void makeEmpty();
private:
    LDNode<DT> *start;   //指向头结点
    LDNode<DT> *current;    //指向当前的结点
    inline void deepCopy(const LinkedList<DT> &original);   //"深复制"
};

#endif //CORENOTE_TEMPLATEUSE_H
