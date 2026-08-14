#include <iostream>
#include "shoe.hpp"

int main() {
    Shoe<Deck{}> shoe{};
    std::array<std::size_t, 10> occurrences{};
    for(std::size_t i{};i<1'000'000;++i) ++occurrences[shoe.next()-1];

    for(std::size_t i{};i<10;++i) {
        std::cout << (i+1) << ": " << occurrences[i] << " [" << (occurrences[i] / 1'000'000.) << "]\n";
    }
}