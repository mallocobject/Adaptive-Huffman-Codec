#include "AHE.h"

#include <iostream>
#include <queue>

AHE::AHE()
{
    root = new Node(-1, 0);
    NYT = root;
    code_table.clear();
    // code_table[NYT_SYMBOL] = "";
    // for (int i = 0; i < 128; i++)
    // {
    //     std::string code = "";
    //     for (int j = 6; j >= 0; j--)
    //     {
    //         code += ((i >> j) & 1) ? '1' : '0';
    //     }
    //     code_table[i] = code;
    // }
}

AHE::~AHE()
{
    deleteTree(root);
}

void AHE::deleteTree(Node *node)
{
    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

void AHE::encode(const char *input)
{
    std::string ret = "";
    for (const char *p = input; *p; p++)
    {
        char symbol = *p;
        if (code_table.find(symbol) != code_table.end())
        {
            ret += code_table[symbol];
        }
        else
        {
            std::string code = code_table[NYT_SYMBOL];
            for (int j = 6; j >= 0; j--)
            {
                code += ((symbol >> j) & 1) ? '1' : '0';
            }
            ret += code;
        }
        ret += ' ';
        update(symbol);
    }

    std::cout << ret << std::endl;
}

void AHE::update(char symbol)
{
    // std::cout << "Hello, World!" << std::endl;
    Node *node = nullptr;
    if (code_table.find(symbol) != code_table.end())
    {
        node = root;
        while (!node->isLeaf())
        {
            for (int i = 0; i < code_table[symbol].size(); i++)
            {
                node = code_table[symbol][i] == '0' ? node->left : node->right;
            }
        }
        Node *cur_node = node;
        while (cur_node != nullptr)
        {
            Node *max_node = getMaxIndexNode(cur_node->frequency);
            if (max_node != nullptr && cur_node != max_node)
            {
                swapNode(cur_node, max_node);
            }
            cur_node->frequency++;
            cur_node = cur_node->parent;
        }
    }
    else
    {
        Node *new_node = new Node(symbol, 1, nullptr, nullptr, NYT);
        NYT->right = new_node;
        NYT->left = new Node(NYT_SYMBOL, 0, nullptr, nullptr, NYT);
        NYT = NYT->left;

        new_node->parent->frequency++;

        // code_table[symbol] = code_table[NYT_SYMBOL] + code_table[symbol];
        // code_table[NYT_SYMBOL] += '0';
        // 判断该子树的父节点是否需要交换
        node = NYT->parent->parent;

        Node *cur_node = node;
        while (cur_node != nullptr)
        {
            Node *max_node = getMaxIndexNode(cur_node->frequency);
            if (max_node != nullptr && cur_node != max_node)
            {
                swapNode(cur_node, max_node);
            }
            cur_node->frequency++;
            cur_node = cur_node->parent;
        }
    }

    updateCodetable(root, ""); // 更新编码表
}

Node *AHE::getMaxIndexNode(uint frequency)
{
    std::queue<Node *> q;
    q.push(root);
    Node *max_node = nullptr;
    while (!q.empty())
    {
        Node *node = q.front();
        q.pop();
        if (node->frequency == frequency)
        {
            max_node = node; // 更新 max_node
            break;           // 跳出循环
        }
        else if (node->frequency < frequency)
        {
            continue;
        }
        if (node->right)
        {
            q.push(node->right);
        }
        if (node->left)
        {
            q.push(node->left);
        }
    }
    return max_node;
}

void AHE::swapNode(Node *node1, Node *node2)
{
    bool isLeft = node2->parent->left == node2;

    if (node1->parent->left == node1)
    {
        node1->parent->left = node2;
    }
    else
    {
        node1->parent->right = node2;
    }

    if (isLeft)
    {
        node2->parent->left = node1;
    }
    else
    {
        node2->parent->right = node1;
    }

    std::swap(node1->parent, node2->parent);
}

void AHE::updateCodetable(Node *node, const std::string &code)
{
    if (node->isLeaf())
    {
        code_table[node->symbol] = code;
        return;
    }
    if (node->left)
    {
        updateCodetable(node->left, code + '0'); // 左子树编码为0
    }
    if (node->right)
    {
        updateCodetable(node->right, code + '1'); // 右子树编码为1
    }
}
