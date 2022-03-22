#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 200000 + 5;

struct Point {
    int x, y;
    inline void read() {
        scanf("%d%d", &x, &y);
    }
};

int n;
int x[maxn], y[maxn];

void my_sort(int A[], int l, int r) { //归排 区间[l, r] //参考数据结构讲义 归并排序 一节
    if (r <= l)
        return;
    int mid = (l + r) >> 1;
    my_sort(A, l, mid);
    my_sort(A, mid + 1, r);
    int pt1 = l, pt2 = mid + 1, pt3 = l;
    static int tmp[maxn];
    memcpy(tmp + l, A + l, sizeof(int) * (mid - l + 1));
    while (pt1 <= mid && pt2 <= r)
        A[pt3++] = (tmp[pt1] < A[pt2] ? tmp[pt1++] : A[pt2++]);
    while (pt1 <= mid)
        A[pt3++] = tmp[pt1++];
}

void input() {//输入
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &y[i]);
}

void init() { //数据排序
    my_sort(x, 0, n - 1);
    my_sort(y, 0, n - 1);
}

inline bool inside(Point p, long long x, long long y) {//以x、y为截距的直线与线段OP是否有交点
    return x * (long long)p.y + y * (long long)p.x >= x * y;
}

int find_ans(Point p) {//二分查找
    int l = 0, r = n, mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (inside(p, x[mid], y[mid])) 
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

void work() {//查询操作
    int T;
    Point p;
    scanf("%d", &T);
    while (T--) {
        p.read();
        printf("%d\n", find_ans(p));
    }
}

int main() {
    input();
    init();
    work();
    return 0;
}