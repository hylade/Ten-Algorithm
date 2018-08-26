### 求解最大子序列和

#### 暴力

```c++
// O(n^3)
int MaxSubArray (int *A, int n)
{
    int maxSum = A[0];
    int currSum;
    for (int i = 0; i < n; i++)
    {
        for(int j = i; j < n; j++)
        {
            currSum = 0;
            for (int k = i; k <= j; k++)
            {
                currSum += A[k];
            }
            if (currSum > maxSum)
            {
                maxSum = currSum;
            }
        }
    }
    return maxSum;
}
```



#### 分治法

1. 将数组从中间分开，那么最大子数组要么完全在左半边数组，要么完全在右半边数组，要么跨立在分界点上
2. 完全在左数组、右数组递归解决
3. 跨立在分界点上：实际上是左数组的最大后缀和右数组的最大前缀的和。因此，从分界点向前扫，向后扫即可

```c++
// O(nlogn)
double MaxAddSub(int from, int to)
{
    if (to == from)
    {
        return a[from];
    }
    
    int middle = (from + to) / 2;
    double m1 = MaxAddSub(from, middle);
    double m2 = MaxAddSub(middle+1, to);
    
    int i, left = a[middle], now = a[middle];
    for (i = middle-1; i>= from; --i)
    {
        now += a[i];
        left = max(now, left);
    }
    
    int right = a[middle + 1];
    now = a[middle + 1];
    for (i = middle; i <= to; ++i)
    {
        now += a[i];
        right = max(now, right);
    }
    
    double m3 = right + left;
    return max(max(m1, m2), m3);
}
```



#### 分析法（逻辑推理）

设前缀和 p[i] = a[0] + a[1] + ... + a[i]

那么子序列和 s[i,j] = p[j] - p[i-1]

算法过程：

1. 前 i 前缀 p[i] : 遍历 i ，p[i] = p[i-1] + a[i]
2. 计算 p[i] - p[j] : 遍历 i ，求最小值 m （m 的初值取 0 （p[-1] = 0），然后遍历 p[0...i-1]），更新 m ；此时 p[i] - m 即为以 a[i] 结尾的数组中最大的子数组



进一步分析：

记 S[i] 为以 A[i] 结尾的数组中和最大的子数组，则 S[i+1] = max(S[i] + A[i+1], A[i+1]) ；且 S[0] = A[0] ；遍历 i 即可；

动态规划思想，时间复杂度 O(n)

```C++
// O(n) 
int result = a[0];
int sum = a[0];
for (int i = 1; i <= length[a]; ++i)
{
    // 判断 max(S[i] + A[i+1], A[i+1]) ，等同于判断 sum 是否大于 0
    if (sum > 0) sum += a[i];
    else sum = a[i];
    
    if (sum > result) result = sum;
}
return result;
```



### 查找旋转数组的最小值

假定一个排序数组以某个位置元素为支点做旋转，如原数组： 0 1 2 4 5  6 7 旋转得到 4 5 6 7 0 1 2 。请找出旋转后数组的最小值。假定数组中没有重复的数字

#### 分析

旋转之后的数组实际上可以划分为两个有序的子数组：前面子数组的大小都大于后面子数组中的元素；同时可以注意到最小的元素就是两个子数组的分界线

#### 思路

用两个指针 low 和 high 分别指向数组的第一个元素和最后一个元素。如果是正常的排序数组（元素间不重复），第一个元素肯定小于最后一个元素

此时计算中间位置 mid = (low + high) / 2

若 A[mid] > A[low] ，则 A[low, low+1, ..., mid] 是递增序列，最小元素应该位于子数组 A[mid+1, mid+2,..., high] 中。因此，赋值 low = mid + 1

若 A[mid] < A[low] ，则 说明 A[low, low+1, ..., mid] 不是 递增序列，即中间元素在该子数组中，赋值 high = mid

==同样，若对 A[mid] 和 A[high] 作比较，也能得出相似结论==

```C++
int FindMin(int* num, int size)
{
    int low = 0;
    int high = size - 1;
    int mid;
    while (low < high)
    {
        mid = (low + high) / 2;
        if (num[mid] < num[high])
        {
            high = mid;
        }
        else if (num[mid] > num[high])
        {
            low = mid + 1;
        }
    }
    return num[low];
}
```



### 零子数组

求对于长度为 N 的数组 A ，求子数组的和接近 0 的子数组，要求时间复杂度为 O(logn)

#### 算法流程

申请同样长度的空间 sum[0, ... N-1] ，定义 sum[i] 为 A 的前 i 项和（需要定义 sum[-1] = 0）

所以 $\sum\limits_{k=i}^j=sum(j)-sum(i-1)$ ，即 sum[j] - sum[i-1] 为 i 项至 j 项的和

对 sum[i] 进行排序，然后计算 sum相邻元素的差（相邻元素的差才能保证小），最小值记为 min1

记 sum[i] 的绝对值的最小值为 min2 ，即 A 中前 k 个元素的和的绝对值最小值

min1 和 min2 中的更小者，即为所求



#### 说明

sum 本身的计算和相邻元素的差的计算，时间复杂度都是 O(n) , 但是 sum 的排序是 O(logn) ，因此，总的时间复杂度是 O(logn)



### LCS 的定义

最长公共子序列即 Longest Common Subsequence， LCS 

一个序列 S 任意删除若干个字符得到新序列 T ，则 T 叫做 S 的子序列

两个序列 X 和 Y 的公共子序列中，长度最长的那个，定义为 X 和 Y 的最长公共子序列

例如 13455 与 245576 的最长公共子序列为 455

同时，注意区别最长公共子串，最长公共子串是要求连续的



#### 暴力

假定字符串 X ， Y 的长度分别为 m 和 n

X 的一个字符列即下标序列 (1, 2, ..., m) 的严格递增子序列，因此 X 共有 $2^m$ 个不同子序列；同理， Y 有 $2^n$ 个不同子序列，从而穷搜需要指数时间 O($2^m\cdot2^n$)

对于 X 的每一个子序列，检查它是否也是 Y 的子序列，从而确定它是否为 X 和 Y 的公共子序列，并且在检查过程中选出最长的公共子序列。由于时间复杂度过大，不可取





#### LCS 记号

若记 Xi 若 X 序列的前 i 个字符，即 Xi = <x1, ..., xi>

若记 Yj 若 Y 序列的前 j 个字符，即 Yi = <y1, ..., yj>

并且记 LCS(X, Y) 为字符串 X 和 Y 的最长公共子序列集，并且其中最长的序列记为 Z = <z1, ..., zk>



若 xm = yn 即最后一个字符相同，那么 Xm 和 Yn 的最长公共子序列 Zk 的最后一个字符必定为 xm（yn）

那么 LCS(Xm, Yn) = LCS(Xm-1, Yn-1) + xm

若记 LCS(Xm, Yn) = W + xm ，那么 W 是 Xm-1 的子序列，同时也是 Yn-1 的子序列，因此 W 是 Xm-1 和 Yn-1 的公共子序列



若 xm != yn ，那么 LCS(Xm, Yn) = max(LCS(Xm-1, Yn), LCS(Xm, Yn-1))

$LCS(X_m,Y_n)=\begin{cases}LCS(X_{m-1},Y_{n-1})+x_m,&当x_m=y_n\\ \max\{LCS(X_{m-1},Y_n),LCS(X_m,Y_{n-1}) \},&当 x_m \not= y_n  \end{cases}$ 



利用 C[m, n] 来记录 LCS 长度，用 B[m, n] 记录生成方式

```C++
Procedure LCS_LENGTH(X, Y)
{
    m = length(X);
    n = length(Y);
    for (int i = 1; i <= m; i++) c[i][0] = 0;
    for (int j = 1; j <= n; j++) c[0][j] = 0;
    
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (x[i] = Y[j])
            {
                [i][j] = c[i-1][j-1] + 1;
                b[i][j] = 1;
            }
            else if (c[i-1][j] >= c[i][j-1])
            {
                c[i][j] = c[i-1][j];
                b[i][j] = 2;
            }
            else
            {
                c[i][j] = c[i][j-1];
            }
        }
    }
    return (c, b);
}

Procedure LCS(b, X, m, n)
{
    if (m == n) return;
    if (b[i][j] == 1)
    {
        LCS(b, X, m-1, n-1);
        printf("%d", x[m]);
    }
    else if (b[i][j] == 2)
    {
        LCS(b, X, m-1, n);
    }
    else
    {
        LCS(b, X, m, n-1);
    }
}
```

#### 进一步思考

方向数组 b 完全可用省略，由于元素 c[i, j] 是由 c[i-1, j-1] ， c[i, j-1] 和 c[i-1, j] 三者之一确定的，因此可以在计算中，临时判断是由那个元素确定



### LCS 的应用：最长递增子序列 LIS

给定一个长度为 N 的数组，找出一个最长的单调递增子序列，如 5 6 7 8 1 2 8 ，其最长单增子序列为 5 6 7 8 ，长度为 4



将原序列排序后为递增的，这样就保证了两序列的最长公共子序列的递增序列，所以，要求最长递增序列，便是原数组和排序后数组的最长公共子序列即可



### LCS 与字符串编辑距离

字符串编辑距离是指两个字符串之间，由一个转化成另一个所需的最少编辑次数，编辑方式包括

1. 将一个字符串替换成另一个字符
2. 插入一个字符
3. 删除一个字符

```C++
/*
设状态 f[i][j] 表示 s1 串前 i 个字符和 s2 串字符相等时 s1 串最小字符操作次数
初始状态 f[i][0] = i ，表示当 s2 为空串时，最少操作次数是将 s1 串字符全部删除
初始状态 f[0][j] = j ，表示当 s1 为空串时，最少操作次数是将 s1 串添加相应 s2 的字符

故当 s1[i-1] == s2[j-1] 时， f[i][j] = f[i-1][j-1]
当 s1[i-1] != s2[j-1] 时， f[i][j] = min(f[i-1][j-1], f[i][j-1], f[i-1]j) + 1

此时 f[i-1][j-1] + 1 表示将 s1[i] 变为 s2[j]
f[i][j-1] + 1 表示在 s1 后插入 s2[j]
f[i-1][j] + 1 表示删除 s1[i]
*/

int EditDistance(char *pSource, char *pTarget)
{
    int srclength = strlength(pSource);
    int targetlength = strlength(pTarget);
    for (int i = 1; j <= srclength; i++)
    {
        dp[i][0] = i;
    }
    for (int j = 1; j <= targetlength; j++)
    {
        dp[0][j] = j;
    }
    for (int i = 1; i <= srclength; i++)
    {
        for (int j = 1; j <= targetlength; j++)
        {
            if (pSource[i-1] == pTarget[j-1])
            {
                dp[i][j] = dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i][j-1], dp[i-1][j]));
            }
        }
    }
    return dp[srclength][targetlength];
}
```



### 最长公共子串

如要计算两个已知字符串的最长公共子串，如何求解？

借鉴 LCS 的思想，考察 A 的 i 前缀和 B 的 j 前缀的最长公共子串 S(i, j)

若 A[i] == B[j] ，则 S(i, j) = S(i-1, j-1) + 1

```C++
int LCS_Length(string &str1, string &str2)
{
    int biggest = 0;
    if (str1 == "" || str2 == "")
    {
        return 0;
    }
    for (int i = 1; i <= str1.length(); i++) dp[i][0] = 0;
    for (int i = 1; i <= str2.length(); i++) dp[0][i] = 0;
    for (int i = 1; i <= str1.length(); i++)
    {
        for (int j = 1; j <= str2.length(); j++)
        {
            if (str1[i-1] == str2[j-1]) 
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            	if (dp[i][j] > biggest) biggest = dp[i][j];
            }
            else dp[i][j] = 0;
        }
    }
    return biggest;
}
```

