#include <cstdio>
#include <ctime>
#include <iostream>

int main() {
    srand(time(0));
    std::string x = "";
    int len = rand() % 20 + 1;
    for (int i = 0; i < len; i++)
        x += char(rand() % 26 + 'A');
    int K = rand() % 15;
    std::string y = x;
    for (int i = 0; i < K; i++) {
        if (rand() % 2) {
            std::string tmp = "A";
            y.insert(rand() % y.size(), tmp);
        }
        else {
            y.erase(rand() % y.size(), 1);
        }
    }
    std::cout << x.size() << " " << y.size() << " " << K << std::endl;
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    return 0;
}