#include "AHE.h"
#include <limits>
#include <stack>

void AdaptiveHuffmanTree::updateTree(uchar symbol)
{
    auto [i, j] = findNode(symbol);
    Node *cur_node = nullptr;
    if (i == -1)
    {
        createNode(symbol);
        cur_node = NYT->parent->parent;
    }
    else
    {
        cur_node = nodes[i][j];
    }

    // exchange first, then update
    while (cur_node != nullptr)
    {
        Node *max_node = getMaxNodeWithWeight(root, cur_node->weight);
        if (max_node != cur_node)
        {
            swapNodes(cur_node, max_node);
        }
        auto [i, j] = findNode(cur_node);
        nodes[i].erase(nodes[i].begin() + j);
        cur_node->weight++;
        nodes[cur_node->weight].push_back(cur_node);
        cur_node = cur_node->parent;
    }
}

Node *AdaptiveHuffmanTree::createNode(uchar symbol)
{
    Node *internal_node = new Node;
    internal_node->parent = NYT->parent;
    internal_node->left = NYT;
    NYT->parent = internal_node;
    NYT->index -= 2;
    internal_node->weight = 1;
    internal_node->index = NYT->index;

    Node *leaf_node = new Node;
    leaf_node->weight = 1;
    leaf_node->index = NYT->index - 1;
    leaf_node->parent = internal_node;
    leaf_node->left = nullptr;
    leaf_node->right = nullptr;
    internal_node->right = leaf_node;

    return leaf_node;
}

std::pair<int, int> AdaptiveHuffmanTree::findNode(uchar symbol)
{
    for (size_t i = 0; i < nodes.size(); i++)
    {
        for (size_t j = 0; j < nodes[i].size(); j++)
        {
            if (nodes[i][j]->symbol == symbol)
            {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

std::pair<int, int> AdaptiveHuffmanTree::findNode(Node *node)
{
    if (node == nullptr)
    {
        return {-1, -1};
    }
    for (size_t i = 0; i < nodes.size(); i++)
    {
        for (size_t j = 0; j < nodes[i].size(); j++)
        {
            if (nodes[i][j] == node)
            {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

void AdaptiveHuffmanTree::swapNodes(Node *node1, Node *node2)
{
    Node *temp = node1->parent;
    size_t temp_index = node1->index;
    if (node2->parent->left == node2)
    {
        node2->parent->left = node1;
    }
    else
    {
        node2->parent->right = node1;
    }

    if (node1->parent->left == node1)
    {
        node1->parent->left = node2;
    }
    else
    {
        node1->parent->right = node2;
    }
    node1->parent = node2->parent;
    node1->index = node2->index;
    node2->parent = temp;
    node2->index = temp_index;
}

AdaptiveHuffmanTree::AdaptiveHuffmanTree() : root(nullptr), NYT(nullptr)
{
    nodes.resize(1);
    NYT = new Node;
    NYT->weight = 0;
    NYT->index = std::numeric_limits<uchar>::max();
    NYT->parent = nullptr;
    NYT->left = nullptr;
    NYT->right = nullptr;
    root = NYT;
}

Node *AdaptiveHuffmanTree::getMaxNodeWithWeight(Node *startNode, int weight)
{
    Node *maxNode = nullptr;

    std::stack<Node *> stack;
    stack.push(startNode);

    while (!stack.empty())
    {
        Node *node = stack.top();
        stack.pop();

        if (node->weight == weight)
        {
            if (maxNode == nullptr || node->index > maxNode->index)
            {
                maxNode = node;
            }
        }

        if (node->left != nullptr)
        {
            stack.push(node->left);
        }
        if (node->right != nullptr)
        {
            stack.push(node->right);
        }
    }

    return maxNode;
}

AdaptiveHuffmanTree::~AdaptiveHuffmanTree()
{
    std::stack<Node *> stack;
    stack.push(root);

    while (!stack.empty())
    {
        Node *node = stack.top();
        stack.pop();

        if (node->left != nullptr)
        {
            stack.push(node->left);
        }
        if (node->right != nullptr)
        {
            stack.push(node->right);
        }

        delete node;
        node = nullptr;
    }
}
