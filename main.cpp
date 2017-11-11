#include <iostream>
#include "Map.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Map a(39, 39);
    a.generate(6, 15, 15);
    a.print_map();
    std::cout<<std::endl<<std::endl;
    a.add_maze();
    a.print_map();
    return 0;
}