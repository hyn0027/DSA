#include <cstdio>
#include <iostream>
#include <cstring>
#include <ctime>

/*
参数在这里改常数值quq！
在生成的数据中：
n 约等于 average_n_base * average_child_num
m 等于 maxm
每个有孩子的节点平均有average_child_num个孩子
生成的指定某个节点的路径长度平均为average_tree_path_length
average_tree_path_find_child_idx一般设置成略大于average_child_num就ok 也可以随便调调看quq
*/
const int average_n_base = 20;
const int maxm = 300;
const int average_child_num = 2;
const int average_tree_path_length = 2;
const int average_tree_path_find_child_idx = 3;


inline int read() {
    int ret = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        ret = (ret << 1) + (ret << 3) + c - '0', c = getchar();
    return ret;
}

inline void write(int w) {
    if (w == 0) {
        putchar('0');
        return;
    }
    if (w < 0) {
        putchar('-');
        w = -w;
    }
    char my_out[20];
    unsigned short pt = 0;
    while (w) {
        my_out[pt++] = w % 10 + '0';
        w /= 10;
    }
    for (int i = pt - 1; i >= 0; i--) 
        putchar(my_out[i]);
}

void tree(int x = 1) {
    int len = rand() % (average_tree_path_length * 2) + 1;
    write(len);
    putchar(' ');
    if (x == 0) {
        write(0);
        putchar(' ');
        len--;
    }
    while(len--) {
        write(rand() % (average_tree_path_find_child_idx * 2));
        putchar(' ');
    }
    putchar('\n');
}

int len[10000000 + 5];

int main() {
    srand(time(0));
    int n = average_n_base;
    int m = maxm;
    int mk = 2, sz = 1;
    for (int i = 1; i <= n; i++) {
        len[i] = rand() % (average_child_num * 2);
        if (i < 20) len[i] = rand() % 4;
        if (i == 1) len[i] = 6;
        sz += len[i];
    }
    n = sz;
    write(n);
    putchar(' ');
    write(m);
    putchar('\n');
    for (int i = 1; i <= n; i++) {
        write(len[i]);
        putchar(' ');
        while (len[i]--) {
            write(mk++);
            putchar(' ');
        }
        putchar('\n');
    }
    while (m--) {
        int op = rand() % 6;
        if (op == 0 || op >= 3) {
            putchar('0');
            putchar('\n');
            tree(0);
            tree();
            putchar('0');
            putchar('\n');
        }
        if (op == 1) {
            putchar('1');
            putchar('\n');
            tree();
        }
        if (op == 2) {
            putchar('2');
            putchar('\n');
            tree();
        }
    }
    return 0;
}