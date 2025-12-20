#include "BitWriter.h"
#include <iostream>
#include <fstream>

BitWriter::BitWriter(const std::string path_file)
{
    file = new std::ofstream(path_file, std::ios::binary);

    file->write(reinterpret_cast<char *>(&cont_total_bits), sizeof(uint64_t));
}

BitWriter::~BitWriter()
{
    delete file;
    file = nullptr;
}

void BitWriter::write_bit(bool bit)
{
    if (bit)
    {
        byte_buffer |= 128 >> cont_buffer_bits;
    }
    cont_buffer_bits++;
    cont_total_bits++;

    if (cont_buffer_bits == 8)
    {
        write_byte();
    }
}

void BitWriter::write_byte()
{
    if (file->is_open())
    {
        file->write(reinterpret_cast<char *>(&byte_buffer), sizeof(uint8_t));
        byte_buffer = 0;
        cont_buffer_bits = 0;
    }
    else
    {
        std::cerr << "File was not opened correctly\n*Check the file path*";
    }
}

void BitWriter::flush()
{
    if (cont_buffer_bits != 0)
    {
        write_byte();
    }
}

void BitWriter::close_file()
{
    if (file->is_open())
    {
        flush();
        file->seekp(file->beg);
        file->write(reinterpret_cast<char *>(&cont_total_bits), sizeof(uint64_t));
        file->close();
        delete file;
        file = nullptr;
    }
    else
    {
        std::cerr << "File was not opened correctly\n*Check the file path*";
    }
}