#ifndef GAME_HPP
#define GAME_HPP

#include "shoe.hpp"
#include "hand.hpp"
#include "result.hpp"

struct Game {
    explicit Game(ShoeRef shoe_) : shoe{shoe_} {}

    // This is just written out for the sake of simplicity and quickness.
    // I haven't given much thought to the layout of this code.
    Result play() const {
        Hand player_hand{}, banker_hand{};

        // Initial deal
        player_hand.add(shoe.next());
        banker_hand.add(shoe.next());
        player_hand.add(shoe.next());
        banker_hand.add(shoe.next());

        // Natural check
        int player_val = player_hand.value();
        int banker_val = banker_hand.value();
        if(player_val >= 8 || banker_val >= 8) return Result::from_hands(player_hand, banker_hand);

        // Player draw
        int player_draw{};
        if(player_val < 6) player_hand.add(player_draw = shoe.next());

        // Banker draw
        if(player_val >= 6) {
            if(banker_val < 6) banker_hand.add(shoe.next());
        } else {
            player_val = player_hand.value();
            switch(banker_val) {
                case 0: [[fallthrough]];
                case 1: [[fallthrough]];
                case 2: {
                    banker_hand.add(shoe.next());
                    break;
                }
                case 3: {
                    if(player_val != 8) banker_hand.add(shoe.next());
                    break;
                }
                case 4: {
                    if(player_val >= 2 && player_val <= 7) banker_hand.add(shoe.next());
                    break;
                }
                case 5: {
                    if(player_val >= 4 && player_val <= 7) banker_hand.add(shoe.next());
                    break;
                }
                case 6: {
                    if(player_val == 6 || player_val == 7) banker_hand.add(shoe.next());
                    break;
                }
                default: break;
            }
        }

        return Result::from_hands(player_hand, banker_hand);
    }

private:
    ShoeRef shoe;
};

#endif