#include <cstdio>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstring>

const int maxl = 1000;

const int small_dataset = 40000;
const int large_dataset = 500000;
int dataset = small_dataset;
double p_insert = 1, p_query = 0;
char read[maxl];
char str[large_dataset][100];
int str_cnt;


inline void write(int w) {
    if (w == 0) {
        putchar('0');
        putchar('\n');
        return;
    }
    if (w < 0) {
        putchar('-');
        w = -w;
    }
    char my_out[20];
    unsigned short pt = 0;
    while (w) {
        my_out[pt++] = w % 10 + '0';
        w /= 10;
    }

    for (int i = pt - 1; i >= 0; i--) 
        putchar(my_out[i]);
    putchar('\n');
}

int main(int argc, char*argv[]) {
    srand(time(0));
    FILE* f;
    if (argv[1][0] == '0')
        f = fopen("./poj.txt", "r");
    else
        f = fopen("./hdu.txt", "r");
    if (argv[2][0] == '0') {//小数据 随机数据 插入查询五五开
        dataset = small_dataset;
        p_insert = 0.5;
        p_query = 0.5;
    }
    else if (argv[2][0] == '1') {//大数据 随机数据 插入查询五五开
        dataset = large_dataset;
        p_insert = 0.5;
        p_query = 0.5;
    }
    else {//规模为第一种的一半 随机数据 全插入
        dataset = small_dataset / 2;
        p_insert = 1;
        p_query = 0;
    }
    char output[200];
    while (dataset--) {
        if (rand() % 100 < p_insert * 100) { //insert
            printf("0 ");
            fgets(read, maxl, f);
            int l = strlen(read), pt1 = 0, pt2 = 0;
            while (read[pt1] != ' ')
                pt1++;
            pt1++;
            while (read[pt1] != ' ') {
                str[str_cnt][pt2] = read[pt1];
                output[pt2++] = read[pt1++];
            }
            str[str_cnt][pt2] = 0;
            str_cnt++;
            output[pt2++] = read[pt1++];
            while (read[pt1] != ' ')
                output[pt2++] = read[pt1++];
            output[pt2] = 0;
            printf("%s\n", output);
        }
        else {//query //所有查询有一半概率是原有的串 一半概率是随机生成的串
            if (str_cnt != 0) {
                int od = rand() % str_cnt;
                printf("1 %s\n", str[od]);
            }
            else {
                int l = rand() % 10 + 1;
                printf("1 ");
                while (l--) 
                    printf("%c", rand() % 94 + 33);
                printf("\n");
            }
        }
    }
    printf("2\n");
    return 0;
}