
#include <iostream>

extern "C" {
    void test() {
        std::cout << "Hello, world!" << std::endl;
    }
}