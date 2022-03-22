#include <cstdio>
#include <iostream>
#include <cstring>

const int maxn = 1e6 + 5;

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

struct Node {
    int key, npl, sz;
    Node *l, *r;
    Node(int k) {
        key = k;
        l = r = nullptr;
        npl = 1;
        sz = 1;
    }
};

Node* merge_queue(Node* a, Node* b) {//小根堆 只存k个
    if (!a) return b;
    if (!b) return a;
    if (a->key > b->key)    std::swap(a, b);
    a->r = merge_queue(a->r, b);
    if (!a->l || (a->l->npl < a->r->npl))
        std::swap(a->l, a->r);
    if (a->r)
        a->npl = a->r->npl + 1;
    else
        a->npl = 1;
    a->sz = 1;
    if (a->l)
        a->sz += a->l->sz;
    if (a->r)
        a->sz += a->r->sz;
    return a;
}

int ancestor[maxn];
Node* pq[maxn];
int n, m, k, q;

int find_fa(int x) {
    if (x == ancestor[x])
        return x;
    return ancestor[x] = find_fa(ancestor[x]);
}

void input() {
    n = read();
    m = read();
    k = read();
    q = read();
    for(int i = 1, a; i <= n; i++) {
        a = read();
        ancestor[i] = i;
        pq[i] = new Node(a);
    }
    int u, v;
    while (m--) {
        u = read();
        v = read();
        u = find_fa(u);
        v = find_fa(v);
        if (u == v)
            continue;
        ancestor[u] = v;
        pq[v] = merge_queue(pq[v], pq[u]);
        pq[u] = nullptr;
        while (pq[v]->sz > k) {
            Node* cur = pq[v];
            pq[v] = merge_queue(pq[v]->l, pq[v]->r);
            delete cur;
        }
    }
}

void operate() {
    int op, u, v;
    while(q--) {
        op = read();
        if (op == 1) {
            u = read();
            v = read();
            u = find_fa(u);
            v = find_fa(v);
            if (u == v)
                continue;
            ancestor[u] = v;
            pq[v] = merge_queue(pq[v], pq[u]);
            pq[u] = nullptr;
            while (pq[v]->sz > k) {
                Node* cur = pq[v];
                pq[v] = merge_queue(pq[v]->l, pq[v]->r);
                delete cur;
            }
        }
        else {
            u = read();
            u = find_fa(u);
            write((pq[u]->sz >= k ? pq[u]->key : -1));
        }
    }
}

int main() {
    input();
    operate();
    return 0;
}