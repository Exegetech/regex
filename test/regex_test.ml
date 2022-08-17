let test_search_one_char () =
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"" ~text:"a");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"a" ~text:"a");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"." ~text:"z");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"" ~text:"h");
  Alcotest.(check bool) __LOC__ false (Regex.search ~pattern:"a" ~text:"b");
  Alcotest.(check bool) __LOC__ false (Regex.search ~pattern:"p" ~text:"");
  Alcotest.(check bool) __LOC__ false (Regex.search ~pattern:"" ~text:"")

let test_search_multiple_chars () =
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"abc" ~text:"abc");
  Alcotest.(check bool) __LOC__ false (Regex.search ~pattern:"abcd" ~text:"abc");
  Alcotest.(check bool) __LOC__ false (Regex.search ~pattern:"abc" ~text:"")

let test_search_with_marks () =
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"a.c" ~text:"abc");

  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"ab?c" ~text:"ac");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"ab?c" ~text:"abc");
  Alcotest.(check bool) __LOC__ false (Regex.search ~pattern:"ab?c" ~text:"abbc");

  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"a*" ~text:"a");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"a*" ~text:"aa");

  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:".?c" ~text:"ac");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:".?c" ~text:"c");

  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:".*c" ~text:"ac");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:".*c" ~text:"aac");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:".*c" ~text:"c");

  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"a*b?c" ~text:"abc");

  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"a*b?c" ~text:"aabc");

  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"a*b?c" ~text:"aabc");

  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"a*b?c" ~text:"aac");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"a*b?c" ~text:"ac");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"a*b?c" ~text:"c");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"^abc" ~text:"abc");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"^a*bc" ~text:"abc");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"^a*bc" ~text:"aabc");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"abc$" ~text:"abc");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"ab*c$" ~text:"abc");
  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"ab*c$" ~text:"abbc");

  Alcotest.(check bool) __LOC__ true (Regex.search ~pattern:"^abc$" ~text:"abc")

let () =
  let open Alcotest in
  run "Regex"
    [
      ("One char", [ test_case "Search one character" `Quick test_search_one_char ]);
      ("Multiple chars", [ test_case "Search multiple characters" `Quick test_search_multiple_chars ]);
      ("With marks", [ test_case "Search with marks" `Quick test_search_with_marks ]);
    ]
