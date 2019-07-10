
#include "parserBase.h"
#include "lexigen.h"

class CErrorHandler;

class CLexerBase
{
protected:
	std::string m_string;
	int m_nDepth;
	CParser<CParserBase> m_parser;
	CErrorHandler* m_errorHandler;

	typedef int lexiType;

	void EOL();
	void respEOF();
	void respEOL();
	void typeEOF();
	void typeEOL();
	void commentEOF();
	void commentEOL();
	void unrecognized(const std::string& s);
public:
	CLexerBase();
	void SetErrorHandler(CErrorHandler* errorHandler);
};