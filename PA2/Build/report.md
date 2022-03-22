# 1. 使用算法

整体来说，使用了常规的多叉树，记录每个节点的子树size和树高。但对于本题，由于有子树的删除与插入操作，而且题目不保证孩子的数量是否有上限，因此在删除与插入子树时遍历孩子维护树高是不现实的。

题目对于cost给出了一定的限制，考虑使用这一限制控制时间复杂度。具体而言，如果一个节点$f$有孩子$c_1, c_2, ...c_m$，此次我们操作的节点是孩子$c_k$，我们需要一些操作，仅仅访问$c_1,c_2,...,c_k$，而维护$f$的树高。这个时候考虑对每个节点定义一个变量$maxHeightInSelfAndOlderBrothers$，比如对于$c_k$， 它的$maxHeightInSelfAndOlderBrothers$等于$max\{c_i的树高|k \leq i \leq m\}$，因此操作$c_k$时，只需要维护$c_1,c_2,...,c_k$的$maxHeightInSelfAndOlderBrothers$，然后$f$的树高就等于$c_1$的$maxHeightInSelfAndOlderBrothers + 1$，此后再维护$f$及$f$的弟弟的$maxHeightInSelfAndOlderBrothers$，如上，递归向上维护树高和$maxHeightInSelfAndOlderBrothers$。而$size$的维护自然地可以顺次向上递归。如此可以将复杂度控制在cost内。

关于树及孩子的存储，每个节点存储它的左右兄弟指针，它的size，height和maxHeightInSelfAndOlderBrothers，以及它第一个孩子的指针。互为兄弟关系的节点使用链表连成一串。

# 2. 问题处理

在处理链表时插入是，有一部分忘记连接导致错误。修改后正确。

# 3. 复杂度

## 3.1 时间复杂度

输入及建树的时间复杂度为$O(n)$

单次挪动的时间复杂度为$O(cost)$，具体愿意如上所述

单次查询的时间复杂度为$O(d)$，其中$d$为待查询节点的深度。

总时间复杂度为$O(n + cost)$

## 3.2 空间复杂度

由于除了存储树的节点及相关信息之外没有其他非$O(1)$的空间需要，因此总空间复杂度为$O(n)$


# 4. 参考资料

题面的提示
