open Base

let player_draws total = total < 6

let banker_draws ~banker_total ~player_drew ~player_third_card =
    if not player_drew then
        banker_total < 6
    else
        let v = player_third_card in
        match banker_total with
        | 0 | 1 | 2 -> true
        | 3 -> v <> 8
        | 4 -> v >= 2 && v <= 7
        | 5 -> v >= 4 && v <= 7
        | 6 -> v = 6 || v = 7
        | _ -> false
