#ifndef DECOMPRESSOR
#define DECOMPRESSOR

#include "BitReader.h"
#include "BitWriter.h"
#include "Format.h"
#include "Huffman.h"
#include <filesystem>

namespace fs = std::filesystem;

class Decompressor
{
private:
    const char signature[6] = ".kern";
    BitReader *bit_reader;
    BitWriter *bit_writer;
    Huffman *huffman;
    Format *format;
    fs::path output_path;
    std::ofstream *file = nullptr;
    void read_header();
    void huffman_build(std::array<std::size_t, 256> &freq_simbols);
    void write_decompressed_file();

public:
    Decompressor(const fs::path path_file);
    ~Decompressor();
};

#endif