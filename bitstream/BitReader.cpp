#include "BitReader.h"
#include <fstream>
#include <cstdint>

BitReader::BitReader(const std::string path_file)
{
    file = new std::ifstream(path_file, std::ios::binary);

    if (!file->is_open())
    {
        throw std::runtime_error("File was not opened correctly: " + path_file);
    }

    file->seekg(0, std::ios::end);

    total_bytes = static_cast<uint64_t>(file->tellg());

    file->clear();
    file->seekg(0, std::ios::beg);
}

BitReader::~BitReader()
{
    if (file != nullptr)
    {
        if (file->is_open())
        {
            file->close();
        }
        delete file;
        file = nullptr;
    }
}

void BitReader::read_byte()
{
    if (file->is_open())
    {
        file->read(reinterpret_cast<char *>(&buffer), sizeof(uint8_t));
        cont_buffer = 0;
    }
    else
    {
        throw std::runtime_error("File was not opened correctly");
    }
}

bool BitReader::read_bit()
{
    if (cont_buffer == 8 || bits_read == 0)
    {
        read_byte();
    }
    bool bit = (buffer >> (7 - cont_buffer)) & 1;
    cont_buffer++;
    bits_read++;

    return bit;
}

void BitReader::read_bytes(char *&data, std::size_t size)
{
    if (file->is_open())
    {
        file->read(data, size);
    }
    else
    {
        throw std::runtime_error("File was not opened correctly");
    }
}

void BitReader::close_file()
{
    if (file->is_open())
    {
        file->close();
        delete file;
        file = nullptr;
    }
    else
    {
        throw std::runtime_error("File was not opened correctly");
    }
}