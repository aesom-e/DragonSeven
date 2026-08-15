open Dragon7
open Stdio

let () = print_endline @@ Int.to_string (Shoe.total (Shoe.fresh 8))
