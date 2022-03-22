#include <cstdio>
#include <iostream>
#include <ctime>
int main() {
    srand(time(0));
    //int len = 10;
    int len = 3200000;
    while (len--)
        putchar(rand() % 26 + 'a');
    //int t = 4000000;
    int t = 100000;
    char cc[2] = {'L', 'R'};
    printf("\n%d\n", t);
    t--;
    while(t--) {
        int o = rand() % 6;
        //int o = 2;
        if (o == 0) {
            putchar('<');
            putchar(' ');
            putchar(cc[rand() % 2]);
            putchar('\n');
        }
        else if (o == 1) {
            putchar('>');
            putchar(' ');
            putchar(cc[rand() % 2]);
            putchar('\n');
        }
        else if (o = 2) {
            putchar('I');
            putchar(' ');
            putchar(cc[rand() % 2]);
            putchar(' ');
            putchar(rand() % 26 + 'a');
            putchar('\n');
        }
        else if (o == 3) {
            putchar('D');
            putchar(' ');
            putchar(cc[rand() % 2]);
            putchar('\n');
        }
        else if (o > 3) {
            putchar('R');
            putchar('\n');
        }
    }
    putchar('S');
    //putchar('\n');
    return 0;
}