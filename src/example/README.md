# Interactive Calculator Example
This example uses both the lexical analyser generator and parser generator to create an interactive calculator

## Source Files
### calculator.wbclex
This example lexer document demonstrates the use of the lexical analysis generation functions in wbclex. Note the
use of the `this->` prefix to access methods of the template base class

Output files:
* lexigen.h
* lexigen_table.h
* lexigen_table.cpp

### calculator.wbcparse
This example lexer document demonstrates the use of the parser generation functions in wbcparse. Note the
use of the `this->` prefix to access methods of the template base class

Output Files:
* LALRGenParser.h
* LALRGenParserTable.h
* LALRGenParserTable.cpp

### LRToken.h
This is the wbcparse token support class header, and is requred for wbcparse to work correctly

### main.cpp
This is the main entrypoint of this application and demonstrates the implementation pattern required to use this software. Note the base classes defined and used.

## Implementation Notes
`LexerBase` implements the methods required to forward the lexical tokens from the analyser to the parser. The use of Token::CreateToken and Token::CreateToken_VOID are required to generate the appropriate token type, and require the parameter to be the type declared in the parser document

`ParserBase` implements the logic required to respond to the syntax structures detected. Note that the type of each
expression is `float` and the type of the other methods are `void`

