open Base

type t = int array

let init n_decks = Array.init 10 ~f:(fun i -> if i = 0 then 16 * n_decks else 4 * n_decks)

let total shoe = Array.fold shoe ~init:0 ~f:(+)

let count shoe v = shoe.(v)

let prob shoe v =
    let n = total shoe in
    if n = 0 then 0.0
    else Float.of_int shoe.(v) /. Float.of_int n

let remove shoe v = 
    let shoe' = Array.copy shoe in
    shoe'.(v) <- shoe.(v) - 1;
    shoe'
