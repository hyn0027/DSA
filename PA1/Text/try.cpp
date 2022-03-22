#include <cstdio>
#include <iostream>
#pragma pack(1)
struct A{
    int a;
    double x;
    char c;
}a[3];

int main() {
    std::cout << sizeof(A) << " " << sizeof(a) << std::endl;
    return 0;
}