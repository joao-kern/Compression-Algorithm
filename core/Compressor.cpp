#include "Compressor.h"
#include "BitWriter.h"
#include "Format.h"
#include "Huffman.h"
#include <fstream>
#include <iostream>
#include <cstdint>
#include <vector>
#include <utility>
#include <filesystem>
#include <unordered_map>
#include <cstring>

namespace fs = std::filesystem;

Compressor::Compressor(const fs::path path_file)
{
    file = new std::ifstream(path_file, std::ios::binary);

    if (!file->is_open())
    {
        std::cerr << "File was not opened correctly\n*Check the file path*" << '\n';
        return;
    }

    format = new Format;

    output_path = path_file;

    output_path.replace_extension(compressor_extension);

    std::string ext = path_file.extension().string();

    std::strncpy(format->og_extension, ext.c_str(), sizeof(format->og_extension) - 1);
    format->og_extension[sizeof(format->og_extension) - 1] = '\0';

    std::strncpy(format->signature, compressor_extension, sizeof(format->signature));

    format->freq_simbols = bytes_counter();

    huffman_build(format->freq_simbols);

    write_compressed_file(format->freq_simbols);
}

Compressor::~Compressor()
{
    if (file->is_open())
    {
        file->close();
    }

    delete file;
    file = nullptr;

    if (bit_writer)
    {
        delete bit_writer;
        bit_writer = nullptr;
    }

    delete format;
    format = nullptr;

    delete huffman;
    huffman = nullptr;
}

void Compressor::huffman_build(std::array<std::size_t, 256> &freq_simbols)
{
    huffman = new Huffman(freq_simbols);
}

std::array<std::size_t, 256> Compressor::bytes_counter()
{
    std::unordered_map<std::uint8_t, std::size_t> simbols_map;

    uint8_t byte;

    while (file->read(reinterpret_cast<char *>(&byte), sizeof(uint8_t)))
    {
        if (simbols_map.count(byte))
        {
            ++simbols_map[byte];
        }
        else
        {
            simbols_map[byte] = 1;
        }
        ++format->og_quant_bytes;
    }

    file->clear();
    file->seekg(0, std::ios::beg);

    std::array<std::size_t, 256> simbols_vec = {0};

    for (const auto &pair : simbols_map)
    {
        simbols_vec[pair.first] = pair.second;
    }

    return simbols_vec;
}

void Compressor::write_compressed_file(const std::array<std::size_t, 256> &freq_simbols)
{
    bit_writer = new BitWriter(output_path);

    bit_writer->write_bytes(reinterpret_cast<char *>(format), sizeof(Format));

    uint8_t byte;

    while (file->read(reinterpret_cast<char *>(&byte), sizeof(uint8_t)))
    {

        std::vector<bool> coded_byte = huffman->encode(byte);

        for (const auto &bit : coded_byte)
        {
            bit_writer->write_bit(bit);
        }
    }

    bit_writer->close_file();
}