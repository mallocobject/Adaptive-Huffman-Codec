#include "AHC.h"

#include <iostream>
#include <queue>
#include <sstream>
#include <algorithm>
#include "terminal.h"

AHC::AHC()
{
    initEncodeTree();
    initDecodeTree();
}

AHC::~AHC()
{
    deleteTree(encode_root);
    deleteTree(decode_root);
}

void AHC::initEncodeTree()
{
    encode_root = new Node(-1, 0);
    encode_NYT = encode_root;
}

void AHC::initDecodeTree()
{
    decode_root = new Node(-1, 0);
    decode_NYT = decode_root;
}

// 递归删除树
void AHC::deleteTree(Node *node)
{
    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
    node = nullptr;
}

// 1 ~ 3999
std::string AHC::int2Roman(int num)
{
    std::vector<std::pair<int, std::string>> roman = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}};

    std::string result;
    for (auto &value : roman)
    {
        while (num >= value.first)
        {
            num -= value.first;
            result += value.second;
        }
    }
    return result;
}

// void AHC::printEscape_char(char ch, std::stringstream &ss)
// {
//     switch (ch)
//     {
//     case '\0':
//         ss << "'\\0', ";
//         break;
//     case '\a':
//         ss << "'\\a', ";
//         break;
//     case '\b':
//         ss << "'\\b', ";
//         break;
//     case '\t':
//         ss << "'\\t', ";
//         break;
//     case '\n':
//         ss << "'\\n', ";
//         break;
//     case '\v':
//         ss << "'\\v', ";
//         break;
//     case '\f':
//         ss << "'\\f', ";
//         break;
//     case '\r':
//         ss << "'\\r', ";
//         break;
//     case '\"':
//         ss << "'\\\"', ";
//         break;
//     case '\'':
//         ss << "'\\'', ";
//         break;
//     case '\\':
//         ss << "'\\\\', ";
//         break;
//     case '\?':
//         ss << "'\\?', ";
//         break;

//     default:
//         ss << ch << ", ";
//         break;
//     }
// }

// show tree structure
void AHC::showTree()
{
    static int index = 0;

    if (encode_root == nullptr)
        return;
    std::queue<Node *> q;
    q.push(encode_root);
    int depth = 0;
    while (!q.empty())
    {
        int level_size = q.size();
        std::stringstream ss;
        ss << "[" << index << " - " << depth++ << "]: ";

        for (int i = 0; i < level_size; i++)
        {
            Node *cur_node = q.front();
            q.pop();

            if (!cur_node)
                ss << "null, ";

            else
            {
                if (cur_node->symbol == -1)
                {
                    if (cur_node->isLeaf())
                        ss << "NYT, ";
                    else
                        ss << int2Roman(cur_node->frequency) << ", ";
                }
                else
                    // printEscape_char(cur_node->symbol, ss);
                    ss << cur_node->symbol << ", ";

                if (cur_node->left)
                    q.push(cur_node->left);
                else
                    q.push(nullptr);

                if (cur_node->right)
                    q.push(cur_node->right);
                else
                    q.push(nullptr);
            }
        }

        std::string line = ss.str();
        line = line.substr(0, line.size() - 2);
        terminal::setColor(terminal::Color::Yellow);
        std::cout << line << std::endl;
        terminal::setColor(terminal::Color::Green);
        std::cout << std::string(line.size(), '-') << std::endl;
    }

    index++;
}

Node *AHC::findSymbol(Node *node, char symbol, std::string &code)
{
    if (node == nullptr)
        return nullptr;
    else if (node->isLeaf() && node->symbol == symbol)
        return node;
    else
    {
        Node *foundNode = findSymbol(node->left, symbol, code);
        if (foundNode != nullptr)
        {
            code += '0';
            return foundNode;
        }

        foundNode = findSymbol(node->right, symbol, code);
        if (foundNode != nullptr)
        {
            code += '1';
            return foundNode;
        }
    }
    return nullptr;
}

Node *AHC::findCode(Node *node, const std::string &code, int &depth)
{
    if (node == nullptr)
        return nullptr;
    else if (node->isLeaf())
        return node;
    else
    {
        depth++;
        if (code[0] == '0')
            return findCode(node->left, code.substr(1), depth);
        else
            return findCode(node->right, code.substr(1), depth);
    }
    return nullptr;
}

// void AHC::printTree(Node *node, int depth)
// {
//     if (node == nullptr)
//         return;
//     printTree(node->left, depth + 1);

//     terminal::setCursor(depth * 2 + 1, 1);
//     if (node->symbol == -1)
//     {
//         if (node->isLeaf())
//         {
//             terminal::setColor(terminal::Color::LightGrey, false);
//             std::cout << " " << std::endl;
//         }
//         else
//         {
//             terminal::setColor(terminal::Color::LightYellow);
//             std::cout << node->frequency << std::endl;
//         }
//     }
//     else
//     {
//         terminal::setColor(terminal::Color::Green);
//         std::cout << node->symbol << std::endl;
//     }
//     terminal::setCursor(depth * 2, 2);

//     printTree(node->right, depth + 1);
// }

// 编码入口
std::string AHC::encode(const std::string &input)
{
    // terminal::setCursor(1, 1);
    // system("cls"); // clear screen

    std::string ret = "";
    for (const char symbol : input)
    {
        // if (code_table.find(symbol) != code_table.end())
        //     ret += vectorBool2String(code_table[symbol]);

        // bool isFind = false;
        std::string code = "";
        Node *isFind = findSymbol(encode_root, symbol, code);
        if (isFind != nullptr)
        {
            std::reverse(code.begin(), code.end());
            ret += code;
            // isFind = true;
        }
        else
        {
            // std::string code = vectorBool2String(code_table[NYT_SYMBOL]);
            std::string code = "";
            findSymbol(encode_root, NYT_SYMBOL, code);
            std::reverse(code.begin(), code.end());

            // 7 bits standard ASCII code
            for (int j = 6; j >= 0; j--)
            {
                code += ((symbol >> j) & 1) ? '1' : '0';
            }
            ret += code;
        }

        ret += ' '; // split each code with a space

        // showTree(); // show tree structure

        // terminal::setCursor(1, 1);
        // printTree(root);
        // terminal::reset();

        update(symbol, isFind, true);
    }

    // showTree(); // show the final tree structure
    terminal::reset();

    // std::cout << input << "->" << input.size() << std::endl;
    // std::cout << ret << std::endl;

    // remove all spaces
    ret.erase(std::remove(ret.begin(), ret.end(), ' '), ret.end());
    return ret;
}

std::string AHC::decode(std::string input)
{
    std::string ret = "";
    while (!input.empty())
    {
        int depth = 0;
        Node *node = findCode(decode_root, input, depth);
        if (node->symbol == NYT_SYMBOL)
        {
            input = input.substr(depth); // remove the code of NYT_SYMBOL from input
            char symbol = 0;
            for (int i = 0; i < 7; i++)
            {
                symbol = (symbol << 1) + (input[i] - '0');
            }
            ret += symbol;
            input = input.substr(7);
            update(symbol, nullptr, false);
        }
        else
        {
            ret += node->symbol;
            update(node->symbol, node, false);
            input = input.substr(depth);
        }
    }

    // std::cout << ret << std::endl;
    return ret;
}

// 动态调整树结构，保持树的平衡
void AHC::update(const char symbol, Node *isFind, bool isEncode)
{
    // std::cout << "Hello, World!" << std::endl;
    Node *node = nullptr;
    if (isFind)
    {
        node = isFind;

        // 判断该叶子节点是否需要交换
        Node *cur_node = node;
        while (cur_node != nullptr)
        {
            Node *max_node = getMaxIndexNode(cur_node, isEncode);
            // max_node 不可能为根节点 root
            if (cur_node != max_node)
                swapNode(cur_node, max_node);

            cur_node->frequency++;
            cur_node = cur_node->parent;
        }
    }
    else
    {
        Node *NYT = nullptr;
        if (isEncode)
            NYT = encode_NYT;
        else
            NYT = decode_NYT;
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
            Node *max_node = getMaxIndexNode(cur_node, isEncode);
            if (cur_node != max_node)
                swapNode(cur_node, max_node);

            cur_node->frequency++;
            cur_node = cur_node->parent;
        }
    }
    // std::vector<bool> code;
    // updateCodetable(root, code); // 更新编码表
}

// 将 vector<bool> 转换为 string
// std::string AHC::vectorBool2String(const std::vector<bool> &v)
// {
//     std::string res;
//     res.reserve(v.size()); // forward allocate memory
//     for (bool b : v)
//     {
//         res += b ? '1' : '0';
//     }
//     return res;
// }

// BFS(广度优先搜索)
// 根， 右， 左
// 保证权重相同的节点中位置最高的节点优先遍历
// 获取的节点不与 node 有祖先关系
Node *AHC::getMaxIndexNode(Node *node, bool isEncode)
{
    std::queue<Node *> q;
    if (isEncode)
        q.push(encode_root);
    else
        q.push(decode_root);
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
            continue;

        // 递归遍历左右子树，优先遍历右子树
        if (cur_node->right)
            q.push(cur_node->right);

        if (cur_node->left)
            q.push(cur_node->left);
    }
    return max_node;
}

// 交换两个节点(节点父指针，并更新各自父指针的对应子树指针)
void AHC::swapNode(Node *node1, Node *node2)
{
    // 由于 node1 和 node2 不可能是 root 节点，所以不需要判断 nodeX->parent 是否为 nullptr
    bool isLeft = node2->parent->left == node2;

    if (node1->parent->left == node1)
        node1->parent->left = node2;
    else
        node1->parent->right = node2;

    if (isLeft)
        node2->parent->left = node1;
    else
        node2->parent->right = node1;

    std::swap(node1->parent, node2->parent); // 交换父指针
}

// 更新编码表
// void AHC::updateCodetable(Node *node, std::vector<bool> &code)
// {
//     if (node->isLeaf())
//     {
//         code_table[node->symbol] = code;
//         return;
//     }
//     if (node->left)
//     {
//         code.push_back(false);
//         updateCodetable(node->left, code); // 左子树编码为0
//         code.pop_back();
//     }
//     if (node->right)
//     {
//         code.push_back(true);
//         updateCodetable(node->right, code); // 右子树编码为1
//         code.pop_back();
//     }
// }
