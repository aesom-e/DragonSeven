type t = {
    p_banker_win : float;
    p_player_win : float;
    p_tie        : float;
    p_dragon7    : float;
}

let zero = { p_banker_win = 0.; p_player_win = 0.; p_tie = 0.; p_dragon7 = 0. }

let add a b =
    { p_banker_win = a.p_banker_win +. b.p_banker_win;
    p_player_win = a.p_player_win +. b.p_player_win;
    p_tie = a.p_tie +. b.p_tie;
    p_dragon7 = a.p_dragon7 +. b.p_dragon7; }

let scale a k =
    { p_banker_win = a.p_banker_win *. k;
    p_player_win = a.p_player_win *. k;
    p_tie = a.p_tie *. k;
    p_dragon7 = a.p_dragon7 *. k; }

let classify ~banker_total ~player_total ~banker_three_card =
    if banker_total > player_total then
        { zero with
        p_banker_win = 1.;
        p_dragon7 = (if banker_three_card && banker_total = 7 then 1. else 0.) }
    else if banker_total < player_total then
        { zero with p_player_win = 1. }
    else
        { zero with p_tie = 1. }
