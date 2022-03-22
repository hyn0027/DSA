#include <cstdio>
#include "hashtable.h"

int main(int argc, char*argv[]) {
    int type;
    char buffer[1000];
    int data;
    int table_sz = TABLE_SIZE;
    hashing_strategy* h;
    collision_strategy* c;
    if (argv[1][0] == '0') 
        h = new naive_hashing();
    else if (argv[1][0] == '1')
        h = new ascii_hashing();
    else
        h = new utf8_hashing();
    if (argv[2][0] == '0')
        c = new linear_probe();
    else if (argv[2][0] == '1')
        c = new bilateral_square();
    else
        c = new public_overflow_area();
    hashtable table(table_sz, h, c);
    while (true) {
        scanf("%d", &type);
        if (type == 0) {
            scanf("%s", buffer);
            scanf("%d", &data);
            table.insert(hash_entry(buffer, data));
        }
        else if (type == 1) {
            scanf("%s",buffer);
            printf("%d\n", table.query(buffer));
        }
        else
            break;
    }
    return 0;
}