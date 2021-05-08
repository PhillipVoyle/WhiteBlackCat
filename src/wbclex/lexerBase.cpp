#include "lexerBase.h"
#include "errorHandler.h"
#include <sstream>
#include "utils.h"

void CLexerBase::commentEOF()
{
	m_errorHandler->EmitError("unexpected end of file");
}

void CLexerBase::commentEOL()
{
	m_errorHandler->IncLineNo();
}

void CLexerBase::defBadChar(char c)
{

  std::stringstream str;
  str << "unexpected character '" << c << "'";
  m_errorHandler->EmitError(str.str());
}

void CLexerBase::unexpectedChar(char c)
{
  if(c != '\r')
  {
    std::stringstream str;
    str << "unexpected character '" << c << "'";
    m_errorHandler->EmitError(str.str());
  }
}

void CLexerBase::defEOF()
{
	m_errorHandler->EmitError("unexpected end of file");
}

void CLexerBase::defEOL()
{
	m_errorHandler->EmitError("unexpected newline in regular expression");
	m_errorHandler->IncLineNo();
}

void CLexerBase::OnEOL()
{
	m_errorHandler->IncLineNo();
}

regularExpressionPtr CLexerBase::rChar(char c)
{
	return CRegularExpression::CreateCharNode(c);
}

regularExpressionPtr CLexerBase::rCharClass(const std::string& sText)
{
	bool charInRange[NCHARS];
	int nIndex = 0;
	int nlen = (int)sText.length();
	bool acceptInRange = true;
	assert(sText[nIndex] == '[');
	nIndex = 1;
	int nChar;
	for(nChar = 0; nChar < NCHARS; nChar++)
	{
		charInRange[nChar] = false;
	}
	if(sText[nIndex] == '^')
	{
		acceptInRange = false;
		nIndex++;
	}
	for(; nIndex < nlen;)
	{
		char c = sText[nIndex];
		if(c == ']')
		{
			assert(nIndex == nlen - 1);
			break;
		}
		else if(c == '\\')
		{
			nIndex++;
			c = Utils::EscapeChar(sText[nIndex]);
			charInRange[(unsigned)c] = true;
			nIndex++;
		}
		else
		{
			nIndex++;
			if(sText[nIndex] == '-')
			{
				nIndex++;
				char c2 = sText[nIndex];
				assert(c2 != ']');
				if(c2 == '\\')
				{
					nIndex++;
					c2 = Utils::EscapeChar(sText[nIndex]);
				}
				unsigned cChar;
				for(cChar = (unsigned)c; cChar <= (unsigned) c2; cChar++)
				{
					charInRange[cChar] = true;
				}
				nIndex++;
			}
			else
			{
				charInRange[(unsigned)c] = true;
			}
		}
	}

	regularExpressionPtr regexp;
	for(nChar = 0; nChar < NCHARS; nChar++)
	{
		if(charInRange[nChar] == acceptInRange)
		{
			char c = (char) nChar;
			regularExpressionPtr rc = rChar(c);
			if(regexp.get() == nullptr)
			{
				regexp = rc;
			}
			else
			{
				regexp = m_parser.regOr(regexp, rc);
			}
		}
	}
	return regexp;
}

regularExpressionPtr CLexerBase::rDef(const std::string& lexeme)
{
	std::string s("{");
	s.append(lexeme);
	return m_parser.GetDef(s);
}

regularExpressionPtr CLexerBase::rDefUnterm(const std::string& lexeme)
{
	std::string s("{");
	s.append(lexeme);
	s.append("}", 1);
	return m_parser.GetDef(s);
}

regularExpressionPtr CLexerBase::rDot()
{
	regularExpressionPtr regexp;
	for(int nChar = 0; nChar < NCHARS; nChar++)
	{
		char c = (char) nChar;
		if(c != '\n')
		{
			regularExpressionPtr rc = rChar(c);
			if(regexp.get() == nullptr)
			{
				regexp = rc;
			}
			else
			{
				regexp = m_parser.regOr(regexp, rc);
			}
		}
	}
	return regexp;
}

regularExpressionPtr CLexerBase::rString(const std::string& stext)
{
	regularExpressionPtr regexp;
	int nlen = (int)stext.length();
	assert(stext[0] == '\"');
	int index = 1;
	for(index = 1; index < nlen; index++)
	{
		if(stext[index] == '\"')
		{
			break;
		}
		assert(index < nlen - 1);
		char c = stext[index];
		if(c == '\\')
		{
			index++;
			c = Utils::EscapeChar(c);
		}
		regularExpressionPtr rc = rChar(c);
		if(regexp.get() == nullptr)
		{
			regexp = rc;
		}
		else
		{
			regexp = m_parser.regCat(regexp, rc);
		}
	}
	return regexp;
}

regularExpressionPtr CLexerBase::rEscape(const std::string& lexeme)
{
	char cEsc = Utils::EscapeChar(lexeme[1]);
	return rChar(cEsc);
}

void CLexerBase::regexpEOL()
{
	m_errorHandler->EmitError("unexpected newline in regular expression");
	m_errorHandler->IncLineNo();
}

void CLexerBase::regexpEOF()
{
	m_errorHandler->EmitError("unexpected end of file in regular expression");
}

void CLexerBase::respEOF()
{
	m_errorHandler->EmitError("unexpected end of file in response");
}

void CLexerBase::respEOL()
{
	m_errorHandler->IncLineNo();
}

void CLexerBase::SetErrorHandler(CErrorHandler* errorHandler)
{
	m_errorHandler = errorHandler;
	m_parser.SetErrorHandler(errorHandler);
}