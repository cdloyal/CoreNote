/**
 * 作者：chenda
 * 时间：2019/8/9:16:07
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_CMP_H
#define CORENOTE_CMP_H

template <class T>
int cmp ( const void *a , const void *b )
{
    return *(T *)a - *(T *)b;   //T为类型
}

template <class T>
int cmp_ptr ( const void *a , const void *b )
{
    return **(T *)a - **(T *)b; //T为指针
}

#endif //CORENOTE_CMP_H
