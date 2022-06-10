#include "../include/huffman_coding.hpp"
#include "huffman_coder.hpp"

namespace huffman_coding {

    std::unique_ptr<IHuffmanData> HuffmanCoding::encode(const std::vector<unsigned char> &input) {
        return HuffmanCoder(input).get();
    }

    std::unique_ptr<std::vector<unsigned char>> HuffmanCoding::decode(const IHuffmanData &input) {
        return {nullptr};
    }

}