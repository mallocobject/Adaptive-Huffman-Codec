#include "AHE.h"
#include <iostream>
#include <chrono>
#include <random>
#include "utils.h"

int main()
{
    // std::cout << '?' << std::endl;
    AHE ahe;
    // char c = 31;
    // std::cout << c << std::endl;
    // ahe.encode("?aabbbacc");

    // "\0\a\b\t\n\v\f\r\"\'\\?"
    // ahe.encode(R"(\0\a\b\t\n\v\f\r\"\'\\?)");

    // 生成随机字符串(for test only)
    for (int i = 0; i < 1; i++)
    {
        std::string input;
        for (int j = 0; j < 10; j++)
        {
            char ch = utils::generateRandomNumber(0, 127); // generate 0-127 ASCII characters

            // avoid control characters
            while (ch <= 31 || ch == 127)
            {
                ch = utils::generateRandomNumber(0, 127);
            }
            input += ch;
        }
        ahe.encode(input);
    }
    // std::cout << "input: " << input << std::endl;
    // std::cout << "output: ";
    // ahe.encode(input);
    // ahe.encode("aabbbacc");
    // std::cout << "Please input a string: ";
    // std::string input;
    // std::getline(std::cin, input);
    // ahe.encode(input);
    system("pause");
    return 0;
}