from dataclasses import dataclass
from typing import Callable
import random
from game import Winner, Result, Game

@dataclass
class Strategy:
    starting_cash: int
    count: dict[int, int] # {Card Value -> Modifier}
    normal_bet: int | None # If this is not None, the player will cover bet the
                           # specified amount randomly on either player or banker
    side_bet: Callable[[int], int] # (lambda count -> side bet amount)

class Player:
    def __init__(self, game: Game, strategy: Strategy) -> None:
        self._game: Game = game
        self._strategy: Strategy = strategy
        self._count: int = 0
        self._money: int = strategy.starting_cash

    @property
    def money(self) -> int: return self._money

    def _true_count(self) -> int:
        return round(self._count / self._game._shoe.divisor())

    def playing_side_bet(self) -> bool:
        return self._strategy.side_bet(self._true_count()) != 0

    def play(self) -> None:
        # Check that the player has money
        if self._money <= 0: return

        player_bet = 0
        if self._strategy.normal_bet is not None:
            bet_on_banker = random.random() > 0.5

            # If this is negative, this counts as a banker bet
            player_bet = self._strategy.normal_bet * (-1 if bet_on_banker else 1)

        # Check that the bet doesn't exceed the bankroll
        if self._money - abs(player_bet) <= 0:
            player_bet = self._money * (-1 if player_bet < 0 else 1)
            side_bet = 0
        else:
            side_bet = self._strategy.side_bet(self._true_count())
            if side_bet > self._money: side_bet = self._money

        player_cards, banker_cards, shuffle, result = self._game.play()

        # Handle the count
        if shuffle: self._count = 0
        else:
            for card in player_cards:
                val = self._strategy.count[card]
                if val is not None: self._count += val
            for card in banker_cards:
                val = self._strategy.count[card]
                if val is not None: self._count += val

        # Calculate the result of the normal bet
        if player_bet is not None:
            match result.winner:
                case Winner.Player: self._money += player_bet
                case Winner.Banker: self._money -= player_bet
                case Winner.Push if player_bet > 0: self._money -= player_bet

        # Calculate the result of the side bet
        if result.dragon7:
            self._money += side_bet * 40
        else:
            self._money -= side_bet

    # Helper to reset the player's state
    def reset(self) -> None:
        self._game._shoe._pos = self._game._shoe._num_cards + 1
        self._game._shoe.new_game()
        self._count = 0
        self._money = self._strategy.starting_cash