#include "BitReader.h"
#include "BitWriter.h"

int main(int argc, char const *argv[])
{
    BitWriter bit_writer(argv[1]);

    for (int i = 0; i < 16; i++)
    {
        bit_writer.write_bit(i % 2);
    }

    bit_writer.close_file();

    BitReader bit_reader(argv[1]);

    for (int i = 0; i < 16; i++)
    {

        std::cout << bit_reader.read_bit();

        if (((i + 1) % 8) == 0)
        {
            std::cout << std::endl;
        }
    }

    bit_reader.close_file();

    return 0;
}
