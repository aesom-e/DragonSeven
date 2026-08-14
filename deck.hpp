#ifndef DECK_HPP
#define DECK_HPP

// The Deck struct will just hold the
// static information for the contents of the deck.
// It will be the job of the Shoe to hold on to the individual cards.
struct Deck {
    constexpr Deck() {}
    explicit constexpr Deck(std::array<std::size_t, 10>&& counts_) : counts{counts_} {}

    [[nodiscard]] constexpr int size() const {
        return std::accumulate(counts.begin(), counts.end(), 0);
    }

    const std::array<std::size_t, 10> counts {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 16
    };
};

#endif