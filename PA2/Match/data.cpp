#include <cstdio>
#include <iostream>
#include <cstring>
#include <ctime>

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

int main() {
    srand(time(0));
    int n = 400;
    int m = 400, op;
    write(n);
    putchar(' ');
    write(m);
    putchar('\n');

    for (int i = 0; i < n; i++)
        putchar(rand() % 2 + 'a');
    putchar('\n');
    while (m--) {
        op = rand() % 6;
        if (n == 0)  op = 0;
        if (op > 3) op = 0;
        if (op == 0) {
            putchar('1');
            putchar(' ');
            op = rand() % (n + 1);
            write(op);
            putchar(' ');
            putchar(rand() % 2 + 'a');
            n++;
            putchar('\n');
        }
        else if (op == 1) {
            putchar('2');
            putchar(' ');
            op = rand() % (n);
            n--;
            write(op);
            putchar('\n');
        }
        else if(op == 2) {
            putchar('3');
            putchar(' ');
            int l = rand() % n, r = rand() % n;
            if(l > r)   std::swap(l, r);
            write(l);
            putchar(' ');
            write(r);
            putchar('\n');
        }
        else if(op == 3) {
            putchar('4');
            putchar(' ');
            int l = rand() % n, r = rand() % n;
            if(l > r)   std::swap(l, r);
            write(l);
            putchar(' ');
            write(r);
            putchar(' ');
            int len = rand() % (n - r) + 1;
            write(len);
            putchar('\n');
        }

    }
    return 0;
}