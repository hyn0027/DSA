#include <cstdio>
#include <iostream>
#include <cstring>
#include <ctime>

const int maxm = 200000 + 5;

int main() {
    srand(time(0));
    int len = 50;
    while (len--)
        putchar('0' + rand() % 2);
    putchar('\n');
    return 0;
}