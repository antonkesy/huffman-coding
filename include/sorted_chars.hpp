#ifndef HUFFMAN_CODING_I_SORTED_ITEMS_HPP
#define HUFFMAN_CODING_I_SORTED_ITEMS_HPP

#include <memory>
#include <map>

namespace huffman_coding {

    class ISortedChars {
    public:
        virtual ~ISortedChars() = default;

        virtual std::shared_ptr<const std::array<uint64_t, 0xFF>> get() = 0;
    };

} // huffman_coding

#endif //HUFFMAN_CODING_I_SORTED_ITEMS_HPP
