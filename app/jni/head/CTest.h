/**
 * 作者：chenda
 * 时间：2019/8/1:9:18
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_CTEST_H
#define CORENOTE_CTEST_H

class CTest{
    CTest * operator=(const CTest &copy);

public:
    int a;
};

typedef struct strTest{
    int a;

    bool operator>(const struct strTest & src){
        return this->a>src.a;
    }
}strTest;

template <class T>
class pointerTemplate{
public:
    pointerTemplate();
    T t;
    int *i;
};
//为什么C++编译器不能支持对模板的分离式编译
//https://blog.csdn.net/pongba/article/details/19130
template<class T>
pointerTemplate<T>::pointerTemplate() {

}

void ctest(void);

#endif //CORENOTE_CTEST_H
