#include <iostream>
#include <cstdio>
#include <cstring>
const int maxn = 20000000 + 5;
int nex[maxn], l;
char p[maxn];
long long ans[maxn];

void get_nex(char* s) {
	nex[0] = -1;
	for(int i = 0, j; i < l; i++){
		j = nex[i];
		while (j >= 0 && s[i] != s[j])
            j = nex[j];
        nex[i + 1] = j + 1;
	}

}

int main() {
    scanf("%s", &p);
    l = strlen(p);
    get_nex(p);
    ans[1] = 1;
    long long out = 1;
    for (int i = 2; i <= l; i++) {
        ans[i] = 1;
        ans[i] += ans[nex[i]];
        out += ans[i];
    }
    printf("%lld\n", out);
    return 0;
}