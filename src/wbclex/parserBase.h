#pragma once
#include <string>
#include <map>

#include "LRToken.h"
#include "regularExpression.h"

#include "parser.h"

#include "lexerGenerator.h"

class CErrorHandler;

typedef CLRToken<CParserTable::TokenID> Token;
typedef std::shared_ptr<Token> TokenPtr;

class CParserBase
{
	std::map<std::string, CAdaptPtr<CRegularExpression> > m_defs;
	CErrorHandler* m_errorHandler;
	CLexerGenerator m_generator;
	std::string m_state;
protected:
	CParserBase();
	virtual ~CParserBase();
	void Accept();
	void ParserError(TokenPtr token);

	void addEOFEvent(const std::string& response);
	void addEvent(regularExpressionPtr r, const std::string& response);
	void assignDef(const std::string& def, regularExpressionPtr r);
	void assignVar(const std::string& varName, const std::string& varValue);
	void setState(const std::string& stateName);

	std::string GetTokenName(TokenPtr token);
public:
	void SetErrorHandler(CErrorHandler* errorHandler);
	regularExpressionPtr GetDef(const std::string& defName);
	regularExpressionPtr regCat(regularExpressionPtr r1, regularExpressionPtr r2);
	regularExpressionPtr regNil();
	regularExpressionPtr regOr(regularExpressionPtr r1, regularExpressionPtr r2);
	regularExpressionPtr regPlus(regularExpressionPtr r);
	regularExpressionPtr regQMark(regularExpressionPtr r);
	regularExpressionPtr regStar(regularExpressionPtr r);
};