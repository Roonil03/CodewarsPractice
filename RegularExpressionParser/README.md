# Regular expression parser
## 2 kyu
### Description:
Your task is to implement a simple regular expression parser. We will have a parser that outputs the following AST of a regular expression:
```
RegExp* normal (char);                     // ^ A character that is not in "()*|."
RegExp* any ();                            // ^ Any character
RegExp* zeroOrMore (RegExp *starred);      // ^ Zero or more occurances of the same regexp
RegExp* orr (RegExp* left, RegExp* right); // ^ A choice between 2 regexps
RegExp* str (RegExp *first);               // ^ A sequence of regexps, first element
RegExp* add (RegExp *str, RegExp* next);   // ^ A sequence of regexps, additional element
```
In C, C++, and C#:
- The functions normal(), any(), zeroOrMore(), or(), str() and add() are pre-written for you; use them.
    - In C#, they are static methods of the Reg class
- `add(str, next)` is not really a distinct node type of the AST; it is a helper function that appends a new item to an existing str sequence. `str()` should be called only to create the first item of the sequence, and `add()` should be called for the following items.

As with the usual regular expressions, Any is denoted by the `'.'` character, ZeroOrMore is denoted by a subsequent `'*'` and Or is denoted by `'|'`. Brackets, `(` and `)`, are allowed to group a sequence of regular expressions into the Str object.

Or is not associative, so "`a|(a|a)`" and "`(a|a)|a`" are both valid regular expressions, whereas "`a|a|a`" is not.

Operator precedences from highest to lowest are: `*`, sequencing and `|`. Therefore the followings hold:
```
"ab*"     -> add (str (normal ('a')), zeroOrMore (normal ('b')))
"(ab)*"   -> zeroOrMore (add (str (normal ('a')), normal ('b')))
"ab|a"    -> orr (add (str (normal ('a')), normal ('b')), normal ('a'))
"a(b|a)"  -> add (str (normal ('a')), orr (normal ('b'), normal ('a')))
"a|b*"    -> orr (normal ('a'), zeroOrMore (normal ('b')))
"(a|b)*"  -> zeroOrMore (orr (normal ('a'), normal ('b')))
```
Some examples:
```
"a"          -> normal ('a')
"ab"         -> add (str (normal ('a')), normal ('b'))
"a.*"        -> add (str (normal ('a')), zeroOrMore (any ()))
"(a.*)|(bb)" -> orr (add (str (normal ('a')), zeroOrMore (any ())), add (str (normal ('b')), normal (b)))
```
The followings are invalid regexps and the parser should return Nothing in Haskell / NULL in C / nullptr in C++ / null in JavaScript or C# / None in Python or Rust / new Void() in Java/Void() in Kotlin:

`""`, `")("`, `"*"`, `"a("`, `"()"`, `"a**"`, etc.

Feel free to use any parser combinator libraries available on codewars, or implement the parser "from scratch".