#ifndef FORMAT
#define FORMAT

#include <iostream>
#include <cstdint>
#include <array>
#include <utility>

struct Format
{
    char signature[6];
    char og_extension[16];
    uint64_t og_quant_bytes = 0;
    std::array<std::size_t, 256> freq_simbols;
};

#endif