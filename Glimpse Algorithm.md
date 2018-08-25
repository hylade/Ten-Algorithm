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

