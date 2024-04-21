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

// 递归删除树
void AHE::deleteTree(Node *node)
{
    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
    node = nullptr;
}

// 编码入口
void AHE::encode(const std::string &input)
{
    std::string ret = "";
    for (const char symbol : input)
    {
        if (code_table.find(symbol) != code_table.end())
        {
            ret += vectorBool2String(code_table[symbol]);
        }
        else
        {
            std::string code = vectorBool2String(code_table[NYT_SYMBOL]);

            // 7 bits standard ASCII code
            for (int j = 6; j >= 0; j--)
            {
                code += ((symbol >> j) & 1) ? '1' : '0';
            }
            ret += code;
        }
        ret += ' '; // split each code with a space
        update(symbol);
    }

    std::cout << ret << std::endl;
}

// 动态调整树结构，保持树的平衡
void AHE::update(const char symbol)
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
                node = code_table[symbol][i] == false ? node->left : node->right;
            }
        }

        // 判断该叶子节点是否需要交换
        Node *cur_node = node;
        while (cur_node != nullptr)
        {
            Node *max_node = getMaxIndexNode(cur_node);
            // max_node 不可能为根节点 root
            if (cur_node != max_node)
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

        // 判断该子树的父节点是否需要交换
        node = NYT->parent->parent;

        Node *cur_node = node;
        while (cur_node != nullptr)
        {
            Node *max_node = getMaxIndexNode(cur_node);
            if (cur_node != max_node)
            {
                swapNode(cur_node, max_node);
            }
            cur_node->frequency++;
            cur_node = cur_node->parent;
        }
    }
    std::vector<bool> code;
    updateCodetable(root, code); // 更新编码表
}

// 将 vector<bool> 转换为 string
std::string AHE::vectorBool2String(const std::vector<bool> &v)
{
    std::string res;
    res.reserve(v.size()); // forward allocate memory
    for (bool b : v)
    {
        res += b ? '1' : '0';
    }
    return res;
}

// BFS (广度优先搜索)
// 根， 右， 左
// 保证权重相同的节点中位置最高的节点优先遍历
// 获取的节点不与 node 有祖先关系
Node *AHE::getMaxIndexNode(Node *node)
{
    std::queue<Node *> q;
    q.push(root);
    Node *max_node = nullptr;
    while (!q.empty())
    {
        Node *cur_node = q.front();
        q.pop();

        // 如果当前节点的频率等于 frequency，且不是 node 的祖先节点(即不与 node 有父子关系)
        if (cur_node->frequency == node->frequency && cur_node != node->parent)
        {
            max_node = cur_node; // 更新 max_node
            break;               // 跳出循环
        }

        // 如果当前节点的频率小于 frequency，说明改节点的子树的频率也小于 frequency，不需要再遍历
        else if (cur_node->frequency < node->frequency)
        {
            continue;
        }
        // 递归遍历左右子树，优先遍历右子树
        if (cur_node->right)
        {
            q.push(cur_node->right);
        }
        if (cur_node->left)
        {
            q.push(cur_node->left);
        }
    }
    return max_node;
}

// 交换两个节点(节点父指针，并更新各自父指针的对应子树指针)
void AHE::swapNode(Node *node1, Node *node2)
{
    // 由于 node1 和 node2 不可能是 root 节点，所以不需要判断 nodeX->parent 是否为 nullptr
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

    std::swap(node1->parent, node2->parent); // 交换父指针
}

// 更新编码表
void AHE::updateCodetable(Node *node, std::vector<bool> &code)
{
    if (node->isLeaf())
    {
        code_table[node->symbol] = code;
        return;
    }
    if (node->left)
    {
        code.push_back(false);
        updateCodetable(node->left, code); // 左子树编码为0
        code.pop_back();
    }
    if (node->right)
    {
        code.push_back(true);
        updateCodetable(node->right, code); // 右子树编码为1
        code.pop_back();
    }
}
