#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

inline void write(long long w) {
    if (w == 0) {
        putchar('0');
        return;
    }
    char my_out[33];
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
    int n = 1000000;
    write(n);
    putchar('\n');
    for (int i = 1; i <= n; i++) {
        write((long long)rand() * rand() % 2000000 + 1);
        putchar(' ');
    }
    putchar('\n');
    long long m = (long long)rand() * rand() % 20000;
    for (int i = 1; i <= n; i++) {
        m = rand() % (m + 1) + 1;
        write(m);
        putchar(' ');
    }
    putchar('\n');
    int T = 200000;
    long long p, q;
    write(T);
    putchar('\n');
    while(T--) {
        p = (long long)rand() * rand() % 2000;
        q = (((long long)rand()  * rand() % 2000) + p) % 2000;
        write(p);putchar(' ');
        write(q);
        putchar('\n');
    }
    return 0;
}