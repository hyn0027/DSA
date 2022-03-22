#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

struct binNode {
    int key;
    int number;
    long long time;
    int tag;
};


unsigned int input[400001];
char ope[200001];
unsigned int pai[400001];
unsigned int temp[400001];
unsigned int unfinished[400001];
unsigned int finished[800002];
binNode tree[1600004];
int leaf;

//mergesort使用PA1-2作业中板子
void merge(int lo, int mi, int hi) {
    int p = 0;
    int p1 = lo;
    int p2 = mi;
    while ((p1<mi)&&(p2<hi)) {
        temp[p++] = (pai[p1] <= pai[p2]) ? pai[p1++] : pai[p2++];
    }
    while (p1<mi) {
        temp[p++] = pai[p1++];
    }
    while (p2<hi) {
        temp[p++] = pai[p2++];
    }
    // for (int i = 0; i < p; i++) 
    //     cout << tempx[i] << ' ';
    // cout << endl;
    memmove(pai+lo, temp, sizeof(unsigned int)*(hi-lo));
    return;
}

void mergesort(int lo, int hi) {
    if (lo == hi-1) return;
    int mi = (lo + hi) >> 1;
    mergesort(lo, mi);
    mergesort(mi, hi);
    merge(lo, mi, hi);
}

inline void down_lazy(int l) {
    if (tree[l].tag) {
        tree[l << 1].time += tree[l << 1].number * tree[l].tag;
        tree[(l << 1) | 1].time += tree[(l << 1) | 1].number * tree[l].tag;
        tree[l << 1].tag += tree[l].tag;
        tree[(l << 1) | 1].tag += tree[l].tag;
        tree[l].tag = 0;
    }
}

//在turn的时候从上往下遍历，维护遍历过得节点的time、tag
void turnover(int l, unsigned int a, unsigned int b) {
    cout << "t" << l << " " << tree[l].key << " " << tree[l].key + tree[l].number - 1 << endl;
    if ((a <= tree[l].key) && (b >= tree[l].key + tree[l].number - 1)) {
        tree[l].time += tree[l].number;
        tree[l].tag++;
        return;
    }
    //在范围外
    else if ((b<tree[l].key)||(a>(tree[l].key+tree[l].number-1))) {
        return;
    }
    //在中间
    else {
        down_lazy(l);
        turnover((l << 1), a, b);
        turnover(((l << 1) | 1), a, b);
        tree[l].time = tree[l << 1].time + tree[(l << 1) | 1].time;
        return;
    }
}

inline void turn(int i) {
    turnover(1, input[i << 1], input[(i << 1) | 1]);
}

//查询时，同样按照范围内 中 外分类，遇到lazy tag则向下扩散
unsigned long long que(int l, unsigned int a, unsigned int b) {
    cout << "q" << l << " " << tree[l].key << " " << tree[l].key + tree[l].number - 1 << endl;
    if ((a <= tree[l].key) && (b >= tree[l].key+tree[l].number-1)) {
        return tree[l].time;
    }
    else if ((b<tree[l].key)||(a>(tree[l].key+tree[l].number-1))) {
        return 0;
    }
    else {
        down_lazy(l);
        return que(l << 1, a, b) + que((l << 1) | 1, a, b);
    }
}

inline void query(int i) {
    cout << que(1, input[i << 1], input[(i << 1) | 1]) << endl;
}

int main() {
    unsigned int n;
    int m;
    cin >> n >> m;
    int count = 0;
    for (int k = 0; k < m; k++) {
        cin >> ope[k] >> input[k << 1] >> input[(k << 1) | 1];
        count++;
    }

    //处理叶节点
    //mergesort
    memmove(pai, input, sizeof(unsigned int)*2*count);
    mergesort(0, 2*count);
    int realc = 1;
    unsigned int tmp = pai[0];
    unfinished[0] = tmp;
    for (int i = 1; i < 2*count; i++) {
        if (pai[i]!=tmp){
            unfinished[realc++] = pai[i];
            tmp = pai[i];
        }
    }
    // for (int i = 0; i < 2*m; i++) {
    //     cout << pai[i] << ' ';
    // }
    // cout << endl;
    // while(realc!=0) {
    //     cout << unfinished[--realc] << ' ';
    // }
    // cout << endl;

    //将每个区间与边界点分为两个区间
    int point0 = 0;
    int point1 = 0;
    while (point1<(realc-1)) {
        finished[point0]=unfinished[point1];
        if (unfinished[point1]!=(unfinished[point1+1]-1)) {
            point0++;
            finished[point0]=unfinished[point1]+1;
        }
        point0++;
        point1++;
    }
    finished[point0]=unfinished[point1];
    point0++; // finished为所有叶节点的第一位数字，point0为叶节点的数目

    // for (int i = 0; i < point0; i++) {
    //     cout << finished[i] << ' ';
    // } 
    // cout << endl;

    //构造segment tree
    //https://www.jianshu.com/p/6fd130084a43(以数组构造segment tree的思路)
    //构造BBST(叶子的上面一层为满的)
    int bei = 0;
    while (pow(2, bei) < point0) {
        bei++;
    }
    int sur = pow(2, bei-1);
    int tmp0 = point0%sur;
    if (tmp0==0) {
        tmp0 = sur;
    }
    for (int i = (sur<<1); i < (sur<<1)+(tmp0<<1); i++) {
        int mem = i-(sur<<1);
        if (mem < point0-1) {
            tree[i].key = finished[mem];
            tree[i].number = finished[mem+1]-finished[mem];
            tree[i].time = 0;
            tree[i].tag = 0;
        }
        else if (mem == point0-1) {
            tree[i].key = finished[mem];
            tree[i].number = 1;
            tree[i].time = 0;
            tree[i].tag = 0;
        }
    }

    for (int i = sur; i < (sur<<1); i++) {
        if (i-sur < tmp0) {
            tree[i].key = tree[i<<1].key;
            tree[i].number = tree[i<<1].number + tree[(i<<1)+1].number;
            tree[i].time = 0;
            tree[i].tag = 0;
        }
        else {
            if (tmp0+i-sur < point0-1) {
                tree[i].key = finished[tmp0+i-sur];
                tree[i].number = finished[tmp0+i-sur+1]-finished[tmp0+i-sur];
                tree[i].time = 0;
                tree[i].tag = 0;
            }
            else if (tmp0+i-sur == point0-1) {
                tree[i].key = finished[tmp0+i-sur];
                tree[i].number = 1;
                tree[i].time = 0;
                tree[i].tag = 0;
            }
        }
    }
    leaf = sur+tmp0;
    // //构造满二叉树
    // for (int i = leaf; i < 2*leaf; i++) {
    //     if (i-leaf < point0-1) {
    //         tree[i].key = finished[i-leaf];
    //         tree[i].number = finished[i-leaf+1]-finished[i-leaf];
    //         tree[i].time = 0;
    //         tree[i].tag = 0;
    //     }
    //     else if (i-leaf == point0-1) {
    //         tree[i].key = finished[i-leaf];
    //         tree[i].number = 1;
    //         tree[i].time = 0;
    //         tree[i].tag = 0;
    //     }
    //     else {
    //         tree[i].key = 0;
    //         tree[i].number = 0;
    //         tree[i].time = 0;
    //         tree[i].tag = 0;
    //     }
    // }
    // for (int i = leaf-1; i > 0; i--) {
    //     tree[i].key = tree[2*i].key;
    //     tree[i].number = tree[2*i].number + tree[2*i+1].number;
    //     tree[i].time = 0;
    //     tree[i].tag = 0;
    // }

    // for (int i = 1; i < 2*leaf; i++) {
    //     cout << tree[i].key << ' ' << tree[i].number << ' ' << tree[i].tag << endl;
    // }

    //树的search
    for (int i = 0; i < m; i++) {
        if (ope[i] == 'H') {
            turn(i);
            // if (i<=6) {
            // for (int i = 1; i < 2*leaf; i++) {
            //     cout << tree[i].key << ' ' << tree[i].number << ' ' << tree[i].time << ' ' << tree[i].tag << endl;
            // }}

        }
        else {
            query(i);
            // if (i<=6) {
            // for (int i = 1; i < 2*leaf; i++) {
            //     cout << tree[i].key << ' ' << tree[i].number << ' ' << tree[i].time << ' ' << tree[i].tag << endl;
            // }}
        }
        cout << endl;
    }

    return 0;
}