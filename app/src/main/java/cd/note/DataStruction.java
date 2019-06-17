package cd.note;

/**
  * @Description:    数据结构的概念
  * @Author:         陈达
  * @CreateDate:     2019/6/16 15:00
  * @UpdateUser:     陈达
  * @UpdateDate:     2019/6/16 15:00
  * @UpdateRemark:   更新说明：
  * @Version:        1.0
  */
public class DataStruction {

    //数据结构是相互之间存在一种或者多种特定关系的数据元素的集合

    //逻辑结构:数据对象中数据元素之间的相互关系
    //集合结构（元素间平等）、线性结构（一对一关系）、树形结构（一对多层次关系）、图形结构（多对多）

    //物理结构：数据的逻辑结构在计算机的存储形式
    //顺序存储结构：把数据元素存储在地址连续的存储单元里。删除、插入元素不方便
    //链式存储结构：数据存储的任意的存储单元。需要指针存放数据元素的地址，通过地址找到相应元素

    //算法时间复杂度
    //T(n)=O(f(n)),f(n)是问题规模n的某个函数，随问题规模n的增大，算法执行时间的增长率和f(n)的增长率相同
    //0(1)      常数阶     12
    //O(n)      线性阶     2n+3
    //O(n^2)    平方阶     n*(n+1)/2
    //O(logn)   对数阶     int c=1;while(c<n){c=c*2};  ==> 2^x=n ==> x=logn
    //O(1)<O(logn)<O(n)<O(nlogn)<O(n^2)<O(n^3)<O(2^n)<O(n!)<O(n^n)

    //算法的空间复杂度
    //S(n)=O(f(n)),f(n)是占存储空间n的某个函数，

    //前驱后继

    //线性表的顺序存储结构
    /**
     *  #define MAXSIZE 20
     *  typedef int ElemType;
     *  typedef struct{
     *      int length;
     *      ElemType data[MAXSIZE];
     *  }sqList;
     **/
    //存储算法，时间复杂度O(1)，通过位置存储值
    //查找算法，时间复杂度O(1)，通过位置返回值
    //插入算法，当插入位置n时，需要移动len-n次，时间复杂度0(n)
    //删除算法，时间复杂度0(n)

    //线性表的链式存储结构
    //节点：数据域和指针域
    //头节点：链表的第一个节点；

    //单链表
    /**
     *  typedef struct Node{
     *      ElemType data;
     *      struct Node* next;
     *  }Node;
     *
     *  typedef struct Node *LinkList;  //LinkList是指向链表的头节点，LinkList->next指向链表的第一个节点
     * */
    //  头指针--> |head--> a1|addr1--> a2|addr2-->......-->an|NULL
    //  头指针--> |NULL        空链表
    //存储和查找算法,当查找位置n时，指针需要移动n次，时间复杂度0(n)
    //插入和删除算法，在节点p和q之间插入s，查找到p和q节点，s->next=q,p->next=s就可以了，插入和删除时间复杂度0(1)
    //整表创建，头部插入、尾部插入
    //整表删除，将下一节点赋值给q，释放p，q赋值给p

    //静态链表：用数组描述的链表
    //数组的每个数据元素由数据域data和游标cur组成
    //
}
