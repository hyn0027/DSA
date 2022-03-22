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

struct Node{
    Node *c[2];
    int id;
    Node() {
        c[0] = c[1] = nullptr;
        id = maxn + 100;
    }
    void insert(int num) {
        id = num;
    }
    void upd() {
        if (c[0])
            id = std::min(c[0]->id, id);
        if (c[1])
            id = std::min(c[1]->id, id);
    }
};

int n, k, ans[maxn];
Node* t;
char in[maxn][maxl];

void add(Node* p, char* str, int pt, int l, int num) {
    if (pt == l) {
        p->insert(num);
        return;
    }
    int kk = str[pt] - '0';
    if(p->c[kk] == nullptr)
        p->c[kk] = new Node;
    add(p->c[kk], str, pt + 1, l, num);
    p->upd();
}

int search(Node* p, char* str, int pt, int l, int num) {
    if (pt == l)
        return p->id;
    int kk = (str[pt] - '0') ^ 1;
    if (p->c[kk] == nullptr || p->c[kk]->id > num + k + 1)
        kk ^= 1;
    return search(p->c[kk], str, pt + 1, l, num);
}

int main() {
    n = read();
    k = read();
    for (int i = 0; i < n; i++) {
        in[i][0] = getchar();
        while (in[i][0] != '0' && in[i][0] != '1')
            in[i][0] = getchar();
        for (int j = 1; j < sz; j++)
            in[i][j] = getchar();
    }
    t = new Node();
    for (int i = n - 1; n - 1 - i <= k + 1 && i >= 0; i--)
        add(t, in[i], 0, sz, i);
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = search(t, in[i], 0, sz, i);
        if (ans[i] == i)    ans[i]++;
        if (i - k - 2 >= 0)
            add(t, in[i - k - 2], 0, sz, i - k - 2);
    }
    for (int i = 0; i < n; i++)
        write(ans[i]);
    return 0;
}