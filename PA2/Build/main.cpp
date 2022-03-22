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
    Node *brothers[2];//[0] younger_brother; [1] older_brother
    Node *fst_son; 
    int maxHeightInSelfAndOlderBrothers;
    int height;
    int sz;
    Node() {
        
    }
};

struct Tree {
    Node* root;
    int **edge, *s_num;
    int operation[maxn], mk_len;

    void build(int s, Node* cur) {
        cur->fst_son = nullptr;
        cur->height = 0;
        cur->sz = 1;
        Node* tmp;
        for (int i = s_num[s] - 1; i >= 0; i--) {
            tmp = new Node;
            tmp -> brothers[1] = cur->fst_son;
            if (cur->fst_son != nullptr)
                cur->fst_son->brothers[0] = tmp;
            cur->fst_son = tmp;
            build(edge[s][i], tmp);
            if(tmp->height + 1 > cur->height)
                cur->height = tmp->height + 1;
            tmp->maxHeightInSelfAndOlderBrothers = tmp->height;
            if (tmp->brothers[1] != nullptr && tmp->brothers[1]->maxHeightInSelfAndOlderBrothers > tmp->height)
                tmp->maxHeightInSelfAndOlderBrothers = tmp->brothers[1]->maxHeightInSelfAndOlderBrothers;
            cur->sz += tmp->sz;
            tmp = nullptr;
        }
        if (cur->fst_son != nullptr)
            cur->fst_son->brothers[0] = nullptr;
        tmp = nullptr;
    }

    int Query(Node* s, int pt, int len, int flag) {
        if (pt == len)
            return (flag == 0 ? s->height : s->sz);
        Node* tmp = s->fst_son;
        if (tmp == nullptr)
            return (flag == 0 ? s->height : s->sz);
        for (int i = 0; i < operation[pt]; i++) {
            tmp = tmp->brothers[1];
            if (tmp == nullptr)
                return (flag == 0 ? s->height : s->sz);
        }
        int ans = Query(tmp, pt + 1, len, flag);
        tmp = nullptr;
        return ans;
    }

    void upd_rmNode_maxHeight(Node *s) {
        Node* tmp = s->brothers[0];
        while (tmp != nullptr) {
            tmp->maxHeightInSelfAndOlderBrothers = tmp->height;
            if (tmp->brothers[1]->maxHeightInSelfAndOlderBrothers > tmp->height)
                tmp->maxHeightInSelfAndOlderBrothers = tmp->brothers[1]->maxHeightInSelfAndOlderBrothers;
            tmp = tmp->brothers[0];
        }
        tmp = nullptr;
        return;
    }

    Node* rm(Node* s, int pt, int len) {
        Node* tmp = s->fst_son;
        bool return_here = false;
        if (pt == len || tmp == nullptr)
            return_here = true;
        if (return_here == false) {
            for (int i = 0; i < operation[pt]; i++) {
                tmp = tmp->brothers[1];
                if (tmp == nullptr) {
                    if (root == s)
                        exit(0);
                    return_here = true;
                    break;
                }
            }
        }
        if (return_here) {
            tmp = s->brothers[0];
            if (tmp != nullptr) {
                tmp->maxHeightInSelfAndOlderBrothers = tmp->height;
                if (s->brothers[1] != nullptr && s->brothers[1]->maxHeightInSelfAndOlderBrothers > tmp->maxHeightInSelfAndOlderBrothers)
                    tmp->maxHeightInSelfAndOlderBrothers = s->brothers[1]->maxHeightInSelfAndOlderBrothers;
                upd_rmNode_maxHeight(tmp);
            }
            if (s->brothers[0] != nullptr)
                s->brothers[0]->brothers[1] = s->brothers[1];
            if (s->brothers[1] != nullptr)
                s->brothers[1]->brothers[0] = s->brothers[0];
            tmp = nullptr;
            mk_len = len - 1;
            return s;
        }
        Node* ans = rm(tmp, pt + 1, len);
        if (ans == s->fst_son)
            s->fst_son = ans->brothers[1];
        if (s->fst_son == nullptr)
            s->height = 0;
        else
            s->height = s->fst_son->maxHeightInSelfAndOlderBrothers + 1;
        s->maxHeightInSelfAndOlderBrothers = s->height;
        if (s->brothers[1] != nullptr && s->brothers[1]->maxHeightInSelfAndOlderBrothers > s->maxHeightInSelfAndOlderBrothers)
            s->maxHeightInSelfAndOlderBrothers = s->brothers[1]->maxHeightInSelfAndOlderBrothers;
        upd_rmNode_maxHeight(s);
        s->sz -= ans->sz;
        tmp = nullptr;
        return ans;
    }

    void insert(Node* s, int pt, int len, Node* src, int order) {
        Node* tmp = s->fst_son;
        bool return_here = false;
        if (pt == len || tmp == nullptr)
            return_here = true;
        if (return_here == false) {
            for (int i = 0; i < operation[pt]; i++) {
                tmp = tmp->brothers[1];
                if (tmp == nullptr) {
                    return_here = true;
                    break;
                }
            }
        }
        if (return_here) {
            tmp = s;
            if (tmp->fst_son == nullptr) {
                tmp->fst_son = src;
                src->maxHeightInSelfAndOlderBrothers = src->height;
                src->brothers[0] = src->brothers[1] = nullptr;
            }
            else if(order != 0) {
                tmp = s->fst_son;
                for (int i = 0; i < order - 1; i++) {
                    if (tmp->brothers[1] == nullptr)
                        break;
                    tmp = tmp->brothers[1];
                }
                src->brothers[0] = tmp;
                src->brothers[1] = tmp->brothers[1];
                if (src->brothers[1] != nullptr)
                    src->brothers[1]->brothers[0] = src;
                tmp->brothers[1] = src;
                src->maxHeightInSelfAndOlderBrothers = src->height;
                if (src->brothers[1] != nullptr && src->brothers[1]->maxHeightInSelfAndOlderBrothers > src->height)
                    src->maxHeightInSelfAndOlderBrothers = src->brothers[1]->maxHeightInSelfAndOlderBrothers;
                upd_rmNode_maxHeight(src);
            }
            else {
                s->fst_son->brothers[0] = src;
                src->brothers[1] = s->fst_son;
                src->brothers[0] = nullptr;
                src->maxHeightInSelfAndOlderBrothers = src->height;
                if (src->brothers[1]->maxHeightInSelfAndOlderBrothers > src->height)
                    src->maxHeightInSelfAndOlderBrothers = src->brothers[1]->maxHeightInSelfAndOlderBrothers;
                s->fst_son = src;
            }
            s->height = s->fst_son->maxHeightInSelfAndOlderBrothers + 1;
            s->maxHeightInSelfAndOlderBrothers = s->height;
            if (s->brothers[1] != nullptr && s->brothers[1]->maxHeightInSelfAndOlderBrothers > s->maxHeightInSelfAndOlderBrothers)
                s->maxHeightInSelfAndOlderBrothers = s->brothers[1]->maxHeightInSelfAndOlderBrothers;
            upd_rmNode_maxHeight(s);
            s->sz += src->sz;
            tmp = nullptr;
            return;
        }
        insert(tmp, pt + 1, len, src, order);
        s->height = s->fst_son->maxHeightInSelfAndOlderBrothers + 1;
        s->maxHeightInSelfAndOlderBrothers = s->height;
        if (s->brothers[1] != nullptr && s->brothers[1]->maxHeightInSelfAndOlderBrothers > s->maxHeightInSelfAndOlderBrothers)
            s->maxHeightInSelfAndOlderBrothers = s->brothers[1]->maxHeightInSelfAndOlderBrothers;
        upd_rmNode_maxHeight(s);
        s->sz += src->sz;
        tmp = nullptr;
        return;
    }
    
public:
    Tree(int n) {
        s_num = new int[n + 2];
        edge = new int*[n + 2];
        for (int i = 1; i <= n; i++) {
            s_num[i] = read();
            edge[i] = new int[s_num[i] + 1];
            for (int j = 0; j < s_num[i]; j++)
                edge[i][j] = read();
            root = new Node;
        }
        build(1, root);
        root->brothers[0] = root->brothers[1] = nullptr;
        root->maxHeightInSelfAndOlderBrothers = root->height;
        delete[] s_num;
        for (int i = 1; i <= n; i++) {
            delete[] edge[i];
            edge[i] = nullptr;
        }
        delete[] edge;
    }

    void query(int flag) {
        int len = read();
        for (int i = 0; i < len; i++)
            operation[i] = read();
        write(Query(root, 0, len, flag));
    }

    void move() {
        int len = read();
        for (int i = 0; i < len; i++)
            operation[i] = read();
        Node* src = rm(root, 0, len);
        len = read();
        for (int i = 0; i < len; i++)
            operation[i] = read();
        int pos = read();
        insert(root, 0, len, src, pos);
    }
}*t;

int main() {
    int n = read(), m = read();
    t = new Tree(n);
    int op;
    while (m--) {
        op = read();
        if (op == 0)
            t->move();
        else
            t->query(op - 1);
    }
    return 0;
}