#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 501000 + 5;

int n, m, k;
string A, B;
short f[maxn][205];

void input() { //输入
    cin >> n >> m >> k;
    getline(cin, A);
    getline(cin, A);
    getline(cin, B);
}

inline short& dp(int x, int y) { //数组下标转换 f[x][y]表示A的0~x位转换为B的0~y位最少需要几次修改，由于k <= 100，因此只需要考虑x与y相差不超过100的情况。因此，y + 102 - x的下标一定是合法的。取102而不是100以留出余量避免访问越界。
    return f[x][y + 102 - x];
}

int ans() { //dp
    if (n == 0 || m == 0)
        return (n + m > k ? -1 : n + m); //特殊情况处理：有一个是空串。
    memset(f, 31, sizeof (f)); //f数组初始化为一个较大值（大于100即可）

    //初始化 dp(0, y)和dp(x, 0)的所有情况
    //dp(0, 0)
    if (A[0] == B[0])
        dp(0, 0) = 0;
    else
        dp(0, 0) = 2;
    //dp(0, y)
    for (int j = 1; j <= 100 && j < m; j++)
        if (A[0] == B[j])
            dp(0, j) = j;
        else
            dp(0, j) = dp(0, j - 1) + 1;
    //dp(x, 0)
    for (int i = 1; i <= 100 && i < n; i++)
        if (A[i] == B[0])
            dp(i, 0) = i;
        else
            dp(i, 0) = dp(i - 1, 0) + 1;
    
    for (int i = 1; i < n; i++) {
        for (int j = max(1, i - 100); j < m && j <= i + 100; j++) { //保证j在范围内，且j与i相差不超过100
            if (A[i] == B[j])
                dp(i, j) = dp(i - 1, j - 1); //dp转移方程
            else
                dp(i, j) = min(dp(i - 1, j), dp(i, j - 1)) + 1; //dp转移方程

            if (dp(i, j) > 200)//由于k<=100 200以上与101是完全等价的 这一操作是为了保证short不溢出
                dp(i, j) = 101;
        }
    }
    return (dp(n - 1, m - 1) > k ? -1 : dp(n - 1, m - 1)); //判定并返回
}

int main() {
    input();
    cout << ans() << endl;
    return 0;
}