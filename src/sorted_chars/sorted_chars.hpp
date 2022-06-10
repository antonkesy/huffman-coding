#ifndef HUFFMAN_CODING_SORTED_CHARS_HPP
#define HUFFMAN_CODING_SORTED_CHARS_HPP

#include <array>
#include <vector>
#include <map>
#include "../../include/sorted_chars.hpp"

namespace huffman_coding {

    class SortedChars : public ISortedChars {
    public:
        explicit SortedChars(const std::vector<unsigned char> &input);

        ~SortedChars() override = default;

        std::shared_ptr<const std::array<uint64_t, 0xFF>> get() override;

    private:
        std::shared_ptr<std::array<uint64_t, 0xFF>> items_;
    };

} // huffman_coding

#endif //HUFFMAN_CODING_SORTED_CHARS_HPP
