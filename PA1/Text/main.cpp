#include <cstdio>
#include <iostream>
#include <iostream>
#include <cstring>

const int maxl = 3200000 + 5, maxn = 4000000 + 5;

inline int read() {
    int ret = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        ret = (ret << 1) + (ret << 3) + c - '0', c = getchar();
    return ret;
}

#pragma pack(1)
struct Node {
    char c;
    int pred, succ;
}node[(maxl + maxn) << 1];

char *str;
int nd_cnt;

inline int new_Node(int pred, int succ, char c = ' ') {
    node[nd_cnt++] = {c, pred, succ};
    return nd_cnt - 1;
}

class List {
private:
    int head, tail, left, right;
    bool rev;

    void InsertAsPred(int goal, char c) {
        node[node[goal].pred].succ = new_Node(node[goal].pred, goal, c);
        node[goal].pred = node[node[goal].pred].succ;
    }

    void Del(int goal) {
        node[node[goal].pred].succ = node[goal].succ;
        node[node[goal].succ].pred = node[goal].pred;
    }

public:
    List(bool flag) {
        head = new_Node(nd_cnt, -1);
        int pt = head;
        int l = strlen(str) - 1;
        if (flag) {
            for (int i = 0; i < l; i++) {
                node[pt].succ = new_Node(pt, -1, str[i]);
                pt = node[pt].succ;
            }
            tail = new_Node(pt, nd_cnt);
            node[pt].succ = tail;
            left = head;
            right = pt;
            rev = 0;
        }
        else {
            for (int i = l - 1; i >= 0; i--) {
                node[pt].succ = new_Node(pt, -1, str[i]);
                pt = node[pt].succ;
            }
            tail = new_Node(pt, nd_cnt);
            node[pt].succ = tail;
            left = pt;
            right = head;
            rev = 1;
        }
    }

    char MoveCusor(char pos, bool direction) {
        //direction: 0left 1right
        if (pos == 'L')
            if (!direction) {
                if (left == head)    return 'F';
                if (left == right)  rev = 0;
                left = node[left].pred;
                return 'T';
            }
            else {
                if (left == node[tail].pred)    return 'F';
                if (left == right)  rev = 1;
                left = node[left].succ;
                return 'T';
            }
        else
            if (!direction) {
                if (right == head)    return 'F';
                if (left == right)  rev = 1;
                right = node[right].pred;
                return 'T';
            }
            else {
                if (right == node[tail].pred)    return 'F';
                if (left == right)  rev = 0;
                right = node[right].succ;
                return 'T';
            }
    }

    void InsertToLeft(char pos, char c) {
        if (pos == 'L') {
            InsertAsPred(node[left].succ, c);
            if (left == right)
                right = node[right].succ;
            left = node[left].succ;
        }
        else {
            InsertAsPred(node[right].succ, c);
            if (left == right)
                left = node[left].succ;
            right = node[right].succ;
        }
    }

    void InsertToRight(char pos, char c) {
        if (pos == 'L')
            InsertAsPred(node[left].succ, c);
        else
            InsertAsPred(node[right].succ, c);
    }

    char DeleteLeft(char pos) {
        if (pos == 'L') {
            if (left == head)
                return 'F';
            if (left == right)
                right = node[right].pred;
            left = node[left].pred;
            Del(node[left].succ);
            return 'T';
        }
        else {
            if (right == head)
                return 'F';
            if (left == right)
                left = node[left].pred;
            right = node[right].pred;
            Del(node[right].succ);
            return 'T';
        } 
    }

    char DeleteRight(char pos) {
        if (pos == 'L') {
            if (left == node[tail].pred)
                return 'F';
            if (node[left].succ == right)
                right = left;
            Del(node[left].succ);
            return 'T';
        }
        else {
            if (right == node[tail].pred)
                return 'F';
            if (left == node[right].succ)
                left = right;
            Del(node[right].succ);
            return 'T';
        }
    }

    int RevLeft() {
        return left;
    }

    int RevRight() {
        return right;
    }

    void RightptRight() {
        right = node[right].succ;
    }

    void RightptLeft() {
        right = node[right].pred;
    }

    void LeftptRight() {
        left = node[left].succ;
    }

    void LeftptLeft() {
        left = node[left].pred;
    }

    char Reverse(List* rev_list) {
        if (left == right || rev)
            return 'F';
        int l1, l2, r1, r2;
        l1 = left;
        r1 = node[right].succ;
        l2 = rev_list->RevRight();
        r2 = node[rev_list->RevLeft()].succ;
        right = node[right].succ;
        rev_list->LeftptRight();
        
        std::swap(node[l1].succ, node[l2].succ);
        node[node[l1].succ].pred = l1;
        node[node[l2].succ].pred = l2;

        std::swap(node[r1].pred, node[r2].pred);
        node[node[r1].pred].succ = r1;
        node[node[r2].pred].succ = r2;
        
        right = node[right].pred;
        rev_list->LeftptLeft();
        return 'T';
    }

    void output(){
        int pt = node[head].succ;
        while (pt != tail) {
            putchar(node[pt].c);
            pt = node[pt].succ;
        }
        putchar('\n');
    }
};

List *list, *rev_list;

int main() {
    str = new char[maxl];
    fgets(str, maxl - 1, stdin);
    list = new List(1);
    rev_list = new List(0);
    delete[] str;
    int T = read();
    char o, w, c;
    while (T--) {
        o = getchar();
        switch(o) {
            case '<': {
                w = getchar();
                while (w != 'L' && w != 'R')
                    w = getchar();
                putchar(list->MoveCusor(w, 0));
                putchar('\n');
                rev_list->MoveCusor(w, 1);
                break;
            }
            case '>': {
                w = getchar();
                while (w != 'L' && w != 'R')
                    w = getchar();
                putchar(list->MoveCusor(w, 1));
                putchar('\n');
                rev_list->MoveCusor(w, 0);
                break;
            }
            case 'I': {
                w = getchar();
                while (w != 'L' && w != 'R')
                    w = getchar();
                c = getchar();
                while (c < 33 || c > 126)
                    c = getchar();
                list->InsertToLeft(w, c);
                rev_list->InsertToRight(w, c);
                putchar('T');
                putchar('\n');
                break;
            }
            case 'D': {
                w = getchar();
                while (w != 'L' && w != 'R')
                    w = getchar();
                putchar(list->DeleteRight(w));
                putchar('\n');
                rev_list->DeleteLeft(w);
                break;
            }
            case 'R': {
                putchar(list->Reverse(rev_list));
                putchar('\n');
                break;
            }
            case 'S': {
                list->output();
                break;
            }
            default: {
                T++;
                break;
            }
        }
    }
    return 0;
}