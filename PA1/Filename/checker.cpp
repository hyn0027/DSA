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
		printf("case %d:\n", i);
		system("data > data.in");
		system("main < data.in > std.out");
		system("test < data.in > test.out");
		if(system("fc std.out test.out"))	break;
	}
	return 0;
}
