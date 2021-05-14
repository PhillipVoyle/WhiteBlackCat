#include <iostream>

#include "LALRGenParser.h"
#include "LALRGenParserTable.h"
#include "lexigen.h"

class ParserBase
{
    bool error;
public:
    ParserBase() {
        error = false;
    }
    float add(float a, float b) {
        auto result = a + b;
        if (!error) {
            std::cout << a << " + " << b << " = " << result << std::endl;
        }
        return result;
    }
    float sub(float a, float b) {
        auto result = a - b;
        if (!error) {
            std::cout << a << " - " << b << " = " << result << std::endl;
        }
        return result;
    }
    float mul(float a, float b) {
        auto result = a * b;
        if (!error) {
            std::cout << a << " * " << b << " = " << result << std::endl;
        }
        return result;
    }
    float div(float a, float b) {
        auto result = a / b;
        if (!error) {
            std::cout << a << " / " << b << " = " << result << std::endl;
        }
        return result;
    }
    void print(float a) {
        if (!error) {
            std::cout << "result = " << a << std::endl;
        }
        std::cout << "calculator> " << std::flush;
        error = false;
    }
    float expectedExpression() {
        if (!error) {
            std::cerr << "expected expression" << std::endl;
        }
        error = true;
        return 0;
    }
    void blankLine() {
        std::cout << "calculator> " << std::flush;
        error = false;
    }
    template<typename T>
    void ParserError(std::shared_ptr<T> badToken) {
        if (!error) {
            std::cerr << "parser error" << std::endl;
        }
        error = true;
    }
    void Accept() {
        std::cout << "\nbye" << std::endl;
    }
};

class LexerBase
{
    CLALRGenParser<ParserBase> m_parser;
public:
    typedef CLALRGenParser<ParserBase> Parser;
    typedef typename Parser::Token Token;
    typedef int lexiType;
    LexerBase() {
    }
    void numberToken(std::string lexeme) {
        m_parser.step(Token::CreateToken<CLALRGenParserTable::tNumber>(atof(lexeme.c_str())));
    }
    void add() {
        m_parser.step(Token::CreateToken_VOID<CLALRGenParserTable::tAdd>());
    }
    void sub() {
        m_parser.step(Token::CreateToken_VOID<CLALRGenParserTable::tSub>());
    }
    void mul() {
        m_parser.step(Token::CreateToken_VOID<CLALRGenParserTable::tMul>());
    }
    void div(){
        m_parser.step(Token::CreateToken_VOID<CLALRGenParserTable::tDiv>());
    }
    void left_parenthesis() {
        m_parser.step(Token::CreateToken_VOID<CLALRGenParserTable::tLeftBracket>());
    }
    void right_parenthesis() {
        m_parser.step(Token::CreateToken_VOID<CLALRGenParserTable::tRightBracket>());
    }
    void endline() {
        m_parser.step(Token::CreateToken_VOID<CLALRGenParserTable::tEndLine>());
    }
    void whitespace() {
    }
    void eof() {
        m_parser.step(Token::CreateToken_VOID<CLALRGenParserTable::$>());
    }
    void unexpected(std::string lexeme) {
        std::cerr << "unexpected token: " << lexeme << std::endl;
    }
};

int main() {

    std::cout << "Interactive calculator demonstration:\n\n" << std::flush;
    std::cout << "calculator> " << std::flush;
    CLexigen<LexerBase> lexer;
    return lexer.scan(std::cin);
}