#include <ctime>
#include <cstdio>
#include <iostream>
const int l = 2000000;

int main() {
    srand(time(0));
    int len = l;
    while (len--)
        putchar(rand() % 1 + 'a');
    putchar('\n');
    return 0;
}