#include "BitWriter.h"
#include <iostream>
#include <fstream>
#include <cstdint>

BitWriter::BitWriter(const std::string path_file)
{
    file = new std::ofstream(path_file, std::ios::binary);
    if (!file->is_open())
    {
        throw std::runtime_error("File was not opened correctly: " + path_file);
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
        throw std::runtime_error("File was not opened correctly");
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
        throw std::runtime_error("File was not opened correctly");
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
        throw std::runtime_error("File was not opened correctly");
    }
}