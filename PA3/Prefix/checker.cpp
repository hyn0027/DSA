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
        double t0 = clock();
		//system("std < data.in > std.out");
        //printf("std use time: %lf\n", 1000 * (clock() - t0) / (double)CLOCKS_PER_SEC);
		//if (1000 * (clock() - t0) / (double)CLOCKS_PER_SEC > 500)
		//	continue;
        //t0 = clock();
		system("main < data.in > test.out");
        printf("test use time: %lf\n", 1000 * (clock() - t0) / (double)CLOCKS_PER_SEC);
		//if (1000 * (clock() - t0) / (double)CLOCKS_PER_SEC > 500)
		//	break;
		//if(system("fc std.out test.out")) {
		//	printf("sth. goes wrong");
		//	break;
		//}
	}
	return 0;
}
