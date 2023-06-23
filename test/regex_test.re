let testEmptyPattern = () => {
  let pattern = ""

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, true, result)

  let result = Regex.search(~pattern, ~text="abcdefg")
  Alcotest.(check(bool))(__LOC__, true, result)
}

let _testOneCharPattern = () => {
  let pattern = "a"

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xbx")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xax")
  Alcotest.(check(bool))(__LOC__, true, result);
}

let _testOneCharWithCaretPattern = () => {
  let pattern = "^"

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="abcd")
  Alcotest.(check(bool))(__LOC__, true, result);
}

let _testOneCharWithDollarPattern = () => {
  let pattern = "$"

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="abcd")
  Alcotest.(check(bool))(__LOC__, true, result);
}

let _testOneCharWithDotPattern = () => {
  let pattern = "."

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="a")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="ab")
  Alcotest.(check(bool))(__LOC__, true, result);
}

let _testOneCharWithQuestionPattern = () => {
  let pattern = "a?"

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="z")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="a")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="abcd")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="babce")
  Alcotest.(check(bool))(__LOC__, true, result);
}

let _testOneCharWithStarPattern = () => {
  let pattern = "a*"

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="z")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="a")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="aa")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="aaz")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="baaz")
  Alcotest.(check(bool))(__LOC__, true, result);
}

let _testMultipleCharsPattern = () => {
  let pattern = "abc"

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xxx")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xxxabcxx")
  Alcotest.(check(bool))(__LOC__, true, result);
}

let _testMultipleCharsWithCaretPattern = () => {
  let pattern = "^abc"

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="abc")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="abcxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxabcd")
  Alcotest.(check(bool))(__LOC__, false, result);
}

let _testMultipleCharsWithDollarPattern = () => {
  let pattern = "abc$"

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="abc")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="abcxxx")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xxxabc")
  Alcotest.(check(bool))(__LOC__, true, result);
}

let _testMultipleCharsWithDotPattern = () => {
  let pattern = "a.c"

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xxxabcxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxazcxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxazzcxxx")
  Alcotest.(check(bool))(__LOC__, false, result);
}

let _testMultipleCharsWithQuestionPattern = () => {
  let pattern = "ab?c"

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xxxacxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxabcxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxabbcxxx")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xxxazcxxx")
  Alcotest.(check(bool))(__LOC__, false, result);
}

let _testMultipleCharsWithStarPattern = () => {
  let pattern = "a*bc"

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xxxacxxx")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xxxbcxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxabcxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxaabcxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxabbcxxx")
  Alcotest.(check(bool))(__LOC__, false, result);
}

let _testMultipleCharsWithDotQuestionPattern = () => {
  let pattern = ".?c"

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xxxxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxcxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxacxxx")
  Alcotest.(check(bool))(__LOC__, true, result);
}

let _testMultipleCharsWithDotStarPattern = () => {
  let pattern = ".*c"

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xxxxxx")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xxxcxxx")
  Alcotest.(check(bool))(__LOC__, true, result);
}

let _testMultipleCharsWithComboPattern = () => {
  let pattern = "a*b?c."

  let result = Regex.search(~pattern, ~text="")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xxxxxx")
  Alcotest.(check(bool))(__LOC__, false, result);

  let result = Regex.search(~pattern, ~text="xxxcxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxacxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxbcxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxabcxxx")
  Alcotest.(check(bool))(__LOC__, true, result);

  let result = Regex.search(~pattern, ~text="xxxabbcxxx")
  Alcotest.(check(bool))(__LOC__, false, result);
}

let () = {
  open Alcotest

  run("Regex",
    [
      ("Empty pattern", [
        test_case("Emtpy pattern", `Quick, testEmptyPattern),
      ]),
      // ("One char pattern", [
      //   test_case("One char pattern", `Quick, testOneCharPattern),
      //   test_case("With caret pattern", `Quick, testOneCharWithCaretPattern),
      //   test_case("With dollar pattern", `Quick, testOneCharWithDollarPattern),
      //   test_case("With dot pattern", `Quick, testOneCharWithDotPattern),
      //   test_case("With question pattern", `Quick, testOneCharWithQuestionPattern),
      //   test_case("With star pattern", `Quick, testOneCharWithStarPattern),
      // ]),
      // ("Multiple chars pattern", [
      //   test_case("Multiple chars pattern", `Quick, testMultipleCharsPattern),
      //   test_case("With caret pattern", `Quick, testMultipleCharsWithCaretPattern),
      //   test_case("With dollar pattern", `Quick, testMultipleCharsWithDollarPattern),
      //   test_case("With dot pattern", `Quick, testMultipleCharsWithDotPattern),
      //   test_case("With question pattern", `Quick, testMultipleCharsWithQuestionPattern),
      //   test_case("With star pattern", `Quick, testMultipleCharsWithStarPattern),
      //   test_case("With dot question pattern", `Quick, testMultipleCharsWithDotQuestionPattern),
      //   test_case("With dot star pattern", `Quick, testMultipleCharsWithDotStarPattern),
      //   test_case("Free pattern", `Quick, testMultipleCharsWithComboPattern),
      // ]),
    ]
  )
}