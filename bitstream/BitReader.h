#include <iostream>
#include <fstream>
#include <cstdint>
#ifndef BITREADER_H
#define BITREADER_H

class BitReader
{
private:
    uint8_t buffer = 0;
    uint8_t cont_buffer = 0;
    uint64_t total_bits = 0;
    uint64_t bits_read = 0;
    std::ifstream *file = nullptr;
    void read_byte();

public:
    BitReader(const std::string path_file);
    ~BitReader();
    int read_bit();
    void close_file();
};

#endif