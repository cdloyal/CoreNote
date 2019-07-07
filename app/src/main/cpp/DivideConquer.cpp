#include <jni.h>
#include <cstring>
#include "DivideConquer.h"
//
// Created by chenda on 2019/6/23.
//

/**
 * 函数增长
 *  theta(g(n)) = {f(n):存在正常量c1 c2和n0,使得对所有n>=n0，有0<=c1*g(n)<=f(n)<=c2*g(n)}
 *  假设f(n)=0.5n^2-3n = thrta(n^2) = theta(g(n))
 *  则存在正常量c1 c2和n0,使得对所有n>=n0，有0<=c1*n^2<=0.5n^2-3n<=c2*n^2
 *      c1<=0.5-3/n<=c2
 *      c1取比a小一些，c2取比a大一些，可以满足不等式，比如：
 *      假设c1=a/4,c2=7a/4 且n0=2*max(|b|/a,(|c|/a)^0.5)
 *
 *  渐进紧界
 *  f(n)=theta(g(n))    theta(g(n))是函数的集合，可以在这个集合找到f(n),且0<=c1*g(n)<=f(n)<=c2*g(n)
 *
 *  渐进上界
 *  O(g(n)) = {f(n):存在正常量c1 c2和n0,使得对所有n>=n0，有0<=f(n)<=c*g(n)}
 *  非渐进紧确上界     远离上界
 *  o(g(n))     2n=o(n^2)   3n^2 != o(n^2)
 *
 *  渐进下界        欧姆
 *  OHM(g(n)) = {f(n):存在正常量c1 c2和n0,使得对所有n>=n0，有f(n)>=c*g(n)}
 *  非渐进紧确下界
 *  w(g(n))
 *
 *
 *
 * */


/**
 * 最大子数组问题
 *
 * 给出未来17天股票价格，目标是实现最大收益
 *      天   0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16
 *    价格 110 113 110  85 105 102  86  63  81 101  94  106 101  79  94  90  97
 *    变化      13  -3 -25  20  -3 -16 -23  18  20  -7   12  -5 -22  15  -4   7
 *
 * 我们希望“低价买进，高价卖出”。但是有可能最低价在前，最高价在后。
 *
 * 1、暴力求解的方法：
 *  简单的尝试每对可能的买进和卖出日期组合，只要卖出日期在买入日期之后即可
 *  n天中有(n)
 *         (2)种组合，Theta(n^2)
 *
 * 2、最大子数组
 *  我们目的是寻找一段日期，使得从第一天到最后一条的股票价格静变值最大。
 *  我们不再从每日的价格看到输入数据，而是考察每日价格变化，从第i天的价格
 *  变化定义变成第i天和第i-1天的价格差。
 *  那么问题就转向为寻找A的和最大的非空连续子数组。最大子数组可能不止一个，而我们只需一个
 *
 *  即使变成价格差也是可以用暴力求解的，T(n)还是等于Theta(n^2)
 *
 *  用分治法：
 *  问题：求数组A[low,high]的最大子数组Max(left,right)
 *  分解：将数组分解成两个子数组A[low,middle]、A[middle+1,high]；还要考虑一种情况最大子数组Max(left,right)，low<=left<=middle<right<=high
 *  解决：递归解出两个子数组A[low,middle]、A[middle+1,high]的最大子数组Max(left,right)。边界low==right,返回。
 *  合并：解low<=left<=middle<right<=high的最大子数组Max(left,right)，和上面解得的两个最大子数组Max(left,right)比较。
 *
 *  解low<=left<=middle<right<=high的最大子数组Max(left,right)
 *  FIND_MAX_AROSSING_SUBARRAY(A,low,middle,high)
 *      sum = middle         //当前和
 *      max_left_sum = sum     //当前左边最大和
 *      left = middle
 *      //先求左边最大值
 *      for i = middle-1 to low
 *          sum += A[i]
 *          if sum>max_left_sum
 *              max_left_sum=sum
 *              left=i
 *
 *      right=middle+1
 *      sum=middle+1
 *      max_right_sum=sum
 *          for i = middle+2 to high
 *          sum += A[i]
 *          if sum>max_right_sum
 *              max_right_sum=sum
 *              right=i
 *
 *      return (left,right,max_left_sum+max_right_sum)
 *
 *  FIND_MAXIMUM_SUBARRAY(A,low,high)
 *      if(low==high)
 *          return (low,high,A[low])
 *
 *      middle = low+(high-low)/2
 *      (low_left,low_right,low_max) = FIND_MAXIMUM_SUBARRAY(A,low,middle)
 *      (high_left,high_right,high_max) = FIND_MAXIMUM_SUBARRAY(A,middle+1,high)
 *      (cross_left,cross_right,cross_max) =FIND_MAX_AROSSING_SUBARRAY(A,low,middle,high)
 *
 *      if(low_max>=high_max && low_left>=cross_max)
 *          return (low_left,low_right,low_max)
 *      eles if(high_max>=low_max && high_max>=cross_max)
 *          return (high_left,high_right,high_max)
 *      else
 *          return (cross_left,cross_right,cross_max)
 *
 * */

void findMaxCrossSubArray(int *A, int low, int middle, int high, int *max, int *left, int *right) {
    int sum = A[middle];         //当前和
    int max_left_sum = sum;     //当前左边最大和
    *left = middle;
    //先求左边最大值
    for(int i=middle-1;i>=low;i-- ){
        sum += A[i];
        if(sum > max_left_sum){
            max_left_sum = sum;
            *left = i;
        }
    }

    *right = middle + 1;
    sum = A[middle + 1];
    int max_right_sum = sum;
    for(int i=middle+2;i<=high;i++ ){
        sum += A[i];
        if(sum > max_right_sum){
            max_right_sum = sum;
            *right = i;
        }
    }

    *max = max_left_sum + max_right_sum;

}

void findMaxSubArray(int *A, int low, int high, int *max, int *left, int *right) {
    int low_left, low_right, low_max;
    int high_left, high_right, high_max;
    int cross_left, cross_right, cross_max;

    if (low == high) {
        *max = A[low];
        *left = low;
        *right = low;
        return;
    }

    int middle = low + (high - low) / 2;

    findMaxSubArray(A, low, middle, &low_max, &low_left, &low_right);
    findMaxSubArray(A, middle+1, high, &high_max, &high_left, &high_right);
    findMaxCrossSubArray(A, low, middle, high, &cross_max, &cross_left, &cross_right);

    if(low_max>=high_max && low_max>=cross_max){
        *max = low_max;
        *left = low_left;
        *right = low_right;
    }else if(high_max>=low_max && high_max>=cross_max){
        *max = high_max;
        *left = high_left;
        *right = high_right;
    } else{
        *max = cross_max;
        *left = cross_left;
        *right = cross_right;
    }
}


