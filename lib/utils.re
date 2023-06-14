let toList = (str: string): list(char) => {
  let length = String.length(str)
  let charGetter = String.get(str)

  List.init(length, charGetter)
}