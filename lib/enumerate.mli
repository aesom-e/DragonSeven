(** [sum_over_draws shoe f] considers every value [v] with cards remaining in [shoe],
    computes the probability of drawing it, removes it to get the resulting shoe,
    calls [f v shoe'] to get the probability-weighted outcome of everything downstream,
    and sums [prob * f v shoe'] over all v. *)
val sum_over_draws :
    Shoe.t -> 
    zero:'a ->
    add:('a -> 'a -> 'a) ->
    scale:('a -> float -> 'a) ->
    f:(int -> Shoe.t -> 'a) ->
    'a
