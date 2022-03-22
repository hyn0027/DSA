#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

unsigned int input[524290];
unsigned int bitmap[524290];

int main() {
    //将输入以bitmap格式存储进input数组
    char c;
    int flag = 0;
    while ((c=getchar()) != '\n') {
        input[flag>>5] = ((c-'0')<<(31-(flag&31))) | input[flag>>5]; 
        flag++; 
    }
    // if (flag != 0) {
    //     char tmp[33];
    //     for (int i = 0; i < flag; i++) {
    //         tmp[i] = temp[i];
    //     }
    //     input[flag2] = strtol(tmp, NULL, 2);
    //     input[flag2] = input[flag2] << (32-flag);
    //     flag2++;
    // }
    

    // cout << flag << endl;

    // for (int i = 0; i < flag>>5; i++) {
    //     cout << input[i] << endl;
    // }

    // clock_t start,end;//定义clock_t变量
    // start = clock();
    int m = 1;
    bool find = false;
    int count = 0;
    int ans = 0;
    // memset(bitmap, 0, (1<<19));
    //对m长度的字符串使用bitmap进行枚举
    while (m <= 24 && !find) {
        cout << m << endl;
        count = 1;
        int all = 1<<m;
        // cout << "all " << all << endl;
        int cur = input[0] >> (32-m);
        // cout << cur << endl;
        int point;
        bitmap[cur>>5] = 1<<(31-(cur&31));
        for (int i = m; i < flag; i++) {
            point = ((input[i>>5] >> (31-(i&31)))&1);
            cur = (cur<<1 & ((1<<m)-1)) | point;
            // cout << point << endl;
            // cout << "cur " << cur << endl;
            unsigned int judge = (1<<(31-(cur&31))) | bitmap[cur>>5];
            if (judge != bitmap[cur>>5]) {
                count++;
                bitmap[cur>>5] = judge;
            }
            if (count == all) {
                // cout << "break" << endl;
                break;
            }
        }

        //若m长度的字符串均已出现，则继续验证m+1长度的字符串
        if (count == all) {
            memset(bitmap, 0, (all>>5)+1);
            m++;
        }
        else {
            // if (m>5) {
            //     for (int i = 0; i < 1<<(m-5); i++) {
            //     if (bitmap[i]!= 4294967296){
            //         for (int j = 0; j < 32; j++) {
            //             if (((bitmap[i]>>(31-(j&31)))&1) == 0) {
            //                 ans = (i<<5) + j;
            //                 find = true;
            //                 break;
            //             }
            //         }
            //         break;
            //     }
            // }
            // }
            // else {
            for (int i = 0; i < all; i++) {
                if (((bitmap[i>>5]>>(31-(i&31)))&1) == 0) {
                    ans = i;
                    find = true;
                    break;
                }
            }
            // }

        }
        // cout << "ans " << ans << endl;
    }

    for (int i = 0; i < m; i++)
        cout << ((ans>>(m-1-i)) &1);
    cout << endl;

    // end = clock();   //结束时间
    // cerr <<"time = " << double(end-start) << "ms" << endl; 

    return 0;
}