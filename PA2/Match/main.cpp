#include <cstdio>
#include <iostream>
#include <cstring>

const int hashmod[2] = {(int)1e9 + 7, (int)1e9 + 9}, maxl = 800000 + 5, p = 998244353;

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

struct Hash {
    int mod[2];
    void init(int x) {
        for (int i = 0; i < 2; i++)
            mod[i] = x % hashmod[i];
    }
    friend bool operator == (Hash a, Hash b) {
        for (int i = 0; i < 2; i++)
            if (a.mod[i] != b.mod[i])
                return false;
        return true;
    }
    inline void add(Hash a) {
        for (int i = 0; i < 2; i++)
            mod[i] = ((long long)mod[i] + a.mod[i]) % hashmod[i];
    }
    inline void mul(Hash a) {
        for (int i = 0; i < 2; i++)
            mod[i] = ((long long)mod[i] * a.mod[i]) % hashmod[i];
    }
};

int n, m, my_exp[maxl][2];

struct Node {
    int sz, c;
    bool rev;
    int ch[2], fa;
    Hash h[2];
    void init(int f, char x) {
        fa = f;
        c = x - 'a';
        rev = ch[0] = ch[1] = 0;
        sz = 1;
        h[0].init(c);
        h[1].init(c);
    }
};

struct pair_hash{
    Hash a, b;
};

class Splay {
    int root, tree_cnt;
    Node t[maxl];
    
	void up(int p){
        t[p].sz = 1;
        if(t[p].ch[0])
            t[p].sz += t[t[p].ch[0]].sz;
        if(t[p].ch[1])
            t[p].sz += t[t[p].ch[1]].sz;
        t[p].h[0] = get_hash(p, 0);
        t[p].h[1] = get_hash(p, 1);
	}

    void rotate(int p) {
        rev(p);
        int f = t[p].fa, z = t[f].fa, k = (t[f].ch[1] == p);
        rev(f);
        rev(z);
        t[z].ch[t[z].ch[1] == f] = p;
        t[p].fa = z;
        t[f].ch[k] = t[p].ch[k ^ 1];
        t[t[p].ch[k ^ 1]].fa = f;
        t[p].ch[k ^ 1] = f;
        t[f].fa = p;
        up(f);
        up(p);
    }

    void splay(int p, int goal) {
        rev(p);
        int f, z;
        while (t[p].fa != goal) {
            f = t[p].fa;
            z = t[f].fa;
            rev(f);
            rev(z);
            if (z != goal)
                (t[z].ch[1] == f) ^ (t[f].ch[1] == p) ? rotate(p) : rotate(f);
            rotate(p);
        }
        if (goal == 0)
            root = p;
    }

    void gothrough(int p) {
        if (!p) return;
        rev(p);
        gothrough(t[p].ch[0]);
        putchar(t[p].c + 'a');
        putchar(' ');
        std::cout << p;
        putchar(' ');
        std::cout << t[p].ch[0] << " " << t[p].ch[1] << " " << t[p].fa << " " << t[p].rev;
        putchar(' ');
        write(t[p].sz);
        gothrough(t[p].ch[1]);
    }

    void rev(int p) {
        if (t[p].rev) {
            std::swap(t[p].ch[0], t[p].ch[1]);
            std::swap(t[p].h[0], t[p].h[1]);
            if(t[p].ch[0])    t[t[p].ch[0]].rev ^= 1;
            if(t[p].ch[1])    t[t[p].ch[1]].rev ^= 1;
            t[p].rev = false;
        }
    }

    Hash get_hash(int p, int k) {
        rev(p);
        Hash ret, cur;
        ret.init(t[p].c);
        if (k == 0) {
            if (t[p].ch[0]) {
                rev(t[p].ch[0]);
                cur = t[t[p].ch[0]].h[k];
                for (int i = 0; i < 2; i++)
                    ret.mod[i] = (((long long)cur.mod[i] * my_exp[1][i]) % hashmod[i] + (long long)ret.mod[i]) % hashmod[i];
            }
            if (t[p].ch[1]) {
                rev(t[p].ch[1]);
                cur = t[t[p].ch[1]].h[k];
                for (int i = 0; i < 2; i++)
                    ret.mod[i] = (((long long)ret.mod[i] * my_exp[t[t[p].ch[1]].sz][i]) % hashmod[i] + (long long)cur.mod[i]) % hashmod[i];
            }
        }
        else {
            if (t[p].ch[1]) {
                rev(t[p].ch[1]);
                cur = t[t[p].ch[1]].h[k];
                for (int i = 0; i < 2; i++)
                    ret.mod[i] = (((long long)cur.mod[i] * my_exp[1][i]) % hashmod[i] + (long long)ret.mod[i]) % hashmod[i];
            }
            if (t[p].ch[0]) {
                rev(t[p].ch[0]);
                cur = t[t[p].ch[0]].h[k];
                for (int i = 0; i < 2; i++)
                    ret.mod[i] = (((long long)ret.mod[i] * my_exp[t[t[p].ch[0]].sz][i]) % hashmod[i] + (long long)cur.mod[i]) % hashmod[i];
            }
        }
        return ret;
    }

public:
    Splay() {
        root = tree_cnt = 0;
    }

    int find(int pos) {
        int tmp = root;
        int tmp_sz = 0;
        while (1) {
            int cur = 1;
            rev(tmp);
            if (t[tmp].ch[0])
                cur += t[t[tmp].ch[0]].sz;
            if (tmp_sz + cur == pos)
                break;
            if (tmp_sz + cur < pos) {
                tmp_sz += cur;
                tmp = t[tmp].ch[1];
            }
            else 
                tmp = t[tmp].ch[0];
        }
        return tmp;
    }

    void insert(int pos, char c) {
        if (root == 0) {
            root = ++tree_cnt;
            t[root].init(0, c);
            return;
        }
        int tmp = root;
        if (pos == 0) {
            tmp = find(1);
            splay(tmp, 0);
            int x = ++tree_cnt;
            t[x].init(tmp, c);
            t[tmp].ch[0] = x;
            splay(x, 0);
            return;
        }
        if (pos == t[root].sz) {
            tmp = find(pos);
            splay(tmp, 0);
            int x = ++tree_cnt;
            t[x].init(tmp, c);
            t[tmp].ch[1] = x;
            splay(x, 0);
            return;
        }
        tmp = find(pos);
        rev(tmp);
        int cur, tmp2 = tmp;
        if (t[tmp2].ch[1] == 0) {
            tmp = ++tree_cnt;
            t[tmp].init(tmp2, c);
            t[tmp2].ch[1] = tmp;
        }
        else {
            cur = t[tmp2].ch[1];
            rev(cur);
            while (t[cur].ch[0]) {
                cur = t[cur].ch[0];
                rev(cur);
            }
            tmp = ++tree_cnt;
            t[tmp].init(cur, c);
            t[cur].ch[0] = tmp;
        }
        splay(tmp, 0);
    }

    void del(int pos) {
        if (pos == 0 || pos == t[root].sz - 1) {
            int k = (pos == 0 ? 0 : 1);
            int tmp = root;
            rev(root);
            while (t[tmp].ch[k]) {
                tmp = t[tmp].ch[k];
                rev(tmp);
            }
            if (t[tmp].fa) {
                t[t[tmp].fa].ch[k] = t[tmp].ch[k ^ 1];
                if (t[tmp].ch[k ^ 1])
                    t[t[tmp].ch[k ^ 1]].fa = t[tmp].fa;
            }
            if (root == tmp) {
                root = t[tmp].ch[k ^ 1];
                if (t[tmp].ch[k ^ 1])
                    t[t[tmp].ch[k ^ 1]].fa = 0;
            }
            int x = t[tmp].fa;
            while(x != root && x) {
                up(x);
                x = t[x].fa;
            }
            up(root);
            if (t[tmp].fa)
                splay(t[tmp].fa, 0);
            return;
        }
        int pre = find(pos);
        splay(pre, 0);
        int suc = find(pos + 2);
        splay(suc, pre);
        rev(root);
        rev(t[root].ch[1]);
        t[t[root].ch[1]].ch[0] = 0;
        up(t[root].ch[1]);
        up(root);
    }

    void reverse(int p, int q) {
        if (p == 0 && q == t[root].sz - 1) {
            t[root].rev ^= 1;
            return;
        }
        if (p == 0) {
            int succ = find(q + 2);
            splay(succ, 0);
            rev(root);
            t[t[root].ch[0]].rev ^= 1;
            return;
        }
        if (q == t[root].sz - 1) {
            int pre = find(p);
            splay(pre, 0);
            rev(root);
            t[t[root].ch[1]].rev ^= 1;
            return;
        }
        int pre = find(p);
        splay(pre, 0);
        int succ = find(q + 2);
        splay(succ, pre);
        rev(root);
        rev(t[root].ch[1]);
        t[t[t[root].ch[1]].ch[0]].rev ^= 1;
        return;

    }

    void check() {
        gothrough(root);
        putchar('\n');
    }

    pair_hash query(int p, int q) {
        if (p == 0 && q == t[root].sz - 1)
            return pair_hash{get_hash(root, 0), get_hash(root, 1)};
        if (p == 0) {
            int succ = find(q + 2);
            splay(succ, 0);
            rev(root);
            return pair_hash{get_hash(t[root].ch[0], 0), get_hash(t[root].ch[0], 1)};
        }
        if (q == t[root].sz - 1) {
            int pre = find(p);
            splay(pre, 0);
            rev(root);
            return pair_hash{get_hash(t[root].ch[1], 0), get_hash(t[root].ch[1], 1)};
        }
        int pre = find(p);
        splay(pre, 0);
        int succ = find(q + 2);
        splay(succ, pre);
        rev(root);
        rev(t[root].ch[1]);
        return pair_hash{get_hash(t[t[root].ch[1]].ch[0], 0), get_hash(t[t[root].ch[1]].ch[0], 1)};
    }
}*splay;

void input() {
    n = read();
    m = read();
    splay = new Splay();
    char c;
    for (int i = 0; i < n; i++) {
        c = getchar();
        while (c < 'a' || c > 'z')  c = getchar();
        splay->insert(i, c);
        //splay->check();
    }
}

void operate() {
    int op, p, c, q, len;
    pair_hash a, b;
    while (m--) {
        op = read();
        switch(op) {
            case 1: {
                p = read();
                c = getchar();
                while (c < 'a' || c > 'z')  c = getchar();
                splay->insert(p, c);
                break;
            }
            case 2: {
                p = read();
                splay->del(p);
                break;
            }
            case 3: {
                p = read();
                q = read();
                splay->reverse(p, q);
                break;
            }
            case 4: {
                p = read();
                q = read();
                len = read();
                a = splay->query(p, p + len - 1);
                b = splay->query(q, q + len - 1);
                if (a.a == b.a && a.b == b.b) putchar('T');
                else    putchar('F');
                break;
            }
        }
        //splay->check();
    }
}

void init() {
    for (int i = 0; i < 2; i++)
        my_exp[0][i] = 1;
    for (int i = 1; i <= 800000; i++)
        for (int j = 0; j < 2; j++)
            my_exp[i][j] = (long long)my_exp[i - 1][j] * p % hashmod[j];
}

int main() {
    init();
    input();
    operate();
    return 0;
}