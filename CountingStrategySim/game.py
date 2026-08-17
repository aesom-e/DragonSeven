import random
from dataclasses import dataclass
from enum import Enum, auto

class Shoe:
    def __init__(self, num_decks: int) -> None:
        self._cards: list[int] = [0] * num_decks * 16 + [v for v in range(1, 10) for _ in range(4 * num_decks)]
        self._num_cards = 52 * num_decks
        self._cut_card: int = int(len(self._cards) * random.uniform(0.7, 0.8))
        self._pos: int = 0
        random.shuffle(self._cards)

    # Call when starting a new game to shuffle if the cut card was drawn in the last game
    def new_game(self) -> bool:
        if self._pos < self._cut_card: return False
        random.shuffle(self._cards)
        self._cut_card = int(len(self._cards) * random.uniform(0.7, 0.8))
        self._pos = 0
        return True

    def draw(self) -> int:
        val = self._cards[self._pos]
        self._pos += 1
        return val

    # Gives the divisor that the player would use to find the true count
    # This will be rounded to the nearest deck
    def divisor(self) -> int:
        decks_left = (self._num_cards - self._pos) / 52
        return round(decks_left)

class Winner(Enum):
    Player = auto()
    Banker = auto()
    Tie = auto()
    Push = auto()

@dataclass
class Result:
    winner: Winner
    dragon7: bool

    @staticmethod
    def from_hand(player_cards: list[int], banker_cards: list[int]) -> "Result":
        player_total, banker_total = sum(player_cards) % 10, sum(banker_cards) % 10

        if player_total == banker_total: return Result(Winner.Tie, False)
        if player_total > banker_total: return Result(Winner.Player, False)

        if len(banker_cards) == 3 and banker_total == 7:
            return Result(Winner.Push, True)

        return Result(Winner.Banker, False)

class Game:
    def __init__(self, shoe: Shoe) -> None:
        self._shoe: Shoe = shoe

    # Returns (Player cards, Banker cards, New shoe, Result)
    def play(self) -> tuple[list[int], list[int], bool, Result]:
        # Draw the first two cards
        player_cards, banker_cards = [], []
        player_cards.append(self._shoe.draw())
        banker_cards.append(self._shoe.draw())
        player_cards.append(self._shoe.draw())
        banker_cards.append(self._shoe.draw())

        # Check for a natural
        player_total, banker_total = sum(player_cards) % 10, sum(banker_cards) % 10
        if player_total >= 8 or banker_total >= 8:
            return (player_cards,
                    banker_cards,
                    self._shoe.new_game(),
                    Result.from_hand(player_cards, banker_cards))

        # Check if the player should draw a third card
        if player_total < 6: player_cards.append(self._shoe.draw())

        # Check if the banker should draw a third card
        if player_total > 5:
            if banker_total < 6: banker_cards.append(self._shoe.draw())
        else:
            player_third_card = player_cards[2]
            match banker_total:
                case 0 | 1 | 2: banker_cards.append(self._shoe.draw())
                case 3 if player_third_card != 8: banker_cards.append(self._shoe.draw())
                case 4 if 2 <= player_third_card <= 7: banker_cards.append(self._shoe.draw())
                case 5 if 4 <= player_third_card <= 7: banker_cards.append(self._shoe.draw())
                case 6 if 6 <= player_third_card <= 7: banker_cards.append(self._shoe.draw())

        return (player_cards,
                banker_cards,
                self._shoe.new_game(),
                Result.from_hand(player_cards, banker_cards))