(** [run shoe] walks the full decision tree for one baccarat hand delt from [shoe]
    and returns the probability states *)
val run : Shoe.t -> Outcome.t
