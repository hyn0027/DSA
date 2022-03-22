#include <iostream>
#include <cstring>
#include <cstdio> 
#include <algorithm>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    string x = "ZY";
    for (int i = 0; i < 26 * 500; i++){
        x += char(i % 26 + 'A');
        x += char(i % 26 + 'A');
    }
    for (int i = 0; i < 500; i++) {
        for (int j = 25; j >= 0; j--) {
            if (i == 0 && j == 25)  continue;
            x += char(j + 'A');
        }
    }
    cout << x << endl;
    int m = 2;
    cout << m << endl;
    while(m--) {
        int pos = 0;
        char col = m % 26 + 'A';
        //cout << pos << " " << col << endl;
    }
    cout << "26002 Z" << endl;
    cout << "0 A" << endl;
    return 0;
}