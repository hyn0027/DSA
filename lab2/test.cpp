#include <cstdio>
#include <cstring>
int main() {
    char s[1000];
    scanf("%s", s);
    printf("%d\n", (s[0] > 0x80));
    printf("%s %d\n", s, strlen(s));
    return 0;
}