#ifndef HUFFMAN_CODING_HUFFMAN_DATA_HPP
#define HUFFMAN_CODING_HUFFMAN_DATA_HPP

#include <vector>
#include <string>
#include <memory>

#include "sorted_chars.hpp"

namespace huffman_coding {

    class IHuffmanData {
    public:
        virtual ~IHuffmanData() = default;

        virtual const std::shared_ptr<ISortedChars> get() = 0;

    private:
        std::shared_ptr<ISortedChars> items_;
    };
} // huffman_coding

#endif //HUFFMAN_CODING_HUFFMAN_DATA_HPP
