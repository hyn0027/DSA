#include "sort.h"
#include <iostream>
const int maxl = 1000000;


inline void swap(int &a, int &b) {
	int t = a;
	a = b, b = t;
}

void my_sort(int* a, int l, int r) {
	if (r - l + 1 == 1)
		return;
	if (r - l + 1 == 2) {
		int min, max;
		compare(a[l], a[l + 1], a[l + 1], &max, &min);
		a[l] = min;
		a[l + 1] = max;
		return;
	}
	if (r - l + 1 == 3) {
		int min, max;
		compare(a[l], a[l + 1], a[l + 2], &max, &min);
		if (a[l + 1] == min)
			swap(a[l], a[l + 1]);
		else if (a[l + 2] == min)
			swap(a[l], a[l + 2]);
		if (a[l + 1] == max)
			swap(a[l + 2], a[l + 1]);
		else if (a[l] == max)
			swap(a[l], a[l + 2]);
		return;
	}
	int mid[4];
	mid[1] = (l + r) >> 1;
	mid[0] = (l + mid[1]) >> 1;
	mid[2] = (mid[1] + 1 + r) >> 1;
	my_sort(a, l, mid[0]);
	my_sort(a, mid[0] + 1, mid[1]);
	my_sort(a, mid[1] + 1, mid[2]);
	my_sort(a, mid[2] + 1, r);
	static int merge[maxl];
	int pt[4] = {l, mid[0] + 1, mid[1] + 1, mid[2] + 1}, all_pt = l;
	int n_r[4] =  {mid[0], mid[1], mid[2], r};
	int unuse = -1;
	int min, max;
	compare(a[pt[0]], a[pt[1]], a[pt[2]], &max, &min);
	if (a[pt[0]] == max)	unuse = 0;
	else if (a[pt[1]] == max)	unuse = 1;
	else	unuse = 2;
	while (pt[0] <= n_r[0] && pt[1] <= n_r[1] && pt[2] <= n_r[2] && pt[3] <= n_r[3]) {
		int c[4];
		for (int i = 0, ptr = 0; i < 4; i++) {
			if (unuse == i)	continue;
			c[ptr++] = a[pt[i]];
		}
		compare(c[0], c[1], c[2], &max, &min);
		for (int i = 0; i < 4; i++)
			if (a[pt[i]] == max) {
				unuse = i;
			}
		for (int i = 0; i < 4; i++)
			if (a[pt[i]] == min) {
				merge[all_pt++] = a[pt[i]++];
				break;
			}
	}
	for (int i = 0, cur_pt = 0; i < 4; i++) {
		if (pt[i] <= n_r[i]) {
			pt[cur_pt] = pt[i];
			n_r[cur_pt++] = n_r[i];
		}
	}
	while (pt[0] <= n_r[0] && pt[1] <= n_r[1] && pt[2] <= n_r[2]) {
		compare(a[pt[0]], a[pt[1]], a[pt[2]], &max, &min);
		for (int i = 0; i < 3; i++)
			if(a[pt[i]] == min) {
				merge[all_pt++] = a[pt[i]++];
				break;
			}
	}
	for (int i = 0, cur_pt = 0; i < 3; i++) {
		if (pt[i] <= n_r[i]) {
			pt[cur_pt] = pt[i];
			n_r[cur_pt++] = n_r[i];
		}
	}
	while (pt[0] <= n_r[0] && pt[1] <= n_r[1]) {
		compare(a[pt[0]], a[pt[1]], a[pt[1]], &max, &min);
		for (int i = 0; i < 2; i++)
			if(a[pt[i]] == min) {
				merge[all_pt++] = a[pt[i]++];
				break;
			}
	}
	for (int i = 0, cur_pt = 0; i < 2; i++) {
		if (pt[i] <= n_r[i]) {
			pt[cur_pt] = pt[i];
			n_r[cur_pt++] = n_r[i];
		}
	}
	while (pt[0] <= n_r[0])
		merge[all_pt++] = a[pt[0]++];
	for (int i = l; i <= r; i++) 
		a[i] = merge[i];
}

void sort(int n, int limit, int *a) {
	my_sort(a, 0, n - 1);
}
