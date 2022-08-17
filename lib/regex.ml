let match_one (pattern : char option) (text : char option) : bool =
  match pattern, text with
  | None, _
  | _, None     -> false
  | Some '.', _ -> true
  | _, _        -> pattern = text

let rec match_multiple (pattern : char list) (text : char list) : bool =
  match pattern, text with
  | [], _
  | ['$'], []         -> true
  | _, []             -> false
  | _ :: '?' :: _, _  -> match_question pattern text
  | _ :: '*' :: _, _  -> match_star pattern text
  | p :: ps, t :: ts  -> match_one (Some p) (Some t) && match_multiple ps ts

and match_question (pattern : char list) (text : char list) : bool =
  match pattern, text with
  | p :: _ :: ps, t :: ts ->
      (match_one (Some p) (Some t) && match_multiple ps ts) ||
      match_multiple ps text
  | _, _                  -> raise Exit

and match_star (pattern : char list) (text : char list) : bool =
  match pattern, text with
  | p :: _ :: ps, t :: ts ->
      (match_one (Some p) (Some t) && match_multiple pattern ts) ||
      match_multiple ps text
  | _, _                  -> raise Exit

let search ~pattern ~text =
  let pattern_list = Regex__Utils.to_list pattern in
  let text_list = Regex__Utils.to_list text in

  match pattern_list, text_list with
  | '^' :: pattern, text  -> match_multiple pattern text
  | pattern, text         -> match_multiple ('.' :: '*' :: pattern) text


(* match_one inline tests *)
let%test "match_one pattern and text are None" =
  match_one None None = false

let%test "match_one pattern is None" =
  match_one None (Some 'a') = false

let%test "match_one text is None" =
  match_one (Some 'a') None = false

let%test "match_one pattern is '.'" =
  match_one (Some '.') (Some 'a')

let%test "match_one pattern and text are same" =
  match_one (Some 'b') (Some 'b')

let%test "match_one pattern and text are not same" =
  match_one (Some 'b') (Some 'c') = false

(* match_multiple inline tests *)
let%test "match_multiple empty pattern empty text" =
  match_multiple [] []

let%test "match_multiple empty pattern non empty text" =
  match_multiple [] ['f'; 'o'; 'o']

let%test "match_multiple $ pattern with empty text" =
  match_multiple ['$'] []

let%test "match_multiple non empty pattern with empty text" =
  match_multiple ['a'] [] = false

let%test "match_multiple pattern and text are the same chars and length" =
  match_multiple ['f'; 'o'; 'o'] ['f'; 'o'; 'o']

let%test "match_multiple pattern and text are not the same chars but same length" =
  match_multiple ['f'; 'o'; 'o'] ['f'; 'o'; 's'] = false

let%test "match_multiple pattern has greater length than text" =
  match_multiple ['f'; 'o'; 'o'] ['f'; 'o'; 'o'; 's']

let%test "match_multiple pattern has lesser length than text" =
  match_multiple ['f'; 'o'; 'o'; 's'] ['f'; 'o'; 'o'] = false

let%test "match_multiple with question mark" =
  match_multiple ['a'; 'b'; '?'; 'c'] ['a'; 'c'] &&
  match_multiple ['a'; 'b'; '?'; 'c'] ['a'; 'b'; 'c'] &&
  match_multiple ['a'; 'b'; '?'; 'c'] ['a'; 'b'; 'b'; 'c'] = false &&
  match_multiple ['a'; 'b'; '?'; 'c'; '?'] ['a'; 'b'; 'c'] && 
  match_multiple ['a'; 'b'; '?'; 'c'; '?'] ['a'; 'b'; 'c'; 'd']

let%test "match_multiple with star mark" =
  match_multiple ['a'; '*'] ['a'] &&
  match_multiple ['a'; '*'] ['a'; 'a'] &&
  match_multiple ['a'; '*'; 'b'] ['a'; 'a'; 'a'; 'b']
