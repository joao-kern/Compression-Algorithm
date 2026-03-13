#ifndef BITREADER_H
#define BITREADER_H

#include <iostream>
#include <fstream>
#include <cstdint>

class BitReader
{
private:
    uint8_t buffer = 0;
    uint8_t cont_buffer = 0;
    uint64_t bits_read = 0;
    std::ifstream *file = nullptr;
    void read_byte();

public:
    BitReader(const std::string path_file);
    ~BitReader();
    uint64_t total_bytes = 0;
    bool read_bit();
    void read_bytes(char *&data, std::size_t size);
    void close_file();
};

#endif