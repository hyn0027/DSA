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
        insert(8500001);
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
    splay = new Splay;
    int T = read(), key;
    char c;
    while (T--) {
        c = getchar();
        while (c < 'A' && c > 'C')  c = getchar();
        key = read();
        switch (c) {
            case 'A': {
                splay->insert(key);
                break;
            }
            case 'B': {
                splay->remove(key);
                break;
            }
            case 'C': {
                write(splay->search(key));
                break;
            }
        }
    }
    return 0;
}