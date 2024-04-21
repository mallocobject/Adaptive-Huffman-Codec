#pragma once

#include <unordered_map>
#include <string>
#include <vector>

using uint = unsigned int;
#define NYT_SYMBOL -1 // Not Yet Transmitted

struct Node
{
    char symbol;
    uint frequency;
    Node *left;
    Node *right;
    Node *parent;
    Node() : symbol(0), frequency(0), left(nullptr), right(nullptr), parent(nullptr) {}
    Node(char symbol, uint frequency) : symbol(symbol), frequency(frequency), left(nullptr), right(nullptr), parent(nullptr) {}
    Node(char symbol, uint frequency, Node *left, Node *right) : symbol(symbol), frequency(frequency), left(left), right(right), parent(nullptr) {}
    Node(char symbol, uint frequency, Node *left, Node *right, Node *parent) : symbol(symbol), frequency(frequency), left(left), right(right), parent(parent) {}
    bool isLeaf() const { return left == nullptr && right == nullptr; }
};

class AHE
{
public:
    AHE();
    ~AHE();
    void encode(const std::string &input);
    // void decode(const char *input);
private:
    void update(const char symbol);
    std::string vectorBool2String(const std::vector<bool> &v);
    Node *getMaxIndexNode(Node *node);
    void swapNode(Node *node1, Node *node2);
    void updateCodetable(Node *node, std::vector<bool> &code);
    void deleteTree(Node *node);

private:
    Node *root;
    Node *NYT;
    // std::unordered_map<char, std::string> code_table;
    std::unordered_map<char, std::vector<bool>> code_table;
};
