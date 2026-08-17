#ifndef RESULT_HPP
#define RESULT_HPP

#include "hand.hpp"

enum class Winner {
    Player,
    Banker,
    Tie,
    Push // In EZ Baccarat, there is no banker commission so to regain their house edge,
         // the casino has the banker push on a banker win with a three-card seven
};

struct Result {
    static Result from_hands(const Hand& player_hand, const Hand& banker_hand) {
        int player_value = player_hand.value(), banker_value = banker_hand.value();
        if(player_value == banker_value) return Result{Winner::Tie};

        // Get the winner
        auto winner{Winner::Player};
        if(banker_value > player_value) winner = Winner::Banker;

        // Check for the side bets
        bool dragon_seven{}, panda_eight{};
        if(winner == Winner::Banker && banker_hand.cards() == 3 && banker_value == 7) {
            dragon_seven = true;
            winner = Winner::Push;
        }
        if(winner == Winner::Player && player_hand.cards() == 3 && player_value == 8)
            panda_eight = true;

        return Result{winner, dragon_seven, panda_eight};
    }

    Winner winner;
    bool dragon_seven;
    bool panda_eight;
};

#endif