#include<iostream>
#include<string.h>
#include<cmath>
using namespace std;
unsigned int raw[524300];
unsigned int memo[524300];
int outing[24];
void print(unsigned int num, int length) {
	for (int i = 0; i < length; i++) {
		outing[i] = num % 2;
		num /= 2;
	}
	for (int i = length - 1; i >= 0; i--) {
		cout << outing[i];
	}
	cout << endl;
}
int main() {
	memset(raw, 0, sizeof(raw));
	memset(memo, 0, sizeof(raw));
	//cout << raw[520000] << raw[524299] << endl;
	char t;
	unsigned int length = 0, x, y;
	//cin >> t;
	while (cin.peek() != 10) {
		cin >> t;
		x = length >> 5;
		//cout << x << ',';
		y = length % 32;
		//cout << y << endl;
		raw[x] |= ((t-'0') << (31 - y));
		//cout << raw[x] << endl;
		length++;
		//cout << t << endl;
	}
	//cout << length;//length记录了原始串的长度/位数
	int m = 1;//m代表检测的子串长度
	unsigned int point;
	unsigned int tool;//用来从原始串中取出片段的“工具”
	int total;
	while (m<=24) {
		//cout << m << ':' << endl;
		tool = pow(2, m) - 1;
		//cout <<"tool"<<':'<<bitset<sizeof(tool) * 8>(tool) << endl;
		total = 0;//记得备注一宁教过这个
		for (point=0; point < length- m + 1; point++) {
			//cout << bitset<sizeof(memo[x]) * 8>(memo[x]) << endl;
			tool = pow(2, m) - 1;
			x = point >> 5;
			y = point % 32;
			tool = raw[x] & (tool << (32 - y - m));
			tool = tool >> (32 - y - m);//到这一步，取出了原始串相应位置相应长度的子串，用10进制表示（这里，怎么告诉它是要左边补0呢？）（前面>>5不是还用得好好的吗啊这）
			//cout << "have taken out:"<<bitset<sizeof(tool) * 8>(tool) << endl;
			//判断子串是否已经检测到了
			x = tool >> 5;
			y = tool % 32;
			if (memo[x] & (1 << (31 - y)))//已经有了
				continue;
			//到了这儿，说明还没有
			total++;
			if (total == pow(2, m)) {
				//cout << bitset<sizeof(memo[x]) * 8>(memo[x]) << endl;
				break;
			}
			memo[x] |= (1 << 31 - y);
			//cout << bitset<sizeof(memo[x]) * 8>(memo[x]) << endl;
			//cout <<"total:"<< total << endl;
		}
		if (total < pow(2, m)) {
			//遍历一遍取出最小的为0位
			for (unsigned int i = 0; i < pow(2, m); i++) {
				x = i >> 5;
				y = i % 32;
				if (!(memo[x] & (1 << (31 - y)))) {
					print(i, m);
					//cout << bitset<sizeof(i) * 8>(i) << endl;
					break;
				}
			}
			break;
		}
		memset(memo, 0, sizeof(memo));
		m++;
	}
	if (m > 24)
		cout << "0000000000000000000000000" << endl;
	//cout << t;
	return 0;
}