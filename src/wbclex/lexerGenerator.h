#pragma once
#include "adaptPtr.h"
#include "regularExpression.h"

#include <string>
#include <map>
#include <vector>
#include <iostream>

class CErrorHandler;

class CLexerGenerator
{
	static const int NCOLS = 16;
	typedef std::vector<int> PositionSet;
	static const PositionSet kEmptyPositionSet;

	struct StateData
	{
		int m_transitions[128];
		int m_announce;
	};
	struct nodeData
	{
		bool m_bEnd;
		int m_dataID;
		nodeData(bool bEnd, int dataID)
		{
			m_bEnd = bEnd;
			m_dataID = dataID;
		}
		bool operator==(const nodeData& data) const
		{
			return (m_bEnd == data.m_bEnd) && (m_dataID == data.m_dataID);
		}
		bool operator<(const nodeData& data) const
		{
			if(m_bEnd)
			{
				if(data.m_bEnd)
				{
					return m_dataID < data.m_dataID;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if(data.m_bEnd)
				{
					return true;
				}
				else
				{
					return m_dataID < data.m_dataID;
				}
			}
		}
	};

	struct dState
	{
		std::vector<int> state;
	} kEmptyState;

	typedef std::vector<StateData> STATEDATAVECTOR;
	typedef std::map<std::string, STATEDATAVECTOR> STATEDATAVECTORMAP;

	STATEDATAVECTORMAP m_stateData;

	typedef CAdaptPtr<CRegularExpression> regPtr;
	std::map<std::string, regPtr> m_regularExpressions;
	std::map<std::string, int> m_eofEvents;
	std::map<std::string, std::string> m_vars;
	std::vector<std::string> m_responses;
	CErrorHandler* m_errorHandler;
	int AssignPositionIDs(CRegularExpression* exp, int id);
	void ComputeFollowPos(CRegularExpression* exp, std::vector<PositionSet>& followPos);
	void ComputeStates(std::vector<PositionSet> followPos, CRegularExpression* exp, std::vector<StateData>& stateData);
	void GetDataAtPositions(CRegularExpression *exp, std::vector<nodeData>& dataAtPosition, std::vector<char> &symbols);
	bool GetNullable(CRegularExpression* exp);
	bool SetNullable(CRegularExpression* exp);
	static void UMerge(std::vector<int>& a, const std::vector<int>& b);
	static std::string DecipherString(const std::string& s);
	bool ReadVariable(const std::string& vName, std::string& vValue);
	static void PrintBanner(std::ostream& s, std::string& fname);
public:
	CLexerGenerator();
	virtual ~CLexerGenerator() {}
	void setErrorHandler(CErrorHandler* errorHandler);
	int registerResponse(const std::string& response);
	void addEOFEvent(const std::string& state, int response);
	void addEvent(const std::string& state, regularExpressionPtr& ptr);
	void setVar(const std::string& variableName, const std::string& value);
	void Process();
	void Export();
};