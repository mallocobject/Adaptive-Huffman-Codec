#include "AHE.h"
#include <iostream>
#include <chrono>
#include <random>

// 生成[min, max]范围内的随机数
int generateRandomNumber(int min, int max)
{
    // 使用当前时间作为种子
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 gen(seed);                    // 生成器
    std::uniform_int_distribution<int> dis(min, max); // 均匀分布
    return dis(gen);                                  // 返回生成的随机数
}

int main()
{
    std::cout << "Hello, World!" << std::endl;
    AHE ahe;

    // 生成随机字符串(for test only)
    for (int i = 0; i < 10000; i++)
    {
        std::string input;
        for (int j = 0; j < 100; j++)
        {
            input += (char)generateRandomNumber(0, 127);
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
    return 0;
}