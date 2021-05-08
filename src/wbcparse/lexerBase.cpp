#include "lexerBase.h"
#include "errorHandler.h"
#include <sstream>
#include <iostream>

CLexerBase::CLexerBase()
{
	m_errorHandler = nullptr;
}

void CLexerBase::SetErrorHandler(CErrorHandler* errorHandler)
{
	m_parser.SetErrorHandler(errorHandler);
	m_errorHandler = errorHandler;
}

void CLexerBase::EOL()
{
	m_errorHandler->IncLineNo();
}

void CLexerBase::respEOF()
{
	m_errorHandler->EmitError("end of file in response");
}

void CLexerBase::respEOL()
{
	m_errorHandler->IncLineNo();

}

void CLexerBase::typeEOF()
{
	m_errorHandler->EmitError("end of file in type expression");
}

void CLexerBase::typeEOL()
{
	m_errorHandler->IncLineNo();
}

void CLexerBase::unrecognized(const std::string& s)
{
	std::stringstream str;
  if(s != "\r" && s != "\f")
  {
    str << "unrecognized char '" << s << "'"; 
    m_errorHandler->EmitError(str.str());
  }
}


void CLexerBase::commentEOF()
{
	m_errorHandler->EmitError("end of file in comment");
}
void CLexerBase::commentEOL()
{
	m_errorHandler->IncLineNo();
}