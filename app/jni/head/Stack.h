/**
 * 作者：chenda
 * 时间：2019/7/23:17:06
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_STACK_H
#define CORENOTE_STACK_H


typedef struct StackNode{
    void* data;
    struct StackNode* next;
}StackNode;
typedef struct Stack{
    int data_size;
    StackNode* stack;
}Stack;

Stack* createStack(int data_size);
void stackEmpty(Stack* stack);
void stackDestory(Stack*& stack);
int isStackEmpty(Stack *stack);
int pushStack(Stack* stack,void* data);
int popStack(Stack *stack, void *data);
int getTopElement(Stack* stack,void* data);

/**
 * 栈的应用：逆波兰计算机，后缀表达式
 *  a+b --> a b +
 *  a+(b-c) --> a b c - +
 *  a+(b-c)*d --> a b c - d * +
 *  a+d*(b-c) --> a d b c - * +
 *
 * 将数字压入栈，当遇到算符，从栈中pop两个数字进行算术，然后将结果重新压入栈
 *
 * 但是如果我们还是要中缀表达式呢？要将中缀表达式转换成后缀表达式再计算
 * 1+(2-3*5)*4+10/5
 *
 * 1       2     3    5      4    10    5
 *   +  (     -     *   ) *     +    /
 *
 *
 * */


#endif //CORENOTE_STACK_H
