#include "hashtable.h"
#include <cstring>

int naive_hashing::operator()(char* str, int N){
    if(str == NULL) return 0;
    else return (str[0]+N)%N;
}

int ascii_hashing::operator()(char* str, int N) {
    int l = strlen(str);
    long long ret = 0;
    for (int i = 0; i < l; i++) {
        ret = (((ret << 7) | (ret >> 16)) + (long long)str[i]) % N;
    }
    ret = (ret + N) % N;
    return ret;
}

char* utf8_hashing::get_utf8_code(int x) {
    static char ret[10];
    if (x >= 0) {
        for (int i = 7; i >= 0; i--)
            ret[7 - i] = '0' + ((x >> i) & 0x1);
    }
    else {
        x = -x;
        int s[10];
        for (int i = 0; i < 8; i++)
            s[i] = ((x >> i) & 0x1) ^ 0x1;
        s[0]++;
        for (int i = 0; i < 8; i++) {
            s[i + 1] += s[i] >> 1;
            s[i] &= 0x01; 
        }
        for (int i = 7; i >= 0; i--)
            ret[7 - i] = s[i] + '0';
    }
    return ret;
}

int utf8_hashing::operator()(char* str, int N) {
    char* tmp;
    char cur[40];
    int len, code, l = strlen(str);
    long long ret = 0;
    for (int i = 0; i < l; i++) {
        tmp = get_utf8_code(str[i]);
        if (tmp[0] == '0')  len = 1;
        else if (tmp[2] == '0') len = 2;
        else len = 3;
        for (int j = 0; j < 8; j++)
            cur[j] = tmp[j];
        for (int j = 1; j < len; j++) {
            i++;
            tmp = get_utf8_code(str[i]);
            for (int k = 0; k < 8; k++)
                cur[k + j * 8] = tmp[k];
        }
        code = 0;
        for (int i = 0; i < (len << 3); i++) {
            code = (code << 1) | (cur[i] - '0');
            code <<= 2;
        }
        if (len == 2) {
            code = code & ((1 << 13) - 1);
            code = (code & ((1 << 6) - 1)) | ((code >> 8) << 6);
            code = (code << 2) | 2;
        }
        if (len == 3) {
            code = code & ((1 << 20) - 1);
            code = (code & ((1 << 6) - 1)) | ((code >> 8) << 6);
            code = (code & ((1 << 12) - 1)) | ((code >> 14) << 12);
            code = (code << 1) | 1;
        }
        ret = (((ret << 16) | (ret >> 7)) + code) % N;
    }
    return ret;
}

int linear_probe::operator()(hash_entry* Table, int table_size, int last_choice){
    return (last_choice + 1) % table_size;
}

void linear_probe::init(){
    return;// do nothing
}

int bilateral_square::operator()(hash_entry* Table, int table_size, int last_choice) {
    int ret = ((last_choice + bias(idx + 1, table_size) - bias(idx, table_size)) % table_size + table_size) % table_size;
    idx++;
    return ret;
}

void bilateral_square::init() {
    idx = 0;
}

int bilateral_square::bias(int x, int table_size) {
    if (x & 1)
        return (long long)(x / 2 + 1) * (x / 2 + 1) % table_size;
    else
        return -(long long)(x / 2) * (x / 2) % table_size;
}

int public_overflow_area::operator()(hash_entry* Table, int table_size, int last_choice) {
    if (last_choice < overflow_hash_size)   return overflow_hash_size;
    return last_choice + 1;
}

void public_overflow_area::init() {
    return;
}