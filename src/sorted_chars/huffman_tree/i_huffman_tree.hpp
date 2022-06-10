#ifndef HUFFMAN_CODING_I_HUFFMAN_TREE_HPP
#define HUFFMAN_CODING_I_HUFFMAN_TREE_HPP

#include <memory>

namespace huffman_coding {

    struct Node {
        unsigned char value;
        uint64_t frequency;
        std::shared_ptr<Node> parent, left, right;
    };

    class IHuffmanTree {
    public:
        ~IHuffmanTree() = default;

    };

} // huffman_coding

#endif //HUFFMAN_CODING_I_HUFFMAN_TREE_HPP
