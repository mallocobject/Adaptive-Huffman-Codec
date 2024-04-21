#include "AHE.h"
#include <iostream>
// #include <sstream>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    AHE ahe;
    // ahe.encode("Hello, World!");
    std::cout << "Please input a string: ";
    std::string input;
    std::getline(std::cin, input);
    ahe.encode(input);
    return 0;
}