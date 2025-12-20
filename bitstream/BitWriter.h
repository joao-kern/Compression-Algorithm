#include <iostream>
#include <fstream>
#include <cstdint>
#ifndef BITWRITER_H
#define BITWRITER_H

class BitWriter
{
private:
    uint8_t byte_buffer = 0;
    uint8_t cont_buffer_bits = 0;
    uint64_t cont_total_bits = 0;
    std::ofstream *file = nullptr;
    void write_byte();
    void flush();

public:
    BitWriter(std::string path_file);
    ~BitWriter();

    void write_bit(bool bit);
    void close_file();
};

#endif
