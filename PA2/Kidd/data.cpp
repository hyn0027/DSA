#include <cstdio>
#include <iostream>
#include <cstring>
#include <ctime>

const int maxm = 200000 + 5;

inline int read() {
    int ret = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        ret = (ret << 1) + (ret << 3) + c - '0', c = getchar();
    return ret;
}

inline void write(long long w) {
    if (w == 0) {
        putchar('0');
        return;
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

int main() {
    srand(time(0));
    /*
    此处n m可调
    */
    int n = (long long)rand() * (long long)rand() * (long long)rand() % ((long long)((long long)1 << 31) - 1);
    int m = 5;
    int a, b;
    write(n);
    putchar('\n');
    write(m);
    putchar('\n');
    while (m--) {
        if (rand() % 2)
            putchar('H');
        else 
            putchar('Q');
        putchar(' ');
        a = (long long)rand() * rand() % n + 1;
        b = (long long)rand() * rand() % n + 1;
        if (a > b)
            std::swap(a, b);
        write(a);
        putchar(' ');
        write(b);
        putchar('\n');
    }
    return 0;
}