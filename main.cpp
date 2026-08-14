#include <iostream>
#include "shoe.hpp"
#include "game.hpp"

constexpr double required_even_payout(std::size_t hits, std::size_t samples) {
    return static_cast<double>(samples) / hits;
}

int main() {
    Shoe<Deck{}> shoe{};
    Game game{ShoeRef{shoe}};
    std::size_t player_wins{}, banker_wins{}, ties{}, pushes{};
    std::size_t dragon_sevens{}, panda_eights{};

    std::size_t samples{10'000'000};
    for(std::size_t i{};i<samples;++i) {
        auto [winner, dragon_seven, panda_eight]{game.play()};
        switch(winner) {
            case Winner::Player: ++player_wins; break;
            case Winner::Banker: ++banker_wins; break;
            case Winner::Tie:    ++ties;        break;
            case Winner::Push:   ++pushes;      break;
        }

        if(dragon_seven) ++dragon_sevens;
        if(panda_eight)  ++panda_eights;
    }

    std::cout << "Player wins: " << player_wins << ". Required payout: " << required_even_payout(player_wins, samples) << "\n";
    std::cout << "Banker wins: " << banker_wins << ". Required payout: " << required_even_payout(banker_wins, samples) << "\n";
    std::cout << "Ties: " << ties << ". Required payout: " << required_even_payout(ties, samples) << "\n";
    std::cout << "Pushes: " << pushes << ". Required payout: " << required_even_payout(pushes, samples) << "\n\n";

    std::cout << "Dragon Sevens: " << dragon_sevens << ". Required payout: " << required_even_payout(dragon_sevens, samples) << "\n";
    std::cout << "Panda Eights: " << panda_eights << ". Required payout: " << required_even_payout(panda_eights, samples) << "\n\n";
}