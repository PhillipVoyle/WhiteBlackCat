#pragma once

#include <string>

class CErrorHandler
{
	int m_lineNo;
	std::string m_filename;
	bool m_bError;
public:
	CErrorHandler();
	virtual ~CErrorHandler();
	void SetFilename(const std::string& filename);
	void EmitError(const std::string& error, int lineNo);
	void EmitError(const std::string& error);
	void IncLineNo();
	bool Ok();
};