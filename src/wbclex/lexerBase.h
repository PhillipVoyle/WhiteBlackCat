#pragma once
#include "parserBase.h"
#include "lexigen.h"
class CErrorHandler;

class CLexerBase
{
	CErrorHandler *m_errorHandler;
	static const int NCHARS = 128;
protected:
	CParser<CParserBase> m_parser;
	std::string m_response;
	int m_nBraces;
	typedef int lexiType;
	void commentEOF();
	void commentEOL();
	void defBadChar(char c);
	void unexpectedChar(char c);
	void defEOF();
	void defEOL();
	void OnEOL();
	regularExpressionPtr rChar(char c);
	regularExpressionPtr rCharClass(const std::string& lexeme);
	regularExpressionPtr rDef(const std::string& lexeme);
	regularExpressionPtr rDefUnterm(const std::string& lexeme);
	regularExpressionPtr rDot();
	regularExpressionPtr rString(const std::string& lexeme);
	regularExpressionPtr rEscape(const std::string& lexeme);
	void regexpEOL();
	void regexpEOF();
	void respEOF();
	void respEOL();
public:
	void SetErrorHandler(CErrorHandler* errorHandler);
};