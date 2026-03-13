#include "Decompressor.h"
#include "BitReader.h"
#include "BitWriter.h"
#include "Format.h"
#include "Huffman.h"
#include <fstream>
#include <iostream>
#include <cstdint>
#include <filesystem>

namespace fs = std::filesystem;

Decompressor::Decompressor(const fs::path path_file)
{
    bit_reader = new BitReader(path_file);

    format = new Format;

    output_path = path_file;

    std::string ext = path_file.extension().string();

    if (ext != signature)
    {
        throw std::invalid_argument("*This file is not supported*");
    }

    read_header();

    huffman_build(format->freq_simbols);

    write_decompressed_file();
}

Decompressor::~Decompressor()
{
    if (file)
    {
        if (file->is_open())
        {
            file->close();
        }
        delete file;
        file = nullptr;
    }

    delete bit_reader;
    bit_reader = nullptr;

    delete bit_writer;
    bit_writer = nullptr;

    delete format;
    format = nullptr;

    delete huffman;
    huffman = nullptr;
}

void Decompressor::read_header()
{
    char *format_data = reinterpret_cast<char *>(format);

    bit_reader->read_bytes(format_data, sizeof(Format));
}

void Decompressor::huffman_build(std::array<std::size_t, 256> &freq_simbols)
{
    huffman = new Huffman(freq_simbols);
}

void Decompressor::write_decompressed_file()
{
    std::string og_extension_str = format->og_extension;
    output_path.replace_extension(og_extension_str);

    file = new std::ofstream(output_path, std::ios::binary);

    if (!file->is_open())
    {
        throw std::invalid_argument("*The input file is corrupted*");
    }

    uint64_t bytes_decoded = 0;

    while (bytes_decoded < format->og_quant_bytes)
    {
        while (true)
        {
            bool bit = bit_reader->read_bit();
            bool valid_simbol = huffman->decode(bit);
            if (valid_simbol)
            {
                uint8_t byte = huffman->get_current_simbol();
                file->write(reinterpret_cast<char *>(&byte), sizeof(uint8_t));
                bytes_decoded++;
                break;
            }
        }
    }

    if (file->is_open())
    {
        file->close();
    }

    delete file;
    file = nullptr;
}