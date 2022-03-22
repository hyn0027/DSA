#include <iostream>
#include <cstring>
#include <cstdio> 
#include <algorithm>
#include <queue> 
#include <fstream>
#include <ctime>
using namespace std;
/*
t是测试组数
当且仅当std程序跑的时间小于max_time_std的时候，data生成的数据将被用来测试 这个threshhold用于保证数据时合法的
当test程序跑的时间大于max_time_test的时候，break，考虑可能出了奇怪的问题 太慢了
*/
int t = 50; 
int max_time_std = 1000;
int max_time_test = 1000;
int main(){
	for(int i = 1; i <= t; i++){
		printf("case %d:\n", i);
		system("data > data.in");
        double t0 = clock();
		system("main < data.in > std.out");
		//system("echo %errorlevel%");
        printf("std use time: %lf\n", 1000 * (clock() - t0) / (double)CLOCKS_PER_SEC);
		if (1000 * (clock() - t0) / (double)CLOCKS_PER_SEC > max_time_std)
			continue;
        t0 = clock();
		system("test < data.in > test.out");
        printf("test use time: %lf\n", 1000 * (clock() - t0) / (double)CLOCKS_PER_SEC);
		if (1000 * (clock() - t0) / (double)CLOCKS_PER_SEC > max_time_test)
			break;
		if(system("fc std.out test.out")) {
			printf("sth. goes wrong");
			break;
		}
	}
	return 0;
}
