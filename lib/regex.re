let matchOne = (pattern: option(char), text: option(char)): bool => {
 switch (pattern, text) {
  | (None, _)
  | (_, None) => false
  | (Some('.'), _) => true
  | (_, _) => pattern == text
 }
}

let rec matchMultiple = (pattern: list(char), text: list(char)): bool => {
 switch (pattern, text) {
  | ([], _)
  | (['$'], []) => true
  | (_, []) => false
  | ([_, '?', _], _) => matchQuestion(pattern, text)
  | ([_, '*', _], _) => matchStar(pattern, text)
  | ([p, ...ps], [t, ...ts]) => {
   let p = Some(p)
   let t = Some(t)

   matchOne(p, t) && matchMultiple(ps, ts)
  }
 }
}

and matchQuestion = (pattern: list(char), text: list(char)): bool => {
 switch (pattern, text) {
  | ([p, _, ...ps], [t, ...ts]) => {
   let p = Some(p)
   let t = Some(t)

   matchOne(p, t) && matchMultiple(ps, ts) || matchMultiple(ps, text)
  }
  | (_, _) => {
   raise(Exit)
  }
 }
}

and matchStar = (pattern: list(char), text: list(char)): bool => {
 switch (pattern, text) {
  | ([p, _, ...ps], [t, ...ts]) => {
   let p = Some(p)
   let t = Some(t)

   matchOne(p, t) && matchMultiple(pattern, ts) || matchMultiple(ps, text)
  }
  | (_, _) => raise(Exit)
 }
}

let search = (~pattern: string, ~text: string): bool => {
 let pattern = Utils.toList(pattern)
 let text = Utils.toList(text)

 switch (pattern, text) {
  | (['^', ...pattern], text) => matchMultiple(pattern, text)
  | (pattern, text) => {
   let pattern = ['.', '*'] @ pattern

   matchMultiple(pattern, text)
  }
 }
}

let%test "matchOne pattern and text are None" = {
 let pattern = None
 let text = None

 matchOne(pattern, text) == false
}

let%test "matchOne pattern is None" = {
 let pattern = None
 let text = Some('a')

 matchOne(pattern, text) == false
}

let%test "matchOne text is None" = {
 let pattern = Some('a')
 let text = None

  matchOne(pattern, text) == false
}

let%test "matchOne pattern is '.'" = {
 let pattern = Some('.')
 let text = Some('a')

 matchOne(pattern, text)
}

let%test "matchOne pattern and text are same" = {
 let pattern = Some('b')
 let text = Some('b')

 matchOne(pattern, text)
}

let%test "matchOne pattern and text are not same" = {
 let pattern = Some('b')
 let text = Some('c')

 matchOne(pattern, text) == false
}

let%test "matchMultiple empty pattern empty text" = {
 let pattern = []
 let text = []

 matchMultiple(pattern, text)
}

let%test "matchMultiple empty pattern non empty text" = {
  let pattern = []
  let text = ['f', 'o', 'o']

 matchMultiple(pattern, text)
}

let%test "matchMultiple $ pattern with empty text" = {
  let pattern = ['$']
  let text = []

 matchMultiple(pattern, text)
}

let%test "matchMultiple non empty pattern with empty text" = {
 let pattern = ['a']
 let text = []

 matchMultiple(pattern, text) == false
}

let%test "matchMultiple pattern and text are the same chars and length" = {
 let pattern = ['f', 'o', 'o']
 let text = ['f', 'o', 'o']

 matchMultiple(pattern, text)
}

let%test "matchMultiple pattern and text are not the same chars but same length" = {
 let pattern = ['f', 'o', 'o']
 let text = ['f', 'o', 's']

 matchMultiple(pattern, text) == false
}

let%test "matchMultiple pattern has greater length than text" = {
 let pattern = ['f', 'o', 'o']
 let text = ['f', 'o', 'o', 's']

 matchMultiple(pattern, text)
}

let%test "matchMultiple pattern has lesser length than text" = {
 let pattern = ['f', 'o', 'o', 's']
 let text = ['f', 'o', 'o']

 matchMultiple(pattern, text) == false
}

let%test "matchMultiple with question mark" = {
 let pattern = ['a', 'b', '?', 'c']

 let text1 = ['a', 'c']
 let text2 = ['a', 'b', 'c']
 let text3 = ['a', 'b', 'd', 'c']

 matchMultiple(pattern, text1) &&
 matchMultiple(pattern, text2) &&
 matchMultiple(pattern, text3) == false
}

let%test "matchMultiple with question mark" = {
 let pattern = ['a', 'b', '?', 'c', '?']

 let text1 = ['a']
 // let text2 = ['a', 'b', 'c', 'd']

 matchMultiple(pattern, text1)
 //  &&
 // matchMultiple(pattern, text2)
}
  // match_multiple ['a'; 'b'; '?'; 'c'; '?'] ['a'; 'b'; 'c'; 'd']

let%test "match_multiple with star mark" = {
 let pattern = ['a', '*']

 let text1 = ['a']

 matchMultiple(pattern, text1)
  // match_multiple ['a'; '*'] ['a'] &&
  // match_multiple ['a'; '*'] ['a'; 'a'] &&
  // match_multiple ['a'; '*'; 'b'] ['a'; 'a'; 'a'; 'b']

}
