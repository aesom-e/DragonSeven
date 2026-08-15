let sum shoe f = Enumerate.sum_over_draws shoe ~zero:Outcome.zero ~add:Outcome.add ~scale:Outcome.scale ~f:f

let run shoe =
    sum shoe  (fun p1 shoe1 ->
    sum shoe1 (fun b1 shoe2 ->
    sum shoe2 (fun p2 shoe3 ->
    sum shoe3 (fun b2 shoe4 ->
        let player_total = (p1 + p2) mod 10 in
        let banker_total = (b1 + b2) mod 10 in
        if player_total >= 8 || banker_total >= 8 then
            Outcome.classify ~banker_total ~player_total ~banker_three_card:false
        else if Rules.player_draws player_total then
            sum shoe4 (fun p3 shoe5 ->
                let player_final = (player_total + p3) mod 10 in
                if Rules.banker_draws ~banker_total ~player_drew:true ~player_third_card:p3 then
                    sum shoe5 (fun b3 _ ->
                        let banker_final = (banker_total + b3) mod 10 in
                        Outcome.classify ~banker_total:banker_final
                                         ~player_total:player_final
                                         ~banker_three_card:true)
                else
                    Outcome.classify ~banker_total
                                     ~player_total:player_final
                                     ~banker_three_card:false)
        else if Rules.banker_draws ~banker_total ~player_drew:false ~player_third_card:0 then
            sum shoe4 (fun b3 _ ->
                let banker_final = (banker_total + b3) mod 10 in
                Outcome.classify ~banker_total:banker_final
                                 ~player_total
                                 ~banker_three_card:true)
        else
            Outcome.classify ~banker_total
                             ~player_total
                             ~banker_three_card:false))))
