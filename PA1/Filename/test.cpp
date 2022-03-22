#include <iostream>
#include <string>
using namespace std;

string old("");
string goal("");
int N,M,K;
char temp;
int** lcs;
int s = 0;
int flag = 0;
void dp(){
    int _K = 2*K;
    lcs[0][K] = (goal[0] == old[0]);
    for(int i = 1; i <= min(M-1, 2*K + 4); i ++){
        lcs[0][i + K] = max(int(goal[i] == old[0]), lcs[0][i - 1 + K]);
        ///cout << 0 << " " << i << " " << lcs[0][i + K] << endl;
    }
    for(int i = 1; i < N; i ++){
        for(int j = max(i - K, 0); j <= min(i + K, M - 1) ; j ++){
            if(old[i] != goal[j]){
                if(j + K - i - 1 >= 0 && j > 0)
                    lcs[i%2][j + K - i] = max(lcs[i%2][j + K - i - 1], lcs[(i-1)%2][j + K - i + 1]);
                else{
                	lcs[i%2][j + K - i] = max(0, lcs[(i - 1)%2][j + K -i + 1]);
                    //cout << "?";
				}
            }
            else if(old[i] == goal[j]){
                 lcs[i%2][j + K - i] = lcs[(i-1)%2][j + K - i]+ 1 ;
            }
            //cout << i << " " << j << " " << lcs[i % 2][j + K - i] << endl;
        }
    }
   //cout << "...";
}


int main(){
    cin >> N >> M >> K;
    lcs = new int*[2];
    int _K = 2*K;
    for(int i = 0; i < 2; i ++)
        lcs[i] = new int[_K + 5];
    for(int i = 0; i < 2; i ++)
        for(int j = 0; j < _K + 5; j ++)
            lcs[i][j] = 0;
    cin >> old;
    cin >> goal;
    dp();
    int result = N + M - 2*lcs[(N-1)%2][M-N+K];
    if(N - M > K || M - N > K)cout<<-1;
    else if(result > K)cout<<-1;
    else{
        cout << result;
    }
    delete[] lcs;
    return 0;

}

