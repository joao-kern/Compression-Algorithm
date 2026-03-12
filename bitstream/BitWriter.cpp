#include "BitWriter.h"
#include <iostream>
#include <fstream>

BitWriter::BitWriter(const std::string path_file)
{
    file = new std::ofstream(path_file, std::ios::binary);
    if (!file->is_open())
    {
        std::cerr << "File was not opened correctly\n*Check the file path*";
    }
}

BitWriter::~BitWriter()
{
    if (file)
    {
        if (file->is_open())
        {
            close_file();
        }
    }
}

void BitWriter::write_bit(bool bit)
{
    if (bit)
    {
        byte_buffer |= 128 >> cont_buffer_bits;
    }
    cont_buffer_bits++;

    if (cont_buffer_bits == 8)
    {
        write_byte();
    }
}

void BitWriter::write_bytes(char *data, std::size_t size)
{
    if (file->is_open())
    {
        file->write(data, size);
    }
    else
    {
        std::cerr << "File was not opened correctly\n*Check the file path*";
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
        file->close();
        delete file;
        file = nullptr;
    }
    else
    {
        std::cerr << "File was not opened correctly\n*Check the file path*";
    }
}