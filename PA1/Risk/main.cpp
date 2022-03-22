#include <iostream>
#include <cstdio>

const int maxn = 1000000 + 10, maxk = 2000000 + 10;

using namespace std;

int n;
int x[maxn], cnt[maxk], kmax, queue[maxn], head, tail;
char readin[maxn * 11 + 10];
long long readm[maxn];

inline long long read() {
    long long ret = 0;
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
        return;
    }
    char my_out[13];
    unsigned short pt = 0;
    while (w) {
        my_out[pt++] = w % 10 + '0';
        w /= 10;
    }

    for (int i = pt - 1; i >= 0; i--) 
        putchar(my_out[i]);
}

int main() {
    scanf("%d", &n);
    fgets(readin, maxn * 11 + 2, stdin);
    for (int i = 1, pt = 0; i <= n; i++) {
        while (readin[pt] < '0' || readin[pt] > '9')
            pt++;
        while (readin[pt] >= '0' && readin[pt] <= '9') {
            x[i] = (x[i] << 1) + (x[i] << 3) + readin[pt] - '0';
            pt++; 
        }
    }
    fgets(readin, maxn * 11 + 2, stdin);
    for (int i = 1, pt = 0; i <= n; i++) {
        while (readin[pt] < '0' || readin[pt] > '9')
            pt++;
        while (readin[pt] >= '0' && readin[pt] <= '9') {
            readm[i] = (readm[i] << 1) + (readm[i] << 3) + readin[pt] - '0';
            pt++; 
        }
    }
    
    for (int i = 1, k; i <= n; i++) {
        long long m = readm[i];
        m = max((long long)i - m, (long long)0);

        while (x[queue[tail]] <= x[i - 1] && tail >= head) 
            tail--;
        queue[++tail] = i - 1;
        while (queue[head] < m)  head++;
        k = x[queue[head]];
        cnt[k]++;
        kmax = max(k, kmax);
    }
    for (int i = 1; i <= kmax + 3; i++)
        cnt[i] += cnt[i - 1];

    int T;
    long long p, q;
    scanf("%d", &T);
    while(T--) {
        scanf("%lld%lld", &p, &q);
        p = min(p, (long long)kmax + 1);
        q = min(q, (long long)kmax + 1);
        if(p != 0 && q != 0) {
            printf("%d %d\n", cnt[p - 1], cnt[q - 1] - cnt[p - 1]);
        }
        else if (q == 0) {
            printf("0 0\n");
        }
        else {
            printf("0 %d\n", cnt[q - 1]);
        }
    }
    return 0;
}