### 寻找和为定值的两个数

输入一个数组 A[0 ... N-1] 和一个数字 Sum ，在数组中查找两个数 Ai 和 Aj ，使其和等于 Sum

#### 暴力

从数组中任意选取两个数 x ， y ，判定它们的和是否为输入的数字 Sum ，时间复杂度为 O(n^2) ，空间复杂度为 O(1)



#### 暴力改进——两头搜索

如果数组是无序的，先进行排序 O(nlogn) ，然后用两个指针 i 和 j ，各自指向数组的首尾两端，令 i = 0 ， j = n - 1 ，然后 i++ 和 j-- ，逐次判断 a[i] + a[j] 是否等于 Sum

若 a[i] + a[j] > Sum ，则 i 不变， j--

若 a[i] + a[j] < Sum ，则 i ++， j 不变

若 a[i] + a[j] = Sum ，如果只要求输出一个结果，则退出；否则，输出结果后 i++ ， j--

此时时间复杂度为 O(nlogn + n) = O(nlogn)

```C++
void TwoSum(int data[], unsigned int length, int sum)
{
    int begin = 0;
    int end = length - 1;
    while (begin < end)
    {
        long currSum = data[begin] + data[end];
        
        if (currSum == sum)
        {
            printf("%d %d", data[begin], data[end]);
            break;
        }
        else
        {
            if (currSum < sum) begin++;
            else end--;
        }
    }
}
```



### Hash

#### Hash 结构

首先针对数组开辟一个足够大的空间用于后续存储数据。以数组元素值 x 为自变量，通过某函数 f ，将其映射为某个整数值 index ，将该整数值 x 存储在 H[index] 处，这样，在以后查找元素 a 是否存在时，只需要计算 f(a) 得到数值 y ，从而只需查看 H[y] 处是否存在 a 即可

Hash 表是通过足够大的存储空间保证在 O(1) 时间内找到某元素；一般认为空间复杂度为 O(n)



#### Hash 函数

Hash 函数在 Hash 结构设计中处于核心地位，一个好的 Hash 函数，能够使数据变得杂乱，避免 Hash 冲突

##### djb2

使用异或的方式： hash(i) = hash(i - 1) * 33 ^ str[i]; （此处 33 被称为魔数，比其他数字效果好，但仍未能解释）

```C++
unsigned long
hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++) // 表示取 str 指针指向的数，然后 +1
    {
        hash = ((hash << 5) + hash) + c; // << 表示放大 2^n 倍，故此处一共放大 33倍
    }
    return hash;
}
```



sdbm

```C++
static unsigned long
sdbm(unsigned char *str)
{
    unsigned long hash = 0;
    int c;
    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;
    
    return hash;
}
```

