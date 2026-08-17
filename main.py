from numpy.ma.extras import average

from game import Shoe, Game
from player import Strategy, Player
import matplotlib.pyplot as plt

def main() -> int | None:
    pass

def side_bet(count: int) -> int:
    match count:
        #case _ if count in [6, 7]: return 5
        case _ if count in [8, 9]: return 10
        case _ if count >= 10: return 25
        case _: return 0

if __name__ == "__main__":
    game = Game(Shoe(8))
    player = Player(game,
                    Strategy(
                        starting_cash=10_000,
                        count={
                            0:  0,
                            1:  0,
                            2:  0,
                            3:  0,
                            4: -1,
                            5: -1,
                            6: -1,
                            7: -1,
                            8:  2,
                            9:  2
                        },
                        normal_bet=None,
                        side_bet=side_bet
                    ))

    runs = []
    for _ in range(1_000):
        series = []
        for _ in range(50_000):
            player.play()
            series.append(player.money)
            if player.money <= 0: break
        runs.append(series)

        # Reset the player
        player.reset()


    # Plot the game
    t = range(len(runs[0]))
    for series in runs:
        plt.plot(t, series, linestyle='-')
    plt.xlabel("Time")
    plt.ylabel("Money")
    plt.title("Bankroll vs Time")
    plt.grid(True)
    plt.show()

    # Print statistics
    ending_values = [series[len(series)-1] for series in runs]
    num_runs = len(runs)
    num_to_end = sum([1 if ending_value != 0 else 0 for ending_value in ending_values])
    num_in_profit = sum([1 if ending_value > player._strategy.starting_cash else 0 for ending_value in ending_values])
    mean = average(ending_values)

    print(f"{num_to_end} out of {num_runs} ({(num_to_end / num_runs):.2f}) made it to the end")
    print(f"{num_in_profit} out of {num_runs} ({(num_in_profit / num_runs):.2f}) made profit")
    print(f"Average ending value: ${mean:.2f} (profit: ${(mean - player._strategy.starting_cash):.2f})")