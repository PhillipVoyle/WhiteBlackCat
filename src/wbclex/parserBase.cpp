#include "LRToken.h"
#include "regularExpression.h"
#include "parserBase.h"
#include "errorHandler.h"
#include <sstream>

CParserBase::CParserBase()
{
	m_errorHandler = NULL;
	m_state = "\"stStart\"";
}

void CParserBase::SetErrorHandler(CErrorHandler* errorHandler)
{
	m_generator.setErrorHandler(errorHandler);
	m_errorHandler = errorHandler;
}

CParserBase::~CParserBase()
{

}

regularExpressionPtr CParserBase::GetDef(const std::string& defName)
{
	std::map<std::string, CAdaptPtr<CRegularExpression> >::iterator it = m_defs.find(defName);
	if(it == m_defs.end())
	{
		std::stringstream str;
		str << "undefined regular definition: " << defName;
		m_errorHandler->EmitError(str.str());
		return regularExpressionPtr();
	}
	else
	{
		return it->second.m_ptr->clone();
	}
}

void CParserBase::Accept()
{
	if(m_errorHandler->Ok())
	{
		m_generator.Process();
		if(m_errorHandler->Ok())
		{
			m_generator.Export();
		}
	}
}

std::string CParserBase::GetTokenName(TokenPtr token)
{
	switch(token->GetTokenID())
	{
	case CParserTable::tVariableName:
		{
			std::stringstream str;
			str << "variable name " << token->GetData<CParserTable::tVariableName>();
			return str.str();
		}
	case CParserTable::tAssign:
		return "'='";
	case CParserTable::tLiteral:
		return "literal";
	case CParserTable::tIdentifier:
		{
			std::stringstream str;
			str << "identifier " << token->GetData<CParserTable::tIdentifier>();
		return str.str();
		}
	case CParserTable::tBeginRegexp:
	case CParserTable::tFinishedRegexp:
		return "'%'";
	case CParserTable::tState:
		return "'STATE'";
	case CParserTable::tOn:
		return "'ON'";
	case CParserTable::tResponse:
		return "response";
	case CParserTable::tEOF:
		return "'eof'";
	case CParserTable::tOr:
		return "'|'";
	case CParserTable::tPlus:
		return "'+'";
	case CParserTable::tStar:
		return "'*'";
	case CParserTable::tQMark:
		return "'?'";
	case CParserTable::tRegexp:
		return "regular expression";
	case CParserTable::tOpen:
		return "'('";
	case CParserTable::tClose:
		return "')'";
	case CParserTable::$:
		return "end of file";
	case CParserTable::ntProgram:
		return "program";
	case CParserTable::ntRegexp:
		return "regular expression";
	case CParserTable::ntAssignVariables:
		return "variable assignment";
	case CParserTable::ntAssignDefinitions:
		return "regular definition";
	case CParserTable::ntInitStates:
		return "state definitions";
	case CParserTable::ntStateAssignment:
		return "state assignment";
	case CParserTable::ntInitOneState:
		return "state definition";
	case CParserTable::ntEvents:
		return "events";
	case CParserTable::ntEvent:
		return "event";
	default:
		return "Unknown";
	}
}

void CParserBase::ParserError(TokenPtr token)
{
	std::stringstream str;
	str << "parser error, before " << GetTokenName(token);
	m_errorHandler->EmitError(str.str());
}

void CParserBase::addEOFEvent(const std::string& response)
{
	m_generator.addEOFEvent(m_state, m_generator.registerResponse(response));
}

void CParserBase::addEvent(regularExpressionPtr r, const std::string& response)
{
  regularExpressionPtr ptr = CRegularExpression::CreateEndNode(m_generator.registerResponse(response));
  regularExpressionPtr cat = CRegularExpression::CreateCatNode(r, ptr);
	m_generator.addEvent(m_state, cat);
}

void CParserBase::assignDef(const std::string& def, regularExpressionPtr r)
{
	std::string ind("{");
	ind.append(def);
	ind.append("}");
	m_defs[ind].m_ptr = r;
}

void CParserBase::assignVar(const std::string& varName, const std::string& varValue)
{
	m_generator.setVar(varName, varValue);
}

regularExpressionPtr CParserBase::regCat(regularExpressionPtr r1, regularExpressionPtr r2)
{
	if(r1.get() == NULL)
	{
		return r2;
	}
	if(r2.get() == NULL)
	{
		return r1;
	}
	return CRegularExpression::CreateCatNode(r1, r2);
}

regularExpressionPtr CParserBase::regNil()
{
	return regularExpressionPtr();
}

regularExpressionPtr CParserBase::regOr(regularExpressionPtr r1, regularExpressionPtr r2)
{
	return CRegularExpression::CreateOrNode(r1, r2);
}

regularExpressionPtr CParserBase::regPlus(regularExpressionPtr r)
{
	return CRegularExpression::CreatePlusNode(r);
}

regularExpressionPtr CParserBase::regQMark(regularExpressionPtr r)
{
	return CRegularExpression::CreateQMarkNode(r);
}

regularExpressionPtr CParserBase::regStar(regularExpressionPtr r)
{
	return CRegularExpression::CreateStarNode(r);
}

void CParserBase::setState(const std::string& stateName)
{
	m_state = stateName;
}
