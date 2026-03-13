#include "Huffman.h"
#include <iostream>
#include <cstdint>
#include <vector>
#include <utility>
#include <algorithm>

Huffman::Huffman(std::array<std::size_t, 256> &freq_simbols)
{
    root = nullptr;
    size = 0;
    current_simbol = 0;
    create_tree(freq_simbols);
    generate_map();
}

Huffman::~Huffman()
{
    if (root)
    {
        delete_node(root);
    }
}

void Huffman::create_tree(std::array<std::size_t, 256> &freq_simbols)
{
    std::vector<Node *> Nodes;

    for (std::size_t i = 0; i < freq_simbols.size(); i++)
    {
        if (freq_simbols[i] == 0)
        {
            continue;
        }

        Node *n = new Node(i, freq_simbols[i], true);
        Nodes.push_back(n);
    }

    const std::size_t i = 0;
    while (Nodes.size() > 1)
    {
        std::sort(Nodes.begin(), Nodes.end(), [](const Node *a, const Node *b)
                  { return a->freq < b->freq; });
        Node *father = new Node(0, Nodes[i]->freq + Nodes[i + 1]->freq, false);
        father->right = Nodes[i];
        father->left = Nodes[i + 1];
        Nodes.erase(Nodes.begin());
        Nodes.erase(Nodes.begin());
        Nodes.push_back(father);
    }

    if (!Nodes.empty())
    {
        root = Nodes[0];
    }
    else
    {
        root = new Node(0, 0, false);
    }

    cursor = root;
}

void Huffman::generate_map()
{
    Node *temp = root;
    std::vector<bool> code;
    temp->search(code_map, code);
}

std::vector<bool> Huffman::encode(std::uint8_t simbol)
{
    return code_map[simbol];
}

void Huffman::delete_node(Node *n)
{
    if (n->left)
    {
        delete_node(n->left);
    }
    if (n->right)
    {
        delete_node(n->right);
    }
    delete n;
}

bool Huffman::decode(bool bit)
{
    if (bit)
    {
        if (cursor->right)
        {
            cursor = cursor->right;
        }
    }
    else
    {
        if (cursor->left)
        {
            cursor = cursor->left;
        }
    }

    if (cursor->is_leaf)
    {
        current_simbol = cursor->simbol;
        cursor = root;
        return true;
    }

    return false;
}

std::uint8_t Huffman::get_current_simbol()
{
    return current_simbol;
}