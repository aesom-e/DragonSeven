#ifndef HAND_HPP
#define HAND_HPP

#include <vector>
#include <numeric>

struct Hand {
    Hand() { contents.reserve(3); }

    void add(int card) { contents.push_back(card); }

    int value() const {
        return std::accumulate(contents.begin(), contents.end(), 0) % 10;
    }

    std::size_t cards() const { return contents.size(); }

private:
    std::vector<int> contents;
};

#endif