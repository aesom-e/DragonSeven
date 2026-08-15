open Base

let sum_over_draws shoe ~zero ~add ~scale ~f =
    List.init 10 ~f:Fn.id
    |> List.fold ~init:zero ~f:(fun acc v ->
        if Shoe.count shoe v = 0 then acc else
            let p = Shoe.prob shoe v in
            let shoe' = Shoe.remove shoe v in
            add acc (scale (f v shoe') p))
