#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <map>

const int maxT = 40;
//const int maxsz = maxT / 2;
const int maxsz = 8500000;
const bool insert_upwards = false,  del_upwards = false, check_upwards = false;
const double p_insert = 0.4, p_del = 0.3, p_check = 0.3;
const int sp = 0;

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

int mrd() {
    return (long long)rand() * rand() % maxsz;
}

struct Node {
    int key;
    Node *ch[2], *fa;
    Node(Node* f, int k) {
        fa = f;
        ch[0] = ch[1] = nullptr;
        key = k;
    }
};

class Splay {
    Node *root, *hot;

    void rotate(Node* p) {
        Node *f, *z;
        f = p->fa;
        z = (f == nullptr ? nullptr : f->fa);
        int k = (f->ch[1] == p);
        if (z)
            z->ch[z->ch[1] == f] = p;
        p->fa = z;
        f->ch[k] = p->ch[k ^ 1];
        if (p->ch[k ^ 1])
            p->ch[k ^ 1]->fa = f;
        p->ch[k ^ 1] = f;
        f->fa = p;
        f = nullptr;
        z = nullptr;
    }

    void splay(Node* p, Node* goal) {
        if (p == goal)
            return;
        Node *f, *z;
        while (p->fa != goal) {
            f = p->fa;
            z = (f == nullptr ? nullptr : f->fa);
            if (z != goal && z != nullptr)
                (z->ch[1] == f) ^ (f->ch[1] == p) ? rotate(p) : rotate(f);
            rotate(p);
        }
        if (goal == nullptr)
            root = p;
        f = nullptr;
        z = nullptr;
    }

public:
    Splay() {
        root = nullptr;
        insert(-1);
        insert(8500001 * 2 + 10);
    }

    int search(int key) {
        if (root == nullptr) {
            hot = nullptr;
            return -1;
        }
        hot = root;
        Node* tmp;
        int ret = -1;
        while (hot->key != key) {
            if (hot->key < key) {
                tmp = hot;
                ret = hot->key;
            }
            if (hot->ch[1] && hot->key < key)
                hot = hot->ch[1];
            else if (hot->ch[0] && hot->key > key)
                hot = hot->ch[0];
            else
                break;
        }
        if (hot->key == key) {
            ret = key;
            tmp = hot;
        }
        splay(tmp, 0);
        hot = tmp;
        return ret;
    }

    int fst() {
        search(-1);
        Node* tmp = root->ch[1];
        while (tmp->ch[0])
            tmp = tmp->ch[0];
        splay(tmp, 0);
        return tmp->key;
    }

    void insert(int key) {
        if (root == nullptr) {
            root = new Node(nullptr, key);
            return;
        }
        search(key);
        Node* tmp = new Node(nullptr, key);
        tmp->ch[0] = root;
        tmp->ch[1] = root->ch[1];
        if (root->ch[1])
            root->ch[1]->fa = tmp;
        if (root) {
            root->fa = tmp;
            root->ch[1] = nullptr;
        }
        root = tmp;
        tmp = nullptr;
    }

    void remove(int key) {
        search(key);
        Node* tmp = hot->ch[1];
        while (tmp->ch[0])
            tmp = tmp->ch[0];
        splay(tmp, root);
        tmp->ch[0] = root->ch[0];
        tmp->fa = nullptr;
        if (root->ch[0])
            root->ch[0]->fa = tmp;
        delete root;
        root = tmp;
        tmp = nullptr;
    }
}*splay;

int main() {
    srand(time(0));
    int T = maxT;
    int sz = 0, op, key, tmp, cnt = 0, check_cnt = 0;
    splay = new Splay;
    write(T);
    while (T--) {
        op = rand() % 100;
        if (op < p_insert * 100)
            op = 0;
        else if (op < (p_insert + p_del) * 100)
            op = 1;
        else
            op = 2;
        if (op == 1 && sz == 0)
            op = 0;
        if (sp != 0) {
            if (T >= maxT / 2)  op = 0;
            else    op = sp;
        }
        switch (op) {
            case 0: {
                if (!insert_upwards) {
                    putchar('A');
                    putchar(' ');
                    key = mrd() % maxsz;
                    tmp = splay->search(key);
                    while (tmp == key) {
                        key++;
                        tmp = splay->search(key);
                    }
                    write(key);
                    splay->insert(key);
                    sz++;
                    break;
                }
                else {
                    putchar('A');
                    putchar(' ');
                    key = cnt;
                    cnt++;
                    sz++;
                    splay->insert(key);
                    write(key);
                    break;
                }
            }
            case 1: {
                putchar('B');
                putchar(' ');
                if (!del_upwards) {
                    key = mrd() % maxsz;
                    tmp = splay->search(key);
                    while (tmp == -1) {
                        key = (key << 1 ) + 1;
                        tmp = splay->search(key);
                    }
                }
                else {
                    tmp = splay->fst();
                }
                write(tmp);
                splay->remove(tmp);
                sz--;
                break;
            }
            case 2: {
                putchar('C');
                putchar(' ');
                if (!check_upwards) {
                    key = mrd() % maxsz;
                }
                else {
                    key = check_cnt;
                    check_cnt += maxsz * 2 / maxT;
                }
                write(key);
                break;
            }
        }
    }
    return 0;
}