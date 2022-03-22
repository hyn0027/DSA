#include <iostream>
#include <ctime>
#include <cstdio>
#include <algorithm>
#define sz 64
const int maxn = 50000;
inline void write(int w) {
    if (w == 0) {
        putchar('0');
        putchar('\n');
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
    int n = maxn;
    int k = rand() % n;
    write(n); putchar(' '); write(k); putchar('\n');
    while(n--) {
        for (int i = 0; i < sz; i++)
            putchar((rand() % 10 < 3 ? 1 : 0) + '0');
        putchar('\n');
    }
}