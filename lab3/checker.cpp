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
	double t0, t1 = 0, t2 = 0;
	for(int i = 1; i <= t; i++){
		printf("case %d:\n", i);
		system("data > data.in");
        t0 = clock();
		system("avl < data.in > avl.out");
        printf("avl use time: %lf\n", 1000 * (clock() - t0) / (double)CLOCKS_PER_SEC);
		t1 +=  1000 * (clock() - t0) / (double)CLOCKS_PER_SEC;
        t0 = clock();
		system("splay < data.in > splay.out");
        printf("splay use time: %lf\n", 1000 * (clock() - t0) / (double)CLOCKS_PER_SEC);
		t2 +=  1000 * (clock() - t0) / (double)CLOCKS_PER_SEC;
		for (int j = 1, k = 1; j < 1000; j++)
			k = k * j % 3;
	}
	printf("avl use time average %lf\nsplay use time average %lf", t1 / t, t2 / t);
	return 0;
}
