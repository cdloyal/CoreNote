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

void ctest(void);

#endif //CORENOTE_CTEST_H
