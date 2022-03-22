#include <cstring>
#include <iostream>
#include <cstdio>
#define sz 64
const int maxn = 5e5 + 5, maxl = 100;

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
    putchar('\n');
}

int n, k;
unsigned long long data[maxn];

int main() {
    n = read();
    k = read();
    char in;
    for (int i = 0; i < n; i++) {
        in = getchar();
        while (in != '0' && in != '1')
            in = getchar();
        data[i] = in - '0';
        for (int j = 1; j < sz; j++)
            data[i] = (data[i] << 1) | (getchar() - '0');
    }
    for (int i = 0; i < n; i++) {
        int ans = i - k - 1;
        ans = std::max(ans, 0);
        for (int j = ans; j - i <= k + 1 && j < n; j++)
            if ((data[j] ^ data[i]) > (data[i] ^ data[ans]))
                ans = j;
        if (ans == i)   ans++;
        std::cout << ans << std::endl;
    }
    return 0;
}