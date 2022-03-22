# 1. 使用算法

令```p```表示输入的串

使用kmp算法的```next```数组实现动态规划。

首先构造好```next```数组。对于```p```中```[0, i]```的位置，如果```p```中```[0, j]```的位置与```[i - j + 1, i]```完全相同，且```j < i```，此处的```j```是满足条件的最大的```j```，则```next[i + 1]```存储的值就是```j +1```。

令```ans[i]```表示```p```中以```i - 1```结尾的子串中与多少是```p```的前缀。特别地，```ans[0] = 0```。则根据```next```数组的性质，容易得到状态转移方程：```ans[i] = 1 + ans[nex[i]]```。

于是对```ans[i]```求和，得到结果。

# 2. 问题处理

一开始由于没有开long long结果错误，修改后正确

# 3. 复杂度

## 3.1 时间复杂度

令$n$为串的长度

读入的复杂度为$O(n)$

next数组的构造的时间复杂度为$O(n)$，此处分析由讲义中使用$2\cdot i - j$的均摊分析可得

计算答案的时间复杂度为$O(n)$

故总时间复杂度为$O(n)$

## 3.2 空间复杂度

需要的非$O(1)$空间包括且仅包括：

$O(n)$存储串

$O(n)$存储next数组

$O(n)$存储ans数组

故总空间复杂度为$O(n)$

# 4. 参考资料

无