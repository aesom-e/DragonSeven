type t 

(** [fresh n_decks] build a full unshuffled shoe of [n_decks] decks. *)
val fresh : int -> t

(** [total shoe] is the total number of cards remaining. *)
val total : t -> int

(** [count shoe v] is the number of cards of value [v] that remain in the shoe. *)
val count : t -> int -> int

(** [prob shoe v] is the probability that the next card drawn has value [v]. *)
val prob : t -> int -> float

(** [remove shoe v] return a new shoe with one card of value [v] taken out.
    Precondition: [count shoe v > 0] *)
val remove : t -> int -> t
