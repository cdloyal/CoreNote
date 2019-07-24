/**
 * 作者：chenda
 * 时间：2019/7/23:17:07
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_QUEUE_H
#define CORENOTE_QUEUE_H

#define MAX 50
typedef int ElemType;
typedef struct node{
    ElemType data[MAX];
    int front,rear;
}SqQueue;

SqQueue* creatSqQueue();
int destroySqQueue();
int isSqQueueEmpty(SqQueue* sqQueue);
int isSqQueueFull(SqQueue* sqQueue);
int EnSqQueue(SqQueue* sqQueue,ElemType e);
int DeSqQueue(SqQueue* sqQueue,ElemType *e);

#endif //CORENOTE_QUEUE_H
