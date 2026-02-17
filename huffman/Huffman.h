#include <iostream>
#include <cstdint>
#include <vector>
#include <tuple>
#include <unordered_map>

class Huffman
{

public:
    Huffman(std::vector<std::tuple<std::size_t, std::string>> &simbols);
    ~Huffman();

    std::vector<bool> encode(std::string simbol);
    bool decode(bool bit);
    std::string get_current_simbol();

private:
    void create_tree(std::vector<std::tuple<std::size_t, std::string>> &simbols);
    void generate_map();

    struct Node
    {
        Node(const std::size_t freq, const std::string simbol) : left{nullptr}, right{nullptr}, freq{freq}, simbol{simbol}
        {
        }

        void search(std::unordered_map<std::string, std::vector<bool>> &code_map, std::vector<bool> &code)
        {
            if (this->simbol != "")
            {
                code_map[this->simbol] = code;
                return;
            }
            std::vector<bool> code_right = code;
            code_right.push_back(true);
            this->right->search(code_map, code_right);

            std::vector<bool> code_left = code;
            code_left.push_back(false);
            this->left->search(code_map, code_left);
        }

        Node *left;
        Node *right;
        std::size_t freq;
        std::string simbol;
    };

    void delete_node(Node *n);

    Node *root;
    Node *cursor;
    std::unordered_map<std::string, std::vector<bool>> code_map;
    size_t size;
    std::string current_simbol;
};
