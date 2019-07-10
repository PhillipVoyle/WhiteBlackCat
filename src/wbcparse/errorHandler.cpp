#include "errorHandler.h"
#include <iostream>

CErrorHandler::CErrorHandler()
{
	m_lineNo = 1;
	m_bError = false;
}

CErrorHandler::~CErrorHandler()
{
}

bool CErrorHandler::Ok()
{
	return !m_bError;
}

void CErrorHandler::SetFilename(const std::string& filename)
{
	m_filename = filename;
}

void CErrorHandler::EmitError(const std::string& error, int lineNo)
{
	m_bError = true;
	std::cerr << m_filename << ":" << lineNo << ":" << error << std::endl;
}

void CErrorHandler::EmitError(const std::string& error)
{
	EmitError(error, m_lineNo);
}

void CErrorHandler::IncLineNo()
{
	m_lineNo++;
}