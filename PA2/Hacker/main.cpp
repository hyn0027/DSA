#include "crc32.h"
#include <cstdio>
#include <iostream>
#include <cstring>

inline int read() {
    int ret = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        ret = (ret << 1) + (ret << 3) + c - '0', c = getchar();
    return ret;
}


const char c_list[20] = "1234567890tsinghua";
char salt[5];
int n;

void init(int len, long long crc, std::string s) {
    if (len == 0)
        return;
    for (int i = 0, x; i < 18; i++) {
        x = crc32(crc, (unsigned char*)c_list[i], 1);
        //hash x, s + c_list[i]
        init(len - 1, x, s + c_list[i]);
    }
}

int main() {
    n = read();
    fgets(salt, 5, stdin);
    init(5, (long long)0, "");
    return 0;
}