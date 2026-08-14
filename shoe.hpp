#ifndef SHOE_HPP
#define SHOE_HPP

#include <array>
#include <vector>
#include <random>
#include "deck.hpp"
#include "globals.hpp"

template<Deck deck, std::size_t number_of_decks = 8>
struct Shoe {
    explicit Shoe() :
        cards{
            [] -> std::array<int, deck.size() * number_of_decks> {
                std::vector<int> cards{};
                cards.reserve(deck.size() * number_of_decks);

                int value{1};
                for(std::size_t count : deck.counts) {
                    for(std::size_t i{};i<count*number_of_decks;++i) cards.push_back(value);
                    ++value;
                }

                std::array<int, deck.size() * number_of_decks> cards_arr{};
                std::copy(cards.begin(), cards.end(), cards_arr.begin());

                return cards_arr;
            }()
        },
        pos{},
        cut_card{cut_card_pos()}
    {
        std::shuffle(cards.begin(), cards.end(), globals::rng);
    }

    // The only current problem with this is that once the cut card is drawn,
    // the dealer finishes the current hand before shuffling the deck.
    // This must be fixed before any accurate counting simulation can be run
    [[nodiscard]] int next() {
        const int value{cards[++pos]};
        if(pos >= cut_card) shuffle();
        return value;
    }

private:
    std::array<int, deck.size() * number_of_decks> cards;
    std::size_t pos, cut_card;

    static std::size_t cut_card_pos() {
        static std::uniform_int_distribution dist{
            static_cast<int>(deck.size() * number_of_decks * 0.7),
            static_cast<int>(deck.size() * number_of_decks * 0.9)
        };

        return dist(globals::rng);
    }

    void shuffle() {
        std::shuffle(cards.begin(), cards.end(), globals::rng);
        pos = 0;
        cut_card = cut_card_pos();
    }
};

struct ShoeRef {
    template<Deck deck, std::size_t number_of_decks>
    explicit ShoeRef(Shoe<deck, number_of_decks>& shoe) :
        ptr{static_cast<void*>(&shoe)},
        next_function([](void* p) -> int {
            return static_cast<Shoe<deck, number_of_decks>*>(p)->next();
        }) {}

    [[nodiscard]] int next() const { return next_function(ptr); }

private:
    void* ptr;
    int (*next_function)(void*);
};

#endif
