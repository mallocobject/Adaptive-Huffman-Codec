#pragma once

#include <unordered_map>
#include <string>

using uint = unsigned int;
#define NYT_SYMBOL -1

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
    void encode(const char *input);
    void update(char symbol);
    // void decode(const char *input, const char *output);
    Node *getMaxIndexNode(uint frequency);
    void swapNode(Node *node1, Node *node2);
    void updateCodetable(Node *node, const std::string &code);

private:
    Node *root;
    Node *NYT;
    std::unordered_map<char, std::string> code_table;
    void deleteTree(Node *node);
};
