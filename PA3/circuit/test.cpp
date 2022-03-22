#include <iostream>
#include <cstring>
#include <cstdio>

const int maxn = 5e5 + 5, maxl = 64 + 5;

struct node{
    int num = 0, lc = -1, rc = -1, next = -1;
} N[maxn / 50];

char first[maxn][maxl];
int post[maxn], maxnum = 0, n,k;

void insert(int ran){
    N[0].num++;
    int now = 0;
    for (int i = 0; i < 64; i ++){
        if (first[ran][i] == '0'){
            if (N[now].lc == -1)
                N[now].lc = ++maxnum;
            N[N[now].lc].num++;
            now = N[now].lc;
        }
        else {
            if(N[now].rc == -1)
                N[now].rc = ++maxnum;
            N[N[now].rc].num++;
            now = N[now].rc;
        }
    }
    N[now].num++;
    if (N[now].next == -1) {
        N[now].next = ran;
        post[ran] = -1;
    }
    else {
        int r = N[now].next;
        while (post[r] != -1)
            r = post[r];
        post[r] = ran;
        post[ran] = -1;
    }
}

void del(int r){
    int now = 0;
    int hot = 0;
    N[0].num--;
    for(int i = 0; i < 64; i ++){
        hot = now;
        if(first[r][i] == '0')
            now = N[now].lc;
        else
            now = N[now].rc;
        N[now].num--;
    }
    if(N[now].num == 0)
        N[now].next = -1;
    else
        N[now].next = post[N[now].next];

}

int search(int goal){
    int now = 0;
    for(int i = 0; i < 64; i ++){
        if(first[goal][i] == '1'){
            if(N[now].lc != -1 && N[N[now].lc].num != 0)
                now = N[now].lc;
            else
                now = N[now].rc;
        }
        else{
            if(N[now].rc != -1 && N[N[now].rc].num != 0)
                now = N[now].rc;
            else
                now = N[now].lc;
        }
    }
    if(N[now].next == goal)return post[goal];
    return N[now].next;
}

int main(){
    memset(post,-1, 500000);
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i ++)
            scanf("%s/n", first[i]);
    for(int i = 0; i < k + 2; i ++){
        insert(i);
    }
    for(int i = 0; i < n && i < k + 2; i ++){
        printf("%d\n", search(i));
        if(i + k + 2 < n) insert(i + k + 2);
    }
    for(int i = k+2; i < n; i ++){
        del(i - k - 2);
        printf("%d\n", search(i));
        if(i + k + 2 < n)insert(i + k + 2);
    }
    return 0;
}