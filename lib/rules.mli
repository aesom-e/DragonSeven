(** [player_draws total] is true if a player showing [total] draws a third card.
    This is only meaningful in the case that no side has drawn a natural. *)
val player_draws : int -> bool

(** [banker_draws ~banker_total ~player_drew ~player_third_card] is true
    if the banker draws a card given the banker's two-card total,
    whether the player drew a third card, and if so, its value. *)
val banker_draws : banker_total:int -> player_drew:bool -> player_third_card:int -> bool
