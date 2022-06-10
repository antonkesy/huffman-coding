#include <string>
#include <iostream>
#include "include/huffman_coding.hpp"


int main() {
    using std::string;
    using huffman_coding::IHuffmanData;
    using huffman_coding::HuffmanCoding;

    string example_string = "BCAADDDCCACACAC";
    auto data = HuffmanCoding::encode({example_string.begin(), example_string.end()});

    auto decoded = HuffmanCoding::decode(*data);
    for (const auto &item: *decoded)
        std::cout << item;

    return 0;
}
