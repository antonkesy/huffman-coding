#include "sorted_chars.hpp"

namespace huffman_coding {
    SortedChars::SortedChars(const std::vector<unsigned char> &input) {
        for (const auto &c: input) ++((*items_)[c - 'A']);
    }

    std::shared_ptr<const std::array<uint64_t, 0xFF>> SortedChars::get() {
        return items_;
    }

} // huffman_coding