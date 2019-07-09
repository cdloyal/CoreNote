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

    /**
     * 主方法求解递归式
     *
     *  T(n) = aT(n/b) + f(n)   //a>=1,b>1
     *
     *  T(n)的渐进界：
     *      如果f(n)=theta(n^LOGb(a)),则T(n)=theta(n^LOGb(a) * lg(n))
     *      如果存在一个常数c，f(n)=O(n^LOGb(a-c))，则T(n)=(n^LOGb(a))
     *      如果存在一个常数c，f(n)=OHM(n^LOGb(a+c))，且对于某个常数d<1和所有足够的n有af(n/b)<=df(n)，T(n)=f(n)
     *
     *  T(n)=9T(n/3)+n
     *      n^LOGb(a)=n^log3(9)=n^2;  n^(2-1)=n=f(n); T(n)=n^2
     *
     *  T(n)=T(2n/3)+1
     *      n^LOGb(a)=nlog2/3(1)=n^0=1=f(n);    T(n)=n^0*lgn=lgn
     *
     *  T(n)=3T(n/4)+nlgn
     *      n^LOGb(a)=n^0.793;  f(n)=OHM(n^0.793); 且对于某个常数d<1和所有足够的n有af(n/b)<=df(n),
     *      af(n/b)=3(n/4)lg(n/4) <= df(n)=dnlgn; 当d=3/4,定理3成立；T(n)=f(n)=nlgn
     *
     * T(n)=2T(n/2)+nlgn
     *      n^LOGb(a)=n;  f(n)=OHM(n);
     *      af(n/b)=2(n/2)lg(n/2)=nlg(n/2) ? df(n)=dnlgn;
     *
     * */

    /**
     * 矩阵乘法的Strassen算法
     *
     * 矩阵相乘
     *  设A为m*p的矩阵，设B为p*n的矩阵，记C=AB
     *  Cij = (AB)ij = (k=1 -> p)(Aik * Bkj) = Ai1*B1j + Ai2*B2j +...+ Aip*Bpj
     *
     *  矩阵A的列数等于矩阵B的行数
     *  矩阵C的第m行第n列元素等于矩阵A的第m行元素与矩阵B的第n列元素对应元素乘积
     *  矩阵C的行数等于矩阵A的行数，矩阵C的列数等于矩阵B的列数
     *
     *
     *  A(n,n)*B(n,n)矩阵相乘
     *
     *      输入：A(n,n)、B(n,n)
     *      输出：C(n,n)
     *      函数定义：Matrix matrixMulti(Matrix A,Matrix B)
     *
     *      暴力求解:Cij = (AB)ij = (k=1 -> n)(Aik * Bkj) = Ai1*B1j + Ai2*B2j +...+ Aip*Bpj
     *               求解一次运行n次，共求n*n个元素，效率n^3
     *
     *      递归求解:
     *
     *          分解：求C(n,n),行数等于列数，子问题规模也要行数等于列数，分解成4个(n/2),(n/2)的数组
     *                A、B也是分解成4个(n/2),(n/2)的数组,这里用来一些矩阵定理
     *
     *                a11 a12       b11 b12       c11 c12
     *                a21 a22       b21 b22       c21 c22
     *
     *                c11 = a11*b11 + a12*b21
     *                c12 = a11*b12 + a12*b22
     *                c21 = a21*b11 + a22*b22
     *                c22 = a21*b12 + a22*b22
     *
     *
     *                简单来说，将输入输出分解
     *                由上面的定理，
     *                输出分解:C(n,n) -> C(0-n/2,0-n/2)、C(n/2-n,0-n/2)、C(0-n/2,n/2-n)、C(n/2-n,n/2-n)
     *                                   c11             c12             c11             c12
     *
     *          求解：Matrix matrixMulti(Matrix A,Matrix B)   ==> 两个矩阵相乘等于一个新的矩阵
     *                输入:A(n,n)、B(n,n)，当n=1时，此时输出C(1,1)=A(1,1)*B(1,1)
     *
     *          归并：c11 c12 c11 c12 -> C(n,n)
     *                  c11 = a11*b11 + a12*b21   ==>  矩阵c11=矩阵a11和矩阵b11相乘，再加上矩阵a12和矩阵b21相乘,这里是矩阵相加，不是普通加法
     *                                            ==>  c11=matrixMulti(a11,b11)+matrixMulti(a12,b21)
     *
     * */
}


