/**
 * 作者：chenda
 * 时间：2019/7/23:17:07
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_QUEUE_H
#define CORENOTE_QUEUE_H


typedef struct LQNode{
    void* data;
    struct LQNode *next;
}LQNode;

typedef struct LQueue{
    int data_size;
    LQNode *front,*rear;
}LQueue;

LQueue* creatLQueue(int data_size);
int emptyLQueue(LQueue* queue);
int destroyLQueue(LQueue* queue);
int isLQueueEmpty(LQueue *Queue);
//int isLQueueFull(LQueue *Queue);
int enLQueue(LQueue *Queue, void *e);
int deLQueue(LQueue *Queue,void *e);

#endif //CORENOTE_QUEUE_H
