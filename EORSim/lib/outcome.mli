type t = {
    p_banker_win : float;
    p_player_win : float;
    p_tie        : float;
    p_dragon7    : float;
}

val zero : t
val add : t -> t -> t
val scale : t -> float -> t

(** [classify ~banker_total ~player_total ~banker_three_card] is the stats vector
    for one terminal hand (exactly one of {p_banker_win, p_player_win, p_tie} is 1.) *)
val classify : banker_total:int -> player_total:int -> banker_three_card:bool -> t
