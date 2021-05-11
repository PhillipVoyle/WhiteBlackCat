# wbclex
This software is for generating lexical analysers

## How to use this software
wbclex requires a single text file as input, that text file is divided into 3 sections variables, definitions and states.

### Variable Section
The following variables can be configured in order to change the output of the lexical analyser generator

    $LEXERNAME      = "CLexer"
    $TABLENAME      = "CLexerTable"
    $HEADER         = "lexer.h"
    $TABLESOURCE    = "table.cpp"
    $TABLEHEADER    = "table.h"

| Variable Name   | Description                       |        Default      |
| ----------------|-----------------------------------|---------------------|
| `$LEXERNAME`    | The name of the Lexer class       | `CLexigen`          |
| `$TABLENAME`    | The name of the Lexer table class | `CLexigenTable`     |
| `$HEADER`       | The Lexer header filename         | `lexigen.h`         |
| `$TABLEHEADER`  | The table header file             | `lexigen_table.h`   |
| `$TABLESOURCE`  | The name of the table file        | `lexigen_table.cpp` |

### Definitions Section
This section lets the programmer set out some patterns that they expect to reuse, these will not be recognised specifically but can be brought into rules using the `{name}` mechanism in the states and rules section.

    whitespace = %[ \t]+%
    identifier = %[a-zA-Z][0-9a-zA-Z]*%

### States and rules
In this final section the programmer can represent the responses to any patterns matched by the analyser. Rules can be grouped into states, with the first optionally prefixed with `#STATE <name>` and each rule beginning with the `ON` keyword. The programmer can opt to:
 * return from a response, which will cause the lexical analyser to return to the calling code. The return type must be configured correctly.
 * throw an exception and cach that exception in the calling code
 * call the `setState` method and pass in a state name in the form `Table::<stateName>`
 * perform some other action, and not return from the analyser. This will cause the scanner to continue processing

The analyser supports either calling an internal parser or returning a lexeme to an external parser. Care must be taken to ensure that the return type of the lexical analyser is compatible, currently it must be able to be constructed from EOF (-1).

Rules are of the format `ON %<regular-expression>% {<response>}` and are evaluated with longer matches preferred, but in the case that two input strings match two patterns, the pattern listed first will take precedence. In the example below, the input string `item` would match the pattern `%item%` but `items` would match the more general `%${identifier}%` pattern given the definition in the Definitions section above.

```
    #STATE stStart
        ON %\n%             { }
        ON %"/*"%           { setState(Table::stComment); }
        ON %item%           { }
        ON %${identifier}%  { return ReturnType(lexeme); }
        ON %.%              { throw std::runtime_error("unexpected"); }
        ON eof              { this->onEof(); }
    #STATE = "stComment"
        ON %"*/"%           {setState(Table::stStart);}
        ON %.%			{ }
        ON %\n%			{ }
        ON eof			{this->commentEOF(); }
```

### Using the output files in your project

Add the `lexigen_table.cpp` source file to your project, and include `lexigen.h` into the source file you want to use as an entry point to the lexical analyser. Specify a class that will be used to contain your internal logic and construct a `CLexer<YourClassName>` class in order to instantiate the lexer. The CLexer class will inherit from the specified template parameter, so any methods declared public or protected in your class will be accessible from within the rules in your wbclex file. Then call `lexer.scan(stream)` passing in a `std::istream` and the lexical analyser will scan the file until either an EOF is encountered or one of your rules elects to return from the lexer. The lexical analyser will maintain it's state between calls to scan. Some example code is listed below:

```
#include <iostream>
#include "lexigen.h"

class LexerBase
{
public:
    struct ReturnType
    {
        ReturnType(int) { //allow construction using EOF
        }
        ReturnType(std::string) {
        }
    };
    typedef ReturnType lexiType; //result type of lexical analyser

    LexerBase(int argc, char**argv)
    {
        /* initialisation logic */
    }
    void commentEof()
    {
        std::cout << "commented eof" << std::endl;
    }
    void onEof()
    {
        std::cout << "eof" << std::endl;
    }
};

int main(int argc, char**argv)
{
    CLexer<LexerBase> lexer(argc, argv); // std::forward-ed arbitrary constructor parameters
    auto result = lexer.scan(std::cin);
    return 0;
}
```
