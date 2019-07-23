/**
 * 作者：chenda
 * 时间：2019/7/23:17:06
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_STACK_H
#define CORENOTE_STACK_H

typedef int DataType;
typedef struct node{
    DataType data;
    struct node* next;
}Stack;

Stack* createStack();
void stackEmpty(Stack* stack);
void stackDestory(Stack* stack);
int isEmpty(Stack* stack);
int pushStack(Stack* stack,DataType data);
int popEmpty(Stack* stack,DataType* data);
DataType getTopElement(Stack* stack);

#endif //CORENOTE_STACK_H
