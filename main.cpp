#include "AHC.h"
#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include "utils.h"

int main()
{
    // std::cout << '?' << std::endl;
    AHC ahe;
    // char c = 31;
    // std::cout << c << std::endl;
    // ahe.encode("?aabbbacc");

    // "\0\a\b\t\n\v\f\r\"\'\\?"
    // ahe.encode(R"(\0\a\b\t\n\v\f\r\"\'\\?)");

    // 生成随机字符串(for test only)
    int cnt = 0;
    for (int i = 0; i < 1000; i++)
    {
        std::string input;
        for (int j = 0; j < 100; j++)
        {
            input += utils::generateRandomNumber(31, 126); // 31-126
        }
        // std::string ret = ahe.decode(ahe.encode(input));
        std::string encode_ret = ahe.encode(input);
        // std::cout << "encode_ret: " << encode_ret << std::endl;
        std::string decode_ret = ahe.decode(encode_ret);
        if (input != decode_ret)
        {
            std::cout << "input: " << input << std::endl;
            std::cout << "decode_ret: " << decode_ret << std::endl;
            cnt++;
        }
        else
        {
            std::cout << "encode and decode successfully!" << std::endl;
        }
    }
    std::cout << "cnt: " << cnt << std::endl;
    // std::cout << "input: " << input << std::endl;
    // std::cout << "output: ";
    // ahe.encode(input);
    // ahe.encode("aabbbacc");
    // std::string encode_ret = ahe.encode("aabbbacc");
    // std::cout << "encode_ret: " << encode_ret << std::endl;
    // std::string decode_ret = ahe.decode(encode_ret);
    // std::cout << "Please input a string: ";
    // std::string input;
    // std::getline(std::cin, input);
    // ahe.encode(input);
    system("pause");
    return 0;
}