#include <iostream>
#include <cstring>
#include <cstdio> 
#include <algorithm>
#include <queue> 
#include <fstream>
#include <ctime>
using namespace std;
int t = 10; 
int main(){
	for(int i = 1; i <= t; i++){
		printf("case %d: ", i);
		system("data > data.in");
        double t0 = clock();
		system("main < data.in > std.out");
        printf("%lf\n", 1000 * (clock() - t0) / (double)CLOCKS_PER_SEC);
	}
	return 0;
}
