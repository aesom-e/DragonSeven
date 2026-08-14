#include <iostream>
#include "shoe.hpp"
#include "game.hpp"

int main() {
    Shoe<Deck{}> shoe{};
    Game game{ShoeRef{shoe}};
    std::size_t player_wins{}, banker_wins{}, ties{}, pushes{};

    for(std::size_t i{};i<100'000'000;++i) {
        Result result{game.play()};
        switch(result.winner) {
            case Winner::Player: ++player_wins; break;
            case Winner::Banker: ++banker_wins; break;
            case Winner::Tie:    ++ties;        break;
            case Winner::Push:   ++pushes;      break;
        }
    }

    std::cout << "Player wins: " << player_wins << "\n";
    std::cout << "Banker wins: " << banker_wins << "\n";
    std::cout << "Ties: " << ties << "\n";
    std::cout << "Pushes: " << pushes << "\n";
}