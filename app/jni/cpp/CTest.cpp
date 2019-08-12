#include <log.h>
#include <cstdlib>
#include "CTest.h"

#include <set>
#include <vector>
#include <CTest.h>

#include <istream>
#include <deque>
#include <list>
#include "Cmp.h"

/**
 * 作者：chenda
 * 时间：2019/8/1:9:18
 * 邮箱：
 * 说明：
 */

void fun_2(double &a){ a=5.0;}

void fun_2(int &a){ a=5;}           //形参a是int型的引用
void fun_3(int *&a){                //形参a是int*型引用,假设实参int *b;
    a=(int*)malloc(sizeof(int));    //那么a,b都指向另外一个地址
    *a=4;
}
void fun_4(int **a){                //形参a是int*型引用
    *a=(int*)malloc(sizeof(int));
    **a=3;
}

int & fun5(){
    int a=6;
    return a;
}

class test2{
    int a = 7;
public:
    int& getA(){
        return a;
    }
};

CTest::CTest() {
    LOGD("cTest CTest()");
}
CTest::CTest(const CTest &ctest) {
    LOGD("cTest CTest(const CTest &ctest)");
    *this = ctest;
}
CTest::~CTest() {
    LOGD("cTest ~CTest（）");
}



std::unique_ptr<std::string> demo(const char * s)

{

    std::unique_ptr<std::string> temp (new std::string(s));
    return temp;

}

void ctest(void){

    std::list<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(7);
    list.push_front(5);
//    auto it  =list.rend();
//    while(it != list.rbegin()){
//        LOGD("ctest rit=%d",(*--it));
//    }
//    auto it  =list.rbegin();
//    while(it != list.rend()){
//        LOGD("ctest rit=%d",(*it++));
//    }
    list.pop_back();
    list.pop_back();
    auto it  =list.rbegin();
    while(it != list.rend()){
        LOGD("ctest rit=%d",(*it++));
    }

    std::shared_ptr<int> ptr = std::make_shared<int>(88);

    int num[10] = {8,2,6,3,5,1,8,3,5,7};
    qsort(num,10,sizeof(num[0]),cmp<int>);
    for(int i=0;i<10;i++){
        LOGD("ctest num[%d]=%d",i,num[i]);
    }

    //智能指针使用 https://blog.csdn.net/weixin_34186931/article/details/87121070
    std::unique_ptr<std::string> ps(new std::string("1212"));

    test2 t2;
    int testa = t2.getA();
    testa = 8;
    LOGD("ctest t2.getA()=%d",t2.getA());
    int &testa1 = t2.getA();
    testa1 = 9;
    LOGD("ctest t2.getA()=%d",t2.getA());

    char ch1 = 'h';
    char ch2[] = "ah";
    LOGD("(ch1==ch2)?%d",(ch1==ch2[1]));

    auto *pt0 = static_cast<pointerTemplate<int> *>(malloc(sizeof(pointerTemplate<int>)));
    int ii = 6;
    pointerTemplate<int> pt1;
    pt1.t = 1;
    pt1.i = &ii;
    pointerTemplate<int> pt2 = pt1;
    LOGD("ctest &pt1=%d",&pt1);
    LOGD("ctest pt1.i=%d",pt1.i);
    LOGD("ctest *pt1.i=%d",*pt1.i);
    LOGD("ctest &pt2=%d",&pt2);
    LOGD("ctest pt2.i=%d",pt2.i);
    LOGD("ctest *pt1.i=%d",*pt2.i);

    //https://blog.csdn.net/x
    // ingjiarong/article/details/47282255
//    char *str = "acbcdef";
//    str[3]='x'; //运行时出错,str指向的是常量区,常量区的值不能被修改

//    const char *str = "acbcdef";
//    str[3]='x'; //编辑时提示出错

    //常量指针,不能修改指针指向的值
    int a = 5;
    const int *b = &a;
    int const *c = &a;
    a=6;
    //指针常量,不能修改指针,可以修改指针指向的值
    int* const d = &a;
    //指向常量的常指针
    const int* const p = &a;



    int e = 1;
    int *f = &e;
    fun_2(e);
    LOGD("ctest %d",e);
    fun_3(f);
    LOGD("ctest %d",e);     //调用fun_3()后f不再指向e
    LOGD("ctest %d",*f);
    fun_4(&f);              //调用fun_3()后f不再指向e
    LOGD("ctest %d",e);
    LOGD("ctest %d",*f);

    int g=fun5();
    LOGD("ctest %d",g);

    //符号重载
    CTest cTest1;
    cTest1.a = 100;
    CTest cTest2=cTest1;
    LOGD("cTest2.a = %d",cTest2.a);
    cTest2.a = 500;
    CTest cTest3= cTest1;
    LOGD("cTest3 = %d",cTest3.a);
    LOGD("&cTest1 = %d",&cTest1);

    strTest strTest1;
    strTest1.a=5;
    strTest strTest2;
    strTest2.a=4;
    LOGD("strTest1>strTest2 = %d",strTest1>strTest2);


    //template 指针
    int h = 111;
    pointerTemplate<int*> pt;
    pt.t = &h;
    LOGD("pt.t=%d,&h=%d",(pt.t),&h);

    char c1[6] = "12233";
    char *c2 = new char[2] ;
    c2[0] = '1';
    c2[1] = '\0';
    LOGD("cTest c2.len=%d",strlen(c2));
    LOGD("cTest c2.size=%d",sizeof(c2));
    strcpy(c1,c2);
    LOGD("cTest c1=%s",c1);

    double limitDouble = std::numeric_limits<double>::infinity();
    #define MAX (1.0/0.0)
    double dd = limitDouble+1000;
    LOGD("cTest limitDouble %f",limitDouble);
    LOGD("cTest dd %f",dd);
    LOGD("cTest limitDouble>10000000000 ? %d",limitDouble>100);
    LOGD("cTest MAX>10000000000 ? %d",MAX>100);

    int **edge;
    edge = new int* [2];
    for(int i=0; i<2;i++)
        edge[i] = new int[3];

    edge[0][1]=3;
    LOGD("cTest edge[0][1] = %d",edge[0][1]);
    delete []edge;
}



