#include "production.h"
#include "parserBase.h"
#include <iostream>
#include <vector>
#include "errorHandler.h"
#include <sstream>

CParserBase::CParserBase()
{
	m_nextProductions = NULL;
	m_associativity = IProduction::asNone;
	m_precedence = 0;
	m_errorHandler = NULL;
}

void CParserBase::SetErrorHandler(CErrorHandler* errorHandler)
{
	m_generator.SetErrorHandler(errorHandler);
	m_errorHandler = errorHandler;
}

void CParserBase::Accept()
{
	if(m_errorHandler->Ok())
	{
		m_generator.GenerateParser(m_productions);
	}
}

void CParserBase::addRule(const std::string& left, syntax_string_list_t& right, const std::string& response)
{
	if(!m_generator.checkVar(left))
	{
		std::stringstream str;
		str << " token " << left << " is undefined";
		m_errorHandler->EmitError(str.str());
	}
	std::auto_ptr<IToken> tokenLeft = IToken::Create(left);
	std::list<std::string>& list = *right;
	std::list<std::string>::iterator it;

	//tokens have been placed in the list in reverse order
	std::auto_ptr<ITokenList> tokenList;
	for(it = list.begin(); it != list.end(); it++)
	{
		if(!m_generator.checkVar(*it))
		{
			std::stringstream str;
			str << " token " << *it << " is undefined";
			m_errorHandler->EmitError(str.str());
		}
		std::auto_ptr<IToken> token = IToken::Create(*it);
		tokenList = ITokenList::Create(token, tokenList);
	}
	std::auto_ptr<IProduction> production = IProduction::Create(tokenLeft, tokenList, response);

	production->SetPrecedence(m_precedence);
	production->SetAssociativity(m_associativity);

  std::auto_ptr<IProductions> _empty;
	std::auto_ptr<IProductions> productions = IProductions::Create(production, _empty);
	IProductions* ptr = productions.get();

	if(m_productions.get() == NULL)
	{
		m_productions = productions;
	}
	else
	{
		m_nextProductions->SetProductions(productions);
	}
	m_nextProductions = ptr;
}

void CParserBase::setAssocLeft()
{
	m_precedence ++;
	m_associativity = IProduction::asLeft;
}

void CParserBase::setAssocRight()
{
	m_precedence ++;
	m_associativity = IProduction::asRight;
}

void CParserBase::setAssocNone()
{
	m_precedence ++;
	m_associativity = IProduction::asNone;
}

syntax_string_list_t CParserBase::addSyntaxStringToList(const std::string& str, syntax_string_list_t list)
{
	(*list).push_back(str);
	return list;
}

void CParserBase::assignVariable(const std::string& varname, const std::string& value)
{
	m_generator.assignVariable(varname, value);
}

void CParserBase::ParserError(TokenPtr tok)
{
	std::stringstream str;
	str << "syntax error, before " << GetTokenDescription(tok.get()) << "";
	m_errorHandler->EmitError(str.str());
}

void CParserBase::setTokenType(const std::string& sType)
{
	const char* type = sType.c_str();
	std::vector<std::string> typeVec;
	std::string typeName("");
	int typeID = 0;
	int typePre5 = 0;
	std::vector<char> stack;
	for(;;)
	{
		char c = *type;
		if(c == '\0')
		{
			break;
  		}
		else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		{
			if(typeID == 5 && typePre5 == 1)
			{
				typeName.append(" ", 1);
			}
			typeName.append(type, 1);
			typeID = 1;
		}
		else if(c == '<')
		{
			typeName.append(type, 1);
			typeID = 2;
			stack.push_back('<');
		}
		else if(c == '>')
		{
			if(typeID == 3 || (typeID == 5 && typePre5 == 3))
			{
				typeName.append(" ", 1);
			}
			typeName.append(type , 1);
			typeID = 3;
			if((stack.size() == 0) || (stack.back() != '<'))
			{
				m_errorHandler->EmitError("unexpected '>' in type expression");
			}
			else
			{
				stack.pop_back();
			}
		}
		else if(c == '"')
		{
			for(;;)
			{
				type++;
				if(*type == '"')
				{
					break;
				}
				else if(*type == '\\')
				{
					typeName.append(type, 1);
					type++;
					typeName.append(type, 1);
					type++;
				}
				else
				{
					typeName.append(type, 1);
					type++;
				}
			}
			typeID = 4;
		}
		else if(c == ' ' || c == '\n' || c == '\t')
		{
			if(typeID != 5)
			{
				typePre5 = typeID;
			}
			typeID = 5;
		}
		else
		{
			if(c == '(')
			{
				stack.push_back('(');
			}
			else if(c == ')')
			{
				if((stack.size() == 0) || (stack.back() != '('))
				{
					m_errorHandler->EmitError("unexpected ')' in type expression");
				}
				else
				{
					stack.pop_back();
				}
			}

			if(c == ',' && stack.size() == 0)
			{
				typeVec.push_back(typeName);
				typeName = "";
				typeID = 0;
			}
			else
			{
				typeName.append(type, 1);
				typeID = 6;
				if(c == ',')
				{
					typeName.append(" ", 1);
				}
			}
		}
		type++;
	}
	typeVec.push_back(typeName);
	if(stack.size() != 0)
	{
		m_errorHandler->EmitError("mismatched tokens in type specifier");
	}

	if(typeVec.size() == 1)
	{
		m_currentStoreType = typeVec[0];
		m_currentTransType = typeVec[0];
	}
	else if(typeVec.size() == 2)
	{
		m_currentStoreType = typeVec[0];
		m_currentTransType = typeVec[1];
	}
	else
	{
		m_currentStoreType = "void";
		m_currentTransType = "void";
		std::stringstream str;
		str <<"type expression has " << (int)typeVec.size() << " components, expects 1 or 2";
		m_errorHandler->EmitError(str.str());
	}
}

void CParserBase::addToken(const std::string& tokenName)
{
	if(m_generator.checkVar(tokenName))
	{
		std::stringstream str;
		str << "token " << tokenName << " already exists";
		m_errorHandler->EmitError(str.str());
	}
	else
	{
		m_generator.setType(tokenName, m_currentStoreType, m_currentTransType);
	}
}

syntax_string_list_t CParserBase::syntaxStringList()
{
	return syntax_string_list_t(new std::list<std::string>());
}

std::string CParserBase::GetTokenDescription(Token* ptr)
{
	CParserTable::TokenID id = ptr->GetTokenID();
	switch(id)
	{
	case CParserTable::tSemicolon: return "';'";
	case CParserTable::tVariableName:
		{
			std::stringstream str;
			str << "variable name " << ptr->GetData<CParserTable::tVariableName>();
			return str.str();
		}
	case CParserTable::tAssign: return "'='";
	case CParserTable::tLiteral:
		{
			std::stringstream str;
			str << "string literal " << ptr->GetData<CParserTable::tLiteral>();
			return str.str();
		}
	case CParserTable::tToken: return "'token'";
	case CParserTable::tTokenType: return "token type";
	case CParserTable::tIdentifier:
		{
			std::stringstream str;
			str << "identifier " << ptr->GetData<CParserTable::tIdentifier>();
			return str.str();
		}
	case CParserTable::tComma: return "','";
	case CParserTable::tProduction: return "'->'";
	case CParserTable::tResponse:
		{
			std::stringstream str;
			str << "response " << ptr->GetData<CParserTable::tResponse>();
			return str.str();
		}
	case CParserTable::tLeft: return "'left'";
	case CParserTable::tRight: return "'right'";
	case CParserTable::tNone: return "'noassoc'";
	case CParserTable::$: return "end of file";
	case CParserTable::program: return "program";
	case CParserTable::ntVariables: return "variables";
	case CParserTable::ntAssignVariable: return "variable assignment";
	case CParserTable::ntTokenDefs: return "token definitions";
	case CParserTable::ntTokenDef: return "token def";
	case CParserTable::ntTokenType: return "token type";
	case CParserTable::ntTokenNames: return "token names";
	case CParserTable::ntTokenNameList: return "token names";
	case CParserTable::ntRules: return "rules";
	case CParserTable::ntRule: return "rule";
	case CParserTable::ntRightSide: return "right side";
	default:
		return "Unknown";
	}
}
