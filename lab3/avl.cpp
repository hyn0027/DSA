#include <iostream>
#include <cstdio>
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
    int key, h;
    Node *ch[2], *fa;

    Node(int k, Node* l, Node* r, Node* f) {
        key = k;
        ch[0] = l;
        ch[1] = r;
        h = 0;
        fa = f;
    }

    Node* tallerch() {
        if (!ch[0]) return ch[1];
        if (!ch[1]) return ch[0];
        if (ch[0]->h > ch[1]->h)
            return ch[0];
        return ch[1];
    }
};

class AVLTree {
    Node *root, *hot;
    
    void up(Node *p) {
        if (!p) return;
        p->h = 0;
        if (p->ch[0])
            p->h = p->ch[0]->h + 1;
        if (p->ch[1] && p->ch[1]->h + 1 > p->h)
            p->h = p->ch[1]->h + 1;
    }

    int BalanceFactor(Node *p) {
        return (p->ch[0] ? p->ch[0]->h : -1) - (p->ch[1] ? p->ch[1]->h : -1);
    }

    bool Balanced(Node* p) {
        int f = BalanceFactor(p);
        return -2 < f && f < 2;
    }

    Node* succ(Node* p) {
        Node* ret = p->ch[1];
        while(ret->ch[0])
            ret = ret->ch[0];
        return ret;
    }

    void removeAt(Node* p) {
        if (!p->fa) {
            if (!p->ch[0] && !p->ch[1]) {
                delete p;
                p = root = hot = nullptr;
                return;
            }
            if (!p->ch[0]) {
                p->ch[1]->fa = nullptr;
                root = p->ch[1];
                delete p;
                p = hot = nullptr;
                return;
            }
            if (!p->ch[1]) {
                p->ch[0]->fa = nullptr;
                root = p->ch[0];
                delete p;
                p = hot = nullptr;
                return;
            }
            hot = succ(p);
            std::swap(hot->key, p->key);
            removeAt(hot);
            return;
        }
        int k = (p->fa->ch[1] == p);
        if (!p->ch[0] && !p->ch[1]) {
            p->fa->ch[k] = nullptr;
            hot = p->fa;
            delete p;
            p = nullptr;
            return;
        }

        if (!p->ch[0]) {
            p->ch[1]->fa = p->fa;
            p->fa->ch[k] = p->ch[1];
            hot = p->fa;
            delete p;
            p = nullptr;
            return;
        }
        if (!p->ch[1]) {
            p->ch[0]->fa = p->fa;
            p->fa->ch[k] = p->ch[0];
            hot = p->fa;
            delete p;
            p = nullptr;
            return;
        }
        hot = succ(p);
        std::swap(hot->key, p->key);
        removeAt(hot);
        return;
    }

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
        up(f);
        up(p);
        if (root == f)
            root = p;
        f = nullptr;
        z = nullptr;
    }

    void rotateAt(Node* p) {
        Node *f, *z;
        f = p->fa;
        z = f->fa;
        (z->ch[1] == f) ^ (f->ch[1] == p) ? rotate(p), rotate(p): rotate(f);
    }

public:
    AVLTree() {
        root = hot = nullptr;
    }

    void insert(int key) {
        if (root == nullptr) {
            root = new Node(key, nullptr, nullptr, nullptr);
            return;
        }
        search(key);
        hot->ch[(key < hot->key ? 0 : 1)] = new Node(key, nullptr, nullptr, hot);
        Node* tmp = hot;
        while (tmp) {
            up(tmp);
            tmp = tmp->fa;
        }
        hot = hot->fa;
        while(hot) {
            if (!Balanced(hot))
                rotateAt(hot->tallerch()->tallerch());
            hot = hot->fa;
        }
        tmp = nullptr;
    }

    void remove(int key) {
        search(key);
        removeAt(hot);
        Node* tmp = hot;
        while (tmp) {
            up(tmp);
            tmp = tmp->fa;
        }
        while(hot) {
            if (!Balanced(hot))
                rotateAt(hot->tallerch()->tallerch());
            hot = hot->fa;
        }
        tmp = nullptr;
    }

    int search(int key) {
        if (root == nullptr) {
            hot = nullptr;
            return -1;
        }
        hot = root;
        int ret = -1;
        while (hot->key != key) {
            if (hot->key < key)
                ret = hot->key;
            if (hot->ch[1] && hot->key < key)
                hot = hot->ch[1];
            else if (hot->ch[0] && hot->key > key)
                hot = hot->ch[0];
            else
                break;
        }
        if (hot->key == key)
            ret = key;
        return ret;
    }
}*avl;

int main() {
    avl = new AVLTree;
    int T = read(), key;
    char c;
    while (T--) {
        c = getchar();
        while (c < 'A' && c > 'C')  c = getchar();
        key = read();
        switch (c) {
            case 'A': {
                avl->insert(key);
                break;
            }
            case 'B': {
                avl->remove(key);
                break;
            }
            case 'C': {
                write(avl->search(key));
                break;
            }
        }
    }
    return 0;
}