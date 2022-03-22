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
	//cout << length;//length��¼��ԭʼ���ĳ���/λ��
	int m = 1;//m��������Ӵ�����
	unsigned int point;
	unsigned int tool;//������ԭʼ����ȡ��Ƭ�εġ����ߡ�
	int total;
	while (m<=24) {
		//cout << m << ':' << endl;
		tool = pow(2, m) - 1;
		//cout <<"tool"<<':'<<bitset<sizeof(tool) * 8>(tool) << endl;
		total = 0;//�ǵñ�עһ���̹����
		for (point=0; point < length- m + 1; point++) {
			//cout << bitset<sizeof(memo[x]) * 8>(memo[x]) << endl;
			tool = pow(2, m) - 1;
			x = point >> 5;
			y = point % 32;
			tool = raw[x] & (tool << (32 - y - m));
			tool = tool >> (32 - y - m);//����һ����ȡ����ԭʼ����Ӧλ����Ӧ���ȵ��Ӵ�����10���Ʊ�ʾ�������ô��������Ҫ��߲�0�أ�����ǰ��>>5���ǻ��õúúõ����⣩
			//cout << "have taken out:"<<bitset<sizeof(tool) * 8>(tool) << endl;
			//�ж��Ӵ��Ƿ��Ѿ���⵽��
			x = tool >> 5;
			y = tool % 32;
			if (memo[x] & (1 << (31 - y)))//�Ѿ�����
				continue;
			//���������˵����û��
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
			//����һ��ȡ����С��Ϊ0λ
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