let to_list (str : string) : char list =
  List.init (String.length str) (String.get str)

let exists (iterator : char list -> bool) (str : char list) : bool =
  match str with
  | [] -> false
  | _ :: cs as str -> 
      iterator str || iterator cs
