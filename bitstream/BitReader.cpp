#include "BitReader.h"
#include <fstream>
#include <cstdint>

BitReader::BitReader(const std::string path_file)
{
    file = new std::ifstream(path_file, std::ios::binary);

    file->read(reinterpret_cast<char *>(&total_bits), sizeof(total_bits));
}

BitReader::~BitReader()
{
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
        std::cerr << "File was not opened correctly\n*Check the file path*";
    }
}

int BitReader::read_bit()
{
    if (bits_read == total_bits)
    {
        return -1;
    }
    if (cont_buffer == 8 || bits_read == 0)
    {
        read_byte();
    }
    int bit = (buffer >> (7 - cont_buffer)) & 1;
    cont_buffer++;
    bits_read++;

    return bit;
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
        std::cerr << "File was not opened correctly\n*Check the file path*";
    }
}