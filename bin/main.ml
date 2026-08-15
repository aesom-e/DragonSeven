open Dragon7
open Stdio

let () = print_endline @@ Float.to_string @@
    Enumerate.sum_over_draws (Shoe.init 8) ~f:(fun v _ -> if v = 1 then 1. else 0.)
