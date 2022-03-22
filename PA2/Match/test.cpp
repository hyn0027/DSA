#include <iostream>

#include "math.h"
using namespace std;

struct Node {
    int fa = -1;
    int lc = -1;
    int rc = -1;
    bool haslc() {
        return lc != -1;
    }
    bool hasrc() {
        return rc != -1;
    }
    int size = 1;
    int reverse = 0;
    long long hash1;
    long long rev_h1;
    long long rev_h2;
    long long hash2;
    int strlen = 1;
    char val;
};

Node* AT;
int root;  // root父亲设为自身
int N;
int M;
int Max;
int base = 131;
long long mod1 = 19260817;
long long mod2 = 19660813;
long long mul[800005][2];
char* read;

void splay(int, int&);
void print();
int search(int, int);
void pushdown(int x) {
    if (x == -1) return;
    if (AT[x].reverse) {
        AT[x].reverse = 0;
        swap(AT[x].hash1, AT[x].rev_h1);
        swap(AT[x].hash2, AT[x].rev_h2);
        swap(AT[x].lc, AT[x].rc);
        if (AT[x].haslc()) AT[AT[x].lc].reverse ^= 1;  //异或！
        if (AT[x].hasrc()) AT[AT[x].rc].reverse ^= 1;
    }
}

int Hash1(char a) { return (long long)a % mod1; }
int Hash2(char a) { return (long long)a % mod2; }

void pushup(int x) {
    if (x == -1) return;
    pushdown(x);
    AT[x].size = 1;
    AT[x].strlen = 1;
    AT[x].hash1 = Hash1(AT[x].val);  // val表示本x节点自身存的char
    AT[x].hash2 = Hash2(AT[x].val);
    AT[x].rev_h1 = Hash1(AT[x].val);
    AT[x].rev_h2 = Hash2(AT[x].val);

    if (AT[x].haslc()) {  //先左后右
        AT[x].size += AT[AT[x].lc].size;
        AT[x].hash1 =
            (AT[AT[x].lc].hash1 * mul[AT[x].strlen][0] + AT[x].hash1) % mod1;
        AT[x].hash2 =
            (AT[AT[x].lc].hash2 * mul[AT[x].strlen][1] + AT[x].hash2) % mod2;
        AT[x].strlen += AT[AT[x].lc].strlen;
    }
    if (AT[x].hasrc()) {
        AT[x].size += AT[AT[x].rc].size;
        AT[x].hash1 =
            (AT[x].hash1 * mul[AT[AT[x].rc].strlen][0] + AT[AT[x].rc].hash1) %
            mod1;
        AT[x].hash2 =
            (AT[x].hash2 * mul[AT[AT[x].rc].strlen][1] + AT[AT[x].rc].hash2) %
            mod2;

        AT[x].rev_h1 = (AT[AT[x].rc].rev_h1 * mul[1][0] + AT[x].rev_h1) % mod1;
        AT[x].rev_h2 = (AT[AT[x].rc].rev_h2 * mul[1][1] + AT[x].rev_h2) % mod2;

        AT[x].strlen += AT[AT[x].rc].strlen;
    }
    if (AT[x].haslc()) {
        AT[x].rev_h1 =
            (AT[x].rev_h1 * mul[AT[AT[x].lc].strlen][0] + AT[AT[x].lc].rev_h1) %
            mod1;
        AT[x].rev_h2 =
            (AT[x].rev_h2 * mul[AT[AT[x].lc].strlen][1] + AT[AT[x].lc].rev_h2) %
            mod2;
    }
}

void attachaslc(int c, int f) {
    if (c == -1) {
        AT[f].lc = -1;
        return;
    }
    AT[c].fa = f;
    AT[f].lc = c;
}

void attachasrc(int c, int f) {  //第一个参数为孩子，第二个为父亲
    if (c == -1) {
        AT[f].rc = -1;
        return;
    }
    AT[c].fa = f;
    AT[f].rc = c;
}

bool is_lch(int x) {
    return AT[AT[x].fa].lc == x;
}

bool is_rch(int x) {
    return AT[AT[x].fa].rc == x;
}

void rotate(int x) {
    int p = AT[x].fa, g = AT[p].fa;
    pushdown(p);
    bool k = is_rch(x);
    pushdown(x);
    pushdown(k ? AT[x].rc : AT[x].lc);
    if (g != -1) is_rch(p) ? attachasrc(x, g) : attachaslc(x, g);
    else AT[x].fa = -1, root = x; // root == p
    if (k) {
        attachasrc(AT[x].lc, p);
        attachaslc(p, x);
    }
    else {
        attachaslc(AT[x].rc, p);
        attachasrc(p, x);
    }
    pushup(p);
}

void splay(int x, int &des) {
    pushdown(x);
    for (int p = AT[x].fa; x != des; rotate(x), pushup(x), p = AT[x].fa) {
        if (p == x) exit(0);
        if (p != des)
            (is_lch(x) ^ is_lch(p)) ? rotate(x) : rotate(p);
    }
}

// need 引用？
int search(int p,
           int cur) {  //返回当前rank 为p的节点的初始下标,cur表示当前所在节点
                       ////认为一定可以找到？
    pushdown(cur);
    if (!AT[cur].haslc() && p == 0)  //以防无左孩子
    {
        return cur;
    } else if (!AT[cur].haslc() && AT[cur].hasrc()) {
        return search(p - 1, AT[cur].rc);
    } else if (p == AT[AT[cur].lc].size) {  // must have lc
        // splay(cur, des);//命中之后再splay, or else太浪费
        // debug
        return cur;
    } else if (p > AT[AT[cur].lc].size) {
        return search(p - AT[AT[cur].lc].size - 1, AT[cur].rc);  //
    } else {
        return search(p, AT[cur].lc);
    }
}

void select(int x, int &des) {
    int t = search(x, root);
    splay(t, des);
}

void select_seg(int l, int r) {
    select(l - 1, root);
    select(r + 1, AT[root].rc);
}

void reverse(int l, int r) {
    select_seg(l, r);
    pushdown(root);
    pushdown(AT[root].rc);
    pushdown(AT[AT[root].rc].lc);
    AT[AT[AT[root].rc].lc].reverse ^= 1;
    splay(AT[AT[root].rc].lc, root);
}

void insert(int pos, char ch) {
    select_seg(pos, pos - 1);
    pushdown(root);
    int p = AT[root].rc;
    pushdown(p);
    int x = Max++;
    AT[x].val = ch;
    AT[x].hash1 = Hash1(ch);
    AT[x].hash2 = Hash2(ch);
    AT[x].rev_h1 = Hash1(ch);
    AT[x].rev_h2 = Hash2(ch);
    attachaslc(x, p);
    pushup(p), pushup(root);
    splay(x, root);
}

void del(int p) {  // splay至根的妙处是，pushup无需从底至上遍历
    select_seg(p, p);
    pushdown(root);
    pushdown(AT[root].rc);
    attachaslc(-1, AT[root].rc);
    splay(AT[root].rc, root);
}

bool issame(int p, int q, int len) {
    if (p == q) return true;

    select_seg(p, p + len -1);
    pushdown(root);
    pushdown(AT[root].rc);
    pushdown(AT[AT[root].rc].lc);
    long long p_hash1 = AT[AT[AT[root].rc].lc].hash1;
    long long p_hash2 = AT[AT[AT[root].rc].lc].hash2;

    select_seg(q, q + len -1);
    pushdown(root);
    pushdown(AT[root].rc);
    pushdown(AT[AT[root].rc].lc);
    long long q_hash1 = AT[AT[AT[root].rc].lc].hash1;
    long long q_hash2 = AT[AT[AT[root].rc].lc].hash2;

    return p_hash1 == q_hash1 && p_hash2 == q_hash2;
}

int build(int l, int r) {
    if (l > r) return -1;
    int mid = (l + r) >> 1;

    char ch = (mid && mid <= N) ? read[mid - 1] : 0;
    AT[mid].val = ch;
    AT[mid].hash1 = Hash1(ch);
    AT[mid].hash2 = Hash2(ch);
    AT[mid].rev_h1 = Hash1(ch);
    AT[mid].rev_h2 = Hash2(ch);
    if ((AT[mid].lc = build(l, mid - 1)) != -1)
        AT[AT[mid].lc].fa = mid;
    if ((AT[mid].rc = build(mid + 1, r)) != -1)
        AT[AT[mid].rc].fa = mid;
    pushup(mid);
    return mid;
}

void hash_init() {
    mul[0][0] = 1;
    mul[0][1] = 1;
    for (int i = 1; i < M + N + 2; i++) {
        mul[i][0] = (mul[i - 1][0] * base) % mod1;
        mul[i][1] = (mul[i - 1][1] * base) % mod2;
    }
}

int main() {
    //应该开N+M大小的数组？考虑到插入
    scanf("%d%d", &N, &M);
    Max = N + 2;
    AT = new Node[M + N + 2];
    read = new char[N + 1];
    if (N)
        scanf("%s", read);
    hash_init();

    root = build(0, N + 1);

    int type;
    int p, q, len;
    char c;
    for (int i = 0; i < M; i++) {
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d", &p);
            while (c = getchar(), c < 'a' || c > 'z');
            insert(p + 1, c);
        }
        if (type == 2) {
            scanf("%d", &p);
            del(p + 1);
        }
        if (type == 3) {
            scanf("%d%d", &p, &q);
            reverse(p + 1, q + 1);
        }
        if (type == 4) {
            scanf("%d%d%d", &p, &q, &len);
            if (issame(p + 1, q + 1, len))
                putchar('T');
            else {
                putchar('F');
            }
        }
    }
    return 0;
}