#include "AHC.h"
#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include <fstream>
#include <thread>
#include <windows.h>
#include "utils.h"

void read2files(int index, int start, int end)
{
    std::string filename = "../output/output_" + std::to_string(index) + ".txt";
    std::ofstream out(filename);
    for (int k = start; k <= end; k++)
    {
        for (int i = 1; i <= 1000; i++)
        {
            AHC ahc;
            std::string input = "";
            for (int j = 0; j < i; j++)
            {
                input += (char)utils::generateRandomNumber(31, 31 + k); // 31-126
            }
            std::string encode_ret = ahc.encode(input);
            out << 7 * input.size() << "," << encode_ret.size() << std::endl;
        }
    }
    out.close();
}

int main()
{
    // std::vector<std::thread> threads;
    // int index = 0;
    // for (int i = 0; i < 90; i += 10)
    // {
    //     threads.emplace_back(std::thread(read2files, index, i, i + 9));
    //     index++;
    // }

    // for (auto &t : threads)
    // {
    //     t.join();
    // }

    AHC ahc;
    std::string input = "";
    std::cout << "Please input a string: ";
    std::getline(std::cin, input);
    std::string encode_ret = ahc.encode(input);
    std::cout << "encode: " << encode_ret << std::endl;

    // int msgboxID = MessageBoxA(
    //     NULL,
    //     "Do you want to decode?",
    //     "Decode Confirmation",
    //     MB_ICONQUESTION | MB_YESNO);

    // if (msgboxID == IDYES)
    // {
    //     std::string decode_ret = ahc.decode(encode_ret);
    //     std::cout << "decode: " << decode_ret << std::endl;
    // }

    std::string decode_ret = ahc.decode(encode_ret);
    std::cout << "decode: " << decode_ret << std::endl;

    system("pause");
    return 0;
}