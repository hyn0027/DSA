#include <cstdio>
#include <iostream>
#include <cstring>

const int maxl =  16777216 + 5;

int l;

class BitMap {//抄的
    int len;
    char *s;
public:
    BitMap(int c) {
        len = (c + 7) / 8;
        s = new char[len];
        memset(s, 0, sizeof(s));
    }

    ~BitMap() {
        delete[] s;
        s = nullptr;
    }

    inline bool query(int k) {
        return s[k >> 3] & (0x80 >> (k & 0x07));
    }

    inline void flag(int k) {
        s[k >> 3] |= (0x80 >> (k & 0x07));
    }

    inline void clear(int k) {
        s[k >> 3] &= ~(0x80 >> (k & 0x07));
    }
}*str, *f;

void input() {
    str = new BitMap(maxl);
    char c = getchar();
    while (c != '0' && c != '1')
        c = getchar();
    while (c == '0' || c == '1') {
        if (c == '1')
            str->flag(l);
        l++;
        c = getchar();
    }
}

void output(int l, int ans) {
    for (int i = l - 1; i >= 0; i--) {
        int t = (ans & (1 << i)) >> i;
        if (t == 0)
            putchar('0');
        else
            putchar('1');
    }
    putchar('\n');
}

void work() {
    f = new BitMap(maxl);
    for (int i = 1; i < 25 && i <= l; i++) {
        int cnt = 0, pos = 0;
        for (int j = 0; j < i; j++)
            pos = (pos << 1) + str->query(j);
        f->flag(pos); 
        cnt++;
        for (int j = 1; j + i - 1 < l; j++) {
            pos = (pos << 1) & ((1 << i) - 1);
            pos |= str->query(j + i - 1);
            if (f->query(pos) == 0) {
                f->flag(pos);
                cnt++;
                if (cnt == (1 << i))
                    break;
            }
        }
        if (cnt < (1 << i)) {
            for (int ans = 0; ans < (1 << i); ans++)
                if (!f->query(ans)) {
                    output(i, ans);
                    return;
                }
        }
        for (int j = 0; j < (1 << i); j++)
            f->clear(j);
    }
}

int main() {
    input();
    work();
    return 0;
}