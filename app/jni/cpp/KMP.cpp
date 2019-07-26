/**
 * 作者：chenda
 * 时间：2019/7/24:17:08
 * 邮箱：
 * 说明：
 */

/**
 * https://blog.csdn.net/x__1998/article/details/79951598
 *
 * char:    a       b       a       b       a       b       c       a
 * index:   0       1       2       3       4       5       6       7
 * 前缀：           a       ab     aba     abab    ababa   ababab   ababab
 * 后缀：           b       ba     bab     baba    babab   bababc   babaca
 * pmt:     0      0        1      2        3       4       0       1
 * next:    -1     0        0      1        2       3       4       0
 *
 * char:    a       a       a       b
 * index:   0       1       2       3
 * pmt:     0       1       2       0
 * next:    -1      0       1       2
 *
 * pmt[i]:字符串[0..i]的前缀集合与后缀集合的交集中最长元素的长度
 *        后缀{[i],[i-1,i],..,[1..i]}
 *        前缀{[0],[0,1],..,[0..i-1]}
 *
 *
 * 这意味着：
 *                              i
 *      要匹配的字符串A[]：ababababca
 *               模式B[]：abababca
 *                             j
 * 当字符串A的第i位与字符串的第j位不匹配时，字符串A[i-pmt[j-1]..i-1](即i的前pmt[j-1])
 * 与字符串B[0..pmt[j-1]-1]位相同，那么接下来要匹配的时A[i]与B[pmt[j-1]]
 *
 * 为了编程方便，我们将pmt数组向又偏移,那么接下来要匹配的时A[i]与B[next[j]]，
 * next[j]==-1，continue?A[i+1]与B[0]
 *
 * 那么next数组代表什么？next[j]:字符串A和字符串B匹配，假设A[i]与B[j]不匹配，
 * 字符串A[i-pmt[j]..i-1](即i的前pmt[j])与字符串B[0..pmt[j]-1]位相同,那么接下来要匹配的时A[i]与B[next[j]]，
 * next[j]:字符串[0..j-1]的前缀集合与后缀集合的交集中最长元素的长度
 *
 * 计算next数组
 * pmt[i]:字符串[0..i]的前缀集合与后缀集合的交集中最长元素的长度
 *        后缀{[i],[i-1,i],..,[1..i]}
 *        前缀{[0],[0,1],..,[0..i-1]}
 *
 * */