# wbcparse
This software uses the LALR parser algorithm to generate parser tables for C++. The generated code is intended to be
type safe and should allow the use of C++ standard types like `vector`, `string`, and `shared_ptr` to be used to
represent your syntax tree.

## How to use this software
`wbcparse` takes a single input file split into 3 sections: variables, tokens, and rules.

### Variables Section
The variables section allows customisation of the parser output files and type names, listed in the table below


| Variable        | Description                            | Default Value            |
| --------------- | -------------------------------------- |------------------------- |
| `$PARSERNAME`   | The generated parser class             | `CLALRGenParser`         |
| `$PARSERHEADER` | The generated parser file              | `LALRGenParser.h`        |
| `$TABLENAME`    | The generated parser table class       | `CLALRGenParserTable`    |
| `$TABLEHEADER`  | The generated parser table header      | `LALRGenParserTable.h`   |
| `$TABLESOURCE`  | The generated parser table source file | `LALRGenParserTable.cpp` |

### Tokens Section

The tokens section can be used to specify the types used for each token. It's recommended that you use typedefs here
if your type names are complex. You should specify types for each terminal and nonterminal that you intend to use in your grammar below

```
    token<std::string> tVariableName, tLiteral, tIdentifier;
```

### Rules Section

The rules section specifies a list of LALR Grammar productions and C++ code that will be executed to perform the
reduction rule when the production is recognised by the parser. Tokens in the right side of the rule are named
`$1`, `$2` etc.. and the token on the right side is named `$$`. These will be written directly into the C++ source
file for the parser. Tokens with type `void` will not be assigned a variable

The first rule listed in the rules section will be treated as the root of the grammar and be used to generate the start state.

Rules are in the form:

```
    nonterminal -> [tokens] { <response> }
```

In the example below the an assignment statement is constructed from an identifier and an expression. Token tEquals and tSemicolon have type void, tIdentifier is of type string, and ntExpression is likely a smart pointer to an abstract class and likely containing a concrete expression implementation

```
    ntAssignmentStatement -> tIdentifier tEquals ntExpression tSemicolon {
        std::cout << "assignment detected" << std::endl;
        $$ = std::make_shared<AssignmentStatement>($1, $3);
    }
```


#### Precedence and associativity

Groups of rules can be separated using the `left`, `right` or `noassoc` keywords. This mechanism can be used to implement operator precedence and left or right derivations automatically given an ambiguous grammar. The rule groups closer to the end of the file have higher precedence, i.e bind more tightly. Choosing `left` will cause a reduction to occur in the case of an ambiguity that causes a shift/reduce conflict, whereas choosing `right` will prefer a shift operation. Choosing `noassoc` will not favour either case and in the event of a shift/reduce ambiguity an error will be reported instead. In the case of a reduce/reduce conflict, the rule with the higher precedence is chosen.


