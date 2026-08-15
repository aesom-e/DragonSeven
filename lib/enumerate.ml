open Base

let sum_over_draws shoe ~f =
    List.init 10 ~f:Fn.id
    |> List.fold ~init:0. ~f:(fun acc v ->
        if Shoe.count shoe v = 0 then acc else
            let p = Shoe.prob shoe v in
            let shoe' = Shoe.remove shoe v in
            acc +. (p *. f v shoe'))
