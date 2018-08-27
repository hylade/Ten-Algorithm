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



### KMP 算法

对于给定文本串 text 和模式串 pattern ，从文本串 text 中找出模式串 pattern 第一次出现的位置

记文本串长度为 N ，模式串长度为 M ，则 BF算法的时间复杂度为 O(MN) ,空间复杂度为 O(1)

KMP 算法是对于 BF 算法的改进，是一种线性时间复杂度的字符串匹配算法，其时间复杂度为 O(M+N)  ，空间复杂度为 O(M)

```C++
// 查找 s 中首次出现 p 的位置
int BruteForceSearch(const char* s, const char* p)
{
    int i = 0; // 当前匹配到的原始串位置
    int j = 0; // 模式串的匹配位置
    int size = strlen(s);
    int psize = strlen(p);
    
    while ((i < size) && (j < psize))
    {
        if (s[i+j] == p[j]) // 若匹配，则模式串匹配位置后移
        {
            j++;
        }
        else // 不匹配，则比对下一个位置，模式串回溯到首位
        {
            i++;
            j = 0;
        }
    }
    if (j >= psize) return 1;
    else return -1;
}
```



#### 分析 BF 和 KMP 的区别

假设当前文本串 text 匹配到 i 的位置，模式串 pattern 串匹配到 j 位置

BF 算法中，如果当前字符匹配成功，即 text[i+j] == pattern[j] ，令 i++ ， j++ ，继续匹配下一个字符；若匹配失败，即 text[i+j] != text[j] 时，令 i++ ，j = 0 ，即每次匹配失败的情况下，模式串 pattern 相当于文本串 text 向右移动了一位

在 BF 中，为什么模式串的索引需要回溯呢？因为模式串中可能存在重复字符，若模式串中的字符两两不相等，此时只需要编写线性时间代码即可

在 KMP 中的字符串比较机制，即当字符出现不匹配时，将 pattern 串向右移动最少 1 位，最多 j-1 位，保证头串与尾串相同，再进行字符比较；即对于模式串的位置 j ，考察 Pattern(j-1) = p0p1... p(j-2)p(j-1) ，查找字符串 Pattern(j-1) 的最大相等 k 前缀和 k 后缀

此时计算 next[j] 时，考察的字符串是模式串前 j-1 个字符，与 pattern[j] 字符无关

即查找满足条件的最大的 k ，使 p0p1... p(k-2)p(k-1) = p(j-k)p(j-k+1)... p(j-2)p(j-1)



#### next 的递推关系

对于模式串的位置 j ，若有 next[j] = k ，即 p0p1... p(k-2)p(k-1) = p(j-k)p(j-k+1)... p(j-2)p(j-1) 则对于模式串位置 j+1 ，考察 pj ：若 p[k] == p[j] ，则 next[j+1] = next[j] + 1 ；若 p[k] != p[j] 时，记 h = next[k] ；若 p[h] == p[j] ，则 next[j+1] = h + 1 ，否则重复此过程

next[k] 表示 k 位置前 k 个字符中，首尾相同的字符串长度为 h ，由于 next[j] = next[k] 相同，故 j 位置的前 k 个字符中，首尾也存在 h 个字符相同，故若 p[h] == p[j] ，那么 next[j+1] = h + 1 ，长度能够增加 1  

```C++
// 1
void CalcNext(char* p, int next[])
{
    int nLen = strlen(p); // 模板字符串长度
    next[0] = 0; // 模板字符串的第一个字符的最大前后缀长度为 0
    int k = 0; // 最大前后缀长度
    for (j = 1,; j <= nLen; j++) // j 为模板字符串下标
    {
		while (k > 0 && p[j] != p[k]) k = next[k-1]; // 递归求出 p[0]...p[j] 的最大前后缀长度
        if (p[j] == p[k]) k++; // 若想等，最大相同的前后缀长度 +1
        next[j] = k;
    }
}
```



```C++
void get_next()
{
    int i = 0, j = -1;
    next[0] = -1;
    while (i < len)
    {
        if (j == -1 || str[i] == str[j])
        {
            i++, j++;
            if (str[i] != str[j]) next[i] = j;
            else next[i] = next[j];
        }
        else j = next[j];
    }
}
```



#### KMP 代码

```C++
// 匹配的时间复杂度为 O(n) ，计算 next 的时间复杂度为 O(m) ，故整体时间复杂度为 O(m+n)
int KMP(const char T[], const char P[], int next[])
{
    int n, m;
    int i, q = 0;
    n = strlen(T);
    m = strlen(P);
    CalcNext(P, next);
    
    for (int i = 0; i < n; i++)
    {
        while (q > 0 && P[q] != T[i]) q = next[q-1];
        if (P[q] == T[i]) q++;
        if (q == m) printf("Yes\n");
    }
}
```



#### 进一步分析 next

文本串若匹配到 i ，模式串匹配到 j ，此刻，若 text[i] != pattern[j] 即失配情况：若 next[j] == k ，说明模式串应该从 j 滑动到 k 位置；但若此时 pattern[j] == pattern[k] ，那么由于 text[i] != pattern[j] ，所以 text[i] != pattern[k] ，即 i 和 k 也不能匹配，所以应该继续滑动到 next[k] 。即在原始的 next 数组中，若 next[j] = k 并且 pattern[j] == pattern[k] ，next[j] 可以直接等于 next[k]



#### KMP 应用： PowerString 问题

给定一个长度为 n 的字符串 S ，如果存在一个字符串 T ，重复若干次 T 能够得到 S ，那么 S 叫做周期串， T 叫做 S 的一个周期

如 字符串 abababab 是周期串， abab 和 ab 都是它的周期，其中 ab 是它的最小周期；设计一个算法，计算 S 的最小周期，如果 S 不存在周期，则返回空串

计算 S 的 next 数组，记 k = next[len-1] ， p = len - k ；若 len 能整除 p ，则 p 就是最小周期长度，前 p 个字符就是最小周期