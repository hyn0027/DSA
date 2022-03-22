#include <iostream>
#include <cstdio>
#include <cstring>
const int maxn = 20000000 + 5;
int l;
char p[maxn];
long long ans;

int main() {
    scanf("%s", &p);
    l = strlen(p);
    for (int i = 1; i <= l; i++) {
        for (int j = 0; j + i - 1 < l; j++) {
            bool diff =  false;
            for (int k = 0; k < i; k++)
                if (p[k] != p[j + k]) {
                    diff = true;
                    break;
                }
            if (diff == false)
                ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}