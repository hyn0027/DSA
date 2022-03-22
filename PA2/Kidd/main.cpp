#include <cstdio>
#include <iostream>
#include <cstring>

const int maxm = 200000 + 5;

inline int read() {
    int ret = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        ret = (ret << 1) + (ret << 3) + c - '0', c = getchar();
    return ret;
}

inline void write(long long w) {
    if (w == 0) {
        putchar('0');
        putchar('\n');
        return;
    }
    char my_out[40];
    unsigned short pt = 0;
    while (w) {
        my_out[pt++] = w % 10 + '0';
        w /= 10;
    }

    for (int i = pt - 1; i >= 0; i--) 
        putchar(my_out[i]);
    putchar('\n');
}

void my_sort(int *A, int l, int r) {
    if (l >= r)
        return;
    int mid = (l + r) >> 1;
    my_sort(A, l, mid);
    my_sort(A, mid + 1, r);
    int pt1 = l, pt2 = mid + 1, pt3 = l;
    static int tmp[maxm * 4];
    memcpy(tmp + l, A + l, sizeof(int) * (mid - l + 1));
    while (pt1 <= mid && pt2 <= r)
        A[pt3++] = (tmp[pt1] < A[pt2] ? tmp[pt1++] : A[pt2++]);
    while (pt1 <= mid)
        A[pt3++] = tmp[pt1++];
}

int n, m, op[maxm][3], t_len;

class Descrete {
    int *data, *desnum, len, *sz;
public:
    Descrete(int c) {
        data = new int[c * 2 + 5];
        desnum = new int[c * 2 + 5];
        sz = new int[c * 2 + 5];
        len = 0;
    }

    void add(int x) {
        data[len++] = x;
    }

    void init() {
        my_sort(data, 0, len - 1);
        int pt1 = 1, pt2 = 1;
        while (pt2 < len) {
            while (pt2 < len && data[pt2] == data[pt2 - 1])
                pt2++;
            if (pt2 >= len)
                break;
            data[pt1++] = data[pt2++];
        }
        pt1 = 0;
        sz[pt1] = 1;
        desnum[pt1++] = data[0];
        for (int i = 1; i < len; i++) {
            if (data[i] != data[i - 1] + 1) {
                sz[pt1] = data[i] - 1 - data[i - 1];
                desnum[pt1++] = data[i] - 1;
            }
            sz[pt1] = 1;
            desnum[pt1++] = data[i];
        }
        len = pt1;
        t_len = len;
    }

    int get_sz(int x) {
        if (x >= len || x < 0)  return 0;
        return sz[x];
    }

    int get_descrete(int x) {
        int l = 0, r = len - 1, mid = 0;
        while (l < r) {
            mid = (l + r) >> 1;
            if (desnum[mid] < x)    l = mid + 1;
            else    r = mid;
        }
        return l;
    }

    int get_origin(int x) {
        if (x >= len || x < 0)  return -1;
        return desnum[x];
    }
}*des;

struct Node{
    long long sz, w, down;
};

class SegmentTree {
    Node *node;

    void build(int pos, int l, int r) {
        node[pos].sz = node[pos].w = node[pos].down = 0;
        if (l == r) {
            node[pos].sz = des->get_sz(l);
            return;
        }
        int mid = (l + r) >> 1;
        build(pos * 2, l, mid);
        build(pos * 2 + 1, mid + 1, r);
        node[pos].sz = node[pos * 2].sz + node[pos * 2 + 1].sz;
    }

    void add(int pos, long long w) {
        node[pos].w += node[pos].sz * w;
        node[pos].down += w;
    }

    void down(int pos) {
        if (node[pos].down) {
            add(pos * 2, node[pos].down);
            add(pos * 2 + 1, node[pos].down);
            node[pos].down = 0;
        }
    }

    void up(int pos) {
        node[pos].w = node[pos * 2].w + node[pos * 2 + 1].w;
    }

public:
    SegmentTree(int c){
        node = new Node[c * 4];
        build(1, 0, c - 1);
    }

    void rev(int pos, int segl, int segr, int goall, int goalr) {
        if (goall <= segl && segr <= goalr) {
            add(pos, (long long)1);
            return;
        }
        down(pos);
        int mid = (segl + segr) >> 1;
        if (goall <= mid)   rev(pos * 2, segl, mid, goall, goalr);
        if (mid + 1 <= goalr)   rev(pos * 2 + 1, mid + 1, segr, goall, goalr);
        up(pos);
    }

    long long query(int pos, int segl, int segr, int goall, int goalr) {
        if (goall <= segl && segr <= goalr)
            return node[pos].w;
        down(pos);
        int mid = (segl + segr) >> 1;
        long long ret = 0;
        if (goall <= mid)   ret += query(pos * 2, segl, mid, goall, goalr);
        if (mid + 1 <= goalr)   ret += query(pos * 2 + 1, mid + 1, segr, goall, goalr);
        return ret;
    }
}*seg;

void input() {
    n = read();
    m = read();
    des = new Descrete(m * 2);
    char c;
    for (int i = 0; i < m; i++) {
        c = getchar();
        while (c != 'Q' && c != 'H')
            c = getchar();
        if (c == 'H')
            op[i][0] = 0;
        else
            op[i][0] = 1;
        op[i][1] = read();
        op[i][2] = read();
        des->add(op[i][1]);
        des->add(op[i][2]);
    }
    des->init();
}

void operate() {
    seg = new SegmentTree(t_len);
    for (int i = 0; i < m; i++) {
        if (op[i][0] == 0)
            seg->rev(1, 0, t_len - 1, des->get_descrete(op[i][1]), des->get_descrete(op[i][2]));
        else
            write(seg->query(1, 0, t_len - 1, des->get_descrete(op[i][1]), des->get_descrete(op[i][2])));
    }
}

int main() {
    input();
    operate();
    return 0;
}