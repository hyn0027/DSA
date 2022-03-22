#include <iostream>
#include <cstring>
#include <cstdio> 
#include <algorithm>
#include <queue> 
#include <fstream>
#include <ctime>
using namespace std;
int t = 1; 
int main(){
	for(int i = 1; i <= t; i++){
		printf("case %d:\n", i);
		system("data > data.in");
		system("std < data.in > std.out");
        ifstream infile; 
        infile.open("std.out"); 
        string data1;
        infile >> data1; 
        infile.close();
        if (data1 == "[Error]") {
            i--;
            continue;
        }
        printf("ok\n");
        int st = time(0);
		system("test < data.in > test.out");
        int ed = time(0);
        cout << ed - st << endl;
        printf(":");
        infile.open("test.out"); 
        string data2;
        infile >> data2; 
        infile.close();
		if(data1 != data2) {
            printf("?");
            break;
        }
	}
	return 0;
}
