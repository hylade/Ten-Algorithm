### 字符串循环左移

给定一个字符串 S[0... N-1]  ，要求把 S 的前 k 个字符移动到 S 的尾部，如把字符串 abcdef 前面的 2 个字符 a 和 b 移动到字符串的尾部，得到新的字符串 cdefab ，即字符串循环左移 k（等价于循环右移 n-k）

算法要求：时间复杂度为 O(n) ，空间复杂度为 O(1)

#### 暴力

每次循环左移一位，调用 k 次即可；

时间复杂度为 O(kn) ，空间复杂度为 O(1)

#### 三次拷贝

将前 k 位先保存 S[0 ... k] = T[0... k]

将 k+1 至 N-1 位前移 S[k+1 ...N-1] = S[0... N-k-1]

将后续的添加进来 T[0... k] = S[N-k... N-1]

时间复杂度为 O(n) ，空间复杂度为 O(k)

#### 逆序

(X'Y')' = YX

如字符串 abcdef ， X 为 ab ， X' 为 ba ， Y 为 cdef ， Y' 为 fedc

故 (X'Y')' = (bafedc)' = cdefab

此时时间复杂度为 O(n) ，空间复杂度为 O(1)

```C++
void ReverseString(char* s, int from, int to)
{
    while (from < to)
    {
        char t = s[from];
        s[from++] = s[to];
        s[to--] = t;
    }
}

void LeftRotateString(char* s, int n, int m)
{
    m %= n; // 取余，对于超过 n 的循环，取余数循环
    ReverseString(s, 0, m-1); // 先进行前 m 位的逆序
    ReverseString(s, m, n-1); // 再进行 n-m 为的逆序
    ReverseString(s, 0, n-1); // 再整体进行逆序
}
```



### 字符串的全排列

给定字符串 S[0... N-1] ，枚举 A 的全排列

```C++
// 递归算法 O(n!)
char str[] = '1234';
int size = sizeof(str) / sizeof(char);

void Permutation(int from, int to)
{
    if (from == to)
    {
        for (int i = 0; i <= to; i++)
        {
            cout << str[i];
        }
        cout << endl;
        return ;
    }
    for (int i = from; i <= to; i++)
    {
        swap(str[i], str[from]);
        Permutation(from+1, to);
        swap(str[i], str[from]);
    }
}

int _tmain()
{
    Permutation(0, size-2);
    return 0;
}
```



#### 若字符有重复

此时需要递归算法中去除重复字符的情况

以 1223 为例： 1-223 ； 2-123 ； 3-221

带重复字符的全排列就是每个字符分别与它后面非重复出现的字符交换，即要求第 i 个字符与第 j 个字符交换时，要求 [i,j) 中没有与第 j 个字符相等的字符

```C++
// 递归算法
char str[] = '1234';
int size = sizeof(str) / sizeof(char);

bool IsSwap(int from, int to)
{
    bool bCan = true;
    for (int i = from; i < to; i++)
    {
        if (str[to] == str[i])
        {
            bCan = false;
            break;
        }
    }
    return bCan;
}

void Permutation(int from, int to)
{
    if (from == to)
    {
        for (int i = 0; i <= to; i++)
        {
            cout << str[i];
        }
        cout << endl;
        return ;
    }
    for (int i = from; i <= to; i++)
    {
        if (!IsSwap(from, i))
            continue;
        swap(str[i], str[from]);
        Permutation(from+1, to);
        swap(str[i], str[from]);
    }
}

int _tmain()
{
    Permutation(0, size-2);
    return 0;
}
```



### 全排列的非递归算法

起点：字典序最小的排列，如 12345

终点：字典序最大的排列，如 54321

过程：从当前排列生成字典序刚好比它大的下一个排列



21543 的下一个排列过程的思考过程

逐位考察哪个能增大：若一个数的右边有比它大的数存在，它就能增大，故最后一个能增大的数是 1

1 应该增大到多少？增大到它右边比它大的数中最小的数，即 3

应该变为 23xxx ，显然 xxx 应该有小到大排列，故为 145 ，故下一个排列为 23145



算法实现便是查找字符串中最后一个升序的位置 i ，即 S[k] > S[k+1] ，S[i] < S[i+1]

查找 S[i+1... N-1] 中比 Ai 大的最小值 Sj ，交换 Si 和 Sj ，此时 S[i+1... N-1] 必定为降序，翻转该部分即可得到下一个序列

```C++
void Swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

// 反转区间
void Reverse(char *a, char *b)
{
    while (a < b)
    {
        Swap(a++, b--);
    }
}

bool Next_permutation(char a[])
{
    char *pEnd = a + strlen(a);
    if (a == pEnd) return false; // 若只有一个字符时
    char *p, *q, *pFind;
    pEnd--;
    p = pEnd;
    while (p != a)
    {
        q = p;
        --p;
        if (*p < *q) // 由于 p q 只相差 1 位，即找升序的相邻 2 数，前一个是需要替换的数
        {
            // 从后面找比替换点大的第一个数
            pFind = pEnd;
            while (*pFind <= *p)
                --pFind;
            // 交换
            Swap(pFind, p);
            // 反转
            Reverse(q, pEnd);
            return true;
        }
    }
 	Reverse(p, pEnd); // 若不存在下一个队列，则全部反转后返回 true
    return false;
}
```

