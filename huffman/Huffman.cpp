#include "Huffman.h"
#include <iostream>
#include <cstdint>
#include <vector>
#include <tuple>
#include <algorithm>

Huffman::Huffman(std::vector<std::tuple<std::size_t, std::string>> &simbols)
{
    root = nullptr;
    size = 0;
    create_tree(simbols);
    generate_map();
}

Huffman::~Huffman()
{
    root->delete_node();
}

void Huffman::create_tree(std::vector<std::tuple<std::size_t, std::string>> &simbols)
{
    std::vector<Node *> Nodes;
    std::sort(simbols.begin(), simbols.end());

    for (const auto &tuple : simbols)
    {
        Node *n = new Node(std::get<0>(tuple), std::get<1>(tuple));
        Nodes.push_back(n);
    }

    std::size_t i = 0;
    while (Nodes.size() > 1)
    {
        std::sort(Nodes.begin(), Nodes.end(), [](const Node *a, const Node *b)
                  { return a->freq <= b->freq; });
        Node *father = new Node(Nodes[i]->freq + Nodes[i + 1]->freq, "");
        father->right = Nodes[i];
        father->left = Nodes[i + 1];
        Nodes.erase(Nodes.begin());
        Nodes.erase(Nodes.begin());
        Nodes.push_back(father);
    }

    root = Nodes[0];

    cursor = root;
}

void Huffman::generate_map()
{
    Node *temp = root;
    std::vector<bool> code;
    temp->search(code_map, code);
}

std::vector<bool> Huffman::encode(std::string simbol)
{
    return code_map[simbol];
}

std::string Huffman::decode(bool bit)
{
    std::size_t i = 0;

    if (bit)
    {
        cursor = cursor->right;
    }
    else
    {
        cursor = cursor->left;
    }
    i++;

    if (cursor->simbol != "")
    {
        std::string s = cursor->simbol;
        cursor = root;
        return s;
    }

    return cursor->simbol;
}