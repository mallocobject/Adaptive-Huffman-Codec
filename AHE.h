#pragma once

#include <vector>

using uchar = unsigned char;
using size_t = std::size_t;

struct Node
{
    size_t weight; // frequency of the symbol
    uchar index;   // index of the node in the tree
    uchar symbol;  // symbol of the node
    Node *parent;
    Node *left;
    Node *right;
};

class AdaptiveHuffmanTree
{
private:
    Node *root;
    Node *NYT;
    std::vector<std::vector<Node *>> nodes;
    void updateTree(uchar symbol);
    Node *createNode(uchar symbol);
    std::pair<int, int> findNode(uchar symbol);
    std::pair<int, int> findNode(Node *node);
    void swapNodes(Node *node1, Node *node2);
    Node *AdaptiveHuffmanTree::getMaxNodeWithWeight(Node *startNode, int weight);

public:
    AdaptiveHuffmanTree(/* args */);
    ~AdaptiveHuffmanTree();
};
