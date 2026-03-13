#ifndef COMPRESSOR
#define COMPRESSOR

#include "BitWriter.h"
#include "Format.h"
#include "Huffman.h"
#include <filesystem>

namespace fs = std::filesystem;

class Compressor
{
private:
    const char compressor_extension[6] = ".kern";
    BitWriter *bit_writer;
    Huffman *huffman;
    Format *format;
    fs::path output_path;
    std::ifstream *file = nullptr;
    void huffman_build(std::array<std::size_t, 256> &freq_simbols);
    std::array<std::size_t, 256> bytes_counter();
    void write_compressed_file(const std::array<std::size_t, 256> &freq_simbols);

public:
    Compressor(const fs::path path_file);
    ~Compressor();
};

#endif