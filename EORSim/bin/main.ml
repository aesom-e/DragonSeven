open Dragon7

let () =
    let shoe = Shoe.init 8 in
    let o = Deal.run shoe in
    Printf.printf "Banker win: %f\n" o.p_banker_win;
    Printf.printf "Player win: %f\n" o.p_player_win;
    Printf.printf "Tie: %f\n" o.p_tie;
    Printf.printf "Dragon7: %f\n" o.p_dragon7;
    Printf.printf "Dragon7 EV: %f\n" ((41. *. o.p_dragon7) -. 1.)
