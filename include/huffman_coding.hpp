#ifndef HUFFMAN_HUFFMAN_CODING_HPP
#define HUFFMAN_HUFFMAN_CODING_HPP

#include "huffman_data.hpp"

namespace huffman_coding {

    class HuffmanCoding {
    public:
        static std::unique_ptr<IHuffmanData> encode(const std::vector<unsigned char> &input);

        static std::unique_ptr<std::vector<unsigned char>> decode(const IHuffmanData &input);
    };
}

#endif