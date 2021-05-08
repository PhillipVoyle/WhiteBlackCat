#pragma once

#include <string>
#include <algorithm>

#include "parserTypes.h"
#include "LRToken.h"
#include "parserTable.h"
#include "parser.h"

#include "lalrGenerator.h"

typedef CLRToken<CParserTable::TokenID> Token;
typedef std::shared_ptr<Token> TokenPtr;

class CErrorHandler;

class CParserBase
{
	CLALRGenerator m_generator;
	std::string m_currentStoreType;
	std::string m_currentTransType;
	std::shared_ptr<IProductions> m_productions;
	IProductions* m_nextProductions;

	int m_precedence;
	IProduction::Associativity m_associativity;
	CErrorHandler* m_errorHandler;
protected:
	CParserBase();
	std::string GetTokenDescription(Token* ptr);
	void Accept();
	void addRule(const std::string& left, syntax_string_list_t& right, const std::string& response);
	syntax_string_list_t addSyntaxStringToList(const std::string& string, syntax_string_list_t list);
	void assignVariable(const std::string& varname, const std::string& value);
	void ParserError(TokenPtr tok);
	void setAssocLeft();
	void setAssocRight();
	void setAssocNone();

	void addToken(const std::string& varname);
	void setTokenType(const std::string& type);
	syntax_string_list_t syntaxStringList();

public:
	void SetErrorHandler(CErrorHandler* errorHandler);
};