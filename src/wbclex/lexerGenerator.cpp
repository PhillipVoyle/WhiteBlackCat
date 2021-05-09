#include "lexerGenerator.h"
#include "errorHandler.h"
#include <sstream>
#include <algorithm>
#include "utils.h"
#include <fstream>
#include <iomanip>
#include <math.h>

const CLexerGenerator::PositionSet CLexerGenerator::kEmptyPositionSet;

CLexerGenerator::CLexerGenerator()
{
	m_errorHandler = nullptr;
}

void CLexerGenerator::setErrorHandler(CErrorHandler *errorHandler)
{
	m_errorHandler = errorHandler;
}

void CLexerGenerator::addEOFEvent(const std::string &state, int response)
{
	if (m_eofEvents.find(state) != m_eofEvents.end())
	{
		std::stringstream str;
		str << "EOF response for state " << state << "already exists";
		m_errorHandler->EmitError(str.str());
	}
	m_eofEvents[state] = response;
}

void CLexerGenerator::addEvent(const std::string &state, regularExpressionPtr &ptr)
{
	if (m_regularExpressions[state] == nullptr)
	{
		m_regularExpressions[state] = ptr;
	}
	else
	{
		m_regularExpressions[state] = CRegularExpression::CreateOrNode(m_regularExpressions[state], ptr);
	}
}

void CLexerGenerator::setVar(const std::string &variableName, const std::string &value)
{
	if (m_vars.find(variableName) != m_vars.end())
	{
		std::stringstream str;
		str << "variable " << variableName << " already has a value";
		m_errorHandler->EmitError(str.str());
	}
	m_vars[variableName] = value;
}

int CLexerGenerator::registerResponse(const std::string &response)
{
	int id = (int)m_responses.size();
	m_responses.push_back(response);
	return id;
}

int CLexerGenerator::AssignPositionIDs(std::shared_ptr<CRegularExpression> exp, int id)
{
	if (exp != nullptr)
	{
		exp->SetID(-1);
		switch (exp->GetTypeID())
		{
		case CRegularExpression::starNode:
		case CRegularExpression::orNode:
		case CRegularExpression::catNode:
		{
			int idA = AssignPositionIDs(exp->GetA(), id);
			return AssignPositionIDs(exp->GetB(), idA);
		}
		break;
		case CRegularExpression::charNode:
		case CRegularExpression::endNode:
			exp->SetID(id);
			return id + 1;
		default:
			break;
		}
	}
	return id;
}

bool CLexerGenerator::Getnullptrable(std::shared_ptr<CRegularExpression> exp)
{
	if (exp == nullptr)
	{
		return true;
	}
	return exp->Getnullptrable();
}

bool CLexerGenerator::Setnullptrable(std::shared_ptr<CRegularExpression> exp)
{
	if (exp == nullptr)
	{
		return true;
	}

	bool bnullptrable = true;
	switch (exp->GetTypeID())
	{
	case CRegularExpression::starNode:
		Setnullptrable(exp->GetA());
		bnullptrable = true;
		break;
	case CRegularExpression::orNode:
	{
		bool bA = Setnullptrable(exp->GetA());
		bool bB = Setnullptrable(exp->GetB());
		bnullptrable = bA || bB;
	}
	break;
	case CRegularExpression::catNode:
	{
		bool bA = Setnullptrable(exp->GetA());
		bool bB = Setnullptrable(exp->GetB());
		bnullptrable = bA && bB;
	}
	break;
	case CRegularExpression::charNode:
	case CRegularExpression::endNode:
		bnullptrable = false;
		break;
	default:
		break;
	}
	exp->Setnullptrable(bnullptrable);
	return bnullptrable;
}

void CLexerGenerator::ComputeFollowPos(std::shared_ptr<CRegularExpression> exp, std::vector<PositionSet> &followPos)
{
	if (exp == nullptr)
	{
		return;
	}

	switch (exp->GetTypeID())
	{
	case CRegularExpression::starNode:
	{
		ComputeFollowPos(exp->GetA(), followPos);
		const PositionSet *fpA = &kEmptyPositionSet;
		const PositionSet *lpA = &kEmptyPositionSet;
		if (exp->GetA())
		{
			fpA = &exp->GetA()->GetFirstPos();
			lpA = &exp->GetA()->GetLastPos();
		}
		exp->SetFirstPos(*fpA);
		exp->SetLastPos(*lpA);

		int i;
		for (i = 0; i < (int)(lpA->size()); i++)
		{
			int pos = (*lpA)[i];
			PositionSet &fPos = followPos[pos];
			UMerge(fPos, *fpA);
		}
	}
	break;
	case CRegularExpression::orNode:
	{
		ComputeFollowPos(exp->GetA(), followPos);
		ComputeFollowPos(exp->GetB(), followPos);
		const PositionSet *fpA = &kEmptyPositionSet;
		const PositionSet *fpB = &kEmptyPositionSet;
		const PositionSet *lpA = &kEmptyPositionSet;
		const PositionSet *lpB = &kEmptyPositionSet;
		if (exp->GetA())
		{
			fpA = &exp->GetA()->GetFirstPos();
			lpA = &exp->GetA()->GetLastPos();
		}
		if (exp->GetB())
		{
			fpB = &exp->GetB()->GetFirstPos();
			lpB = &exp->GetB()->GetLastPos();
		}
		PositionSet uf;
		std::set_union(fpA->begin(), fpA->end(), fpB->begin(), fpB->end(), std::back_insert_iterator<PositionSet>(uf));
		PositionSet ul;
		std::set_union(lpA->begin(), lpA->end(), lpB->begin(), lpB->end(), std::back_insert_iterator<PositionSet>(ul));
		exp->SetFirstPos(uf);
		exp->SetLastPos(ul);
	}
	break;
	case CRegularExpression::catNode:
	{
		ComputeFollowPos(exp->GetA(), followPos);
		ComputeFollowPos(exp->GetB(), followPos);
		const PositionSet *fpA = &kEmptyPositionSet;
		const PositionSet *fpB = &kEmptyPositionSet;
		const PositionSet *lpA = &kEmptyPositionSet;
		const PositionSet *lpB = &kEmptyPositionSet;
		if (exp->GetA())
		{
			fpA = &exp->GetA()->GetFirstPos();
			lpA = &exp->GetA()->GetLastPos();
		}
		if (exp->GetB())
		{
			fpB = &exp->GetB()->GetFirstPos();
			lpB = &exp->GetB()->GetLastPos();
		}

		const PositionSet *uf = nullptr;
		PositionSet ufHandle;
		if (Getnullptrable(exp->GetA()))
		{
			std::set_union(fpA->begin(), fpA->end(), fpB->begin(), fpB->end(), std::back_insert_iterator<PositionSet>(ufHandle));
			uf = &ufHandle;
		}
		else
		{
			uf = fpA;
		}
		exp->SetFirstPos(*uf);

		const PositionSet *ul = nullptr;
		PositionSet ulHandle;
		if (Getnullptrable(exp->GetB()))
		{
			std::set_union(lpA->begin(), lpA->end(), lpB->begin(), lpB->end(), std::back_insert_iterator<PositionSet>(ulHandle));
			ul = &ulHandle;
		}
		else
		{
			ul = lpB;
		}
		exp->SetLastPos(*ul);

		int i;
		for (i = 0; i < (int)lpA->size(); i++)
		{
			PositionSet &fPos = followPos[(*lpA)[i]];
			UMerge(fPos, *fpB);
		}
	}
	break;
	case CRegularExpression::charNode:
	case CRegularExpression::endNode:
	{
		PositionSet ps;
		ps.push_back(exp->GetID());
		exp->SetFirstPos(ps);
		exp->SetLastPos(ps);
	}
	break;
	default:
		break;
	}
}

void CLexerGenerator::GetDataAtPositions(std::shared_ptr<CRegularExpression> exp, std::vector<nodeData> &dataAtPosition, std::vector<char> &symbols)
{
	if (exp == nullptr)
		return;

	switch (exp->GetTypeID())
	{
	case CRegularExpression::starNode:
		GetDataAtPositions(exp->GetA(), dataAtPosition, symbols);
		break;
	case CRegularExpression::orNode:
		GetDataAtPositions(exp->GetA(), dataAtPosition, symbols);
		GetDataAtPositions(exp->GetB(), dataAtPosition, symbols);
		break;
	case CRegularExpression::catNode:
		GetDataAtPositions(exp->GetA(), dataAtPosition, symbols);
		GetDataAtPositions(exp->GetB(), dataAtPosition, symbols);
		break;
	case CRegularExpression::charNode:
	{
		int nID = exp->GetID();
		int size = (int)dataAtPosition.size();
		assert(nID == size);
		char c = exp->GetC();
		dataAtPosition.push_back(nodeData(false, (int)c));
		if (std::find(symbols.begin(), symbols.end(), c) == symbols.end())
		{
			symbols.push_back(c);
		}
	}
	break;
	case CRegularExpression::endNode:
	{
		int nID = exp->GetID();
		int size = (int)dataAtPosition.size();
		assert(nID == size);
		dataAtPosition.push_back(nodeData(true, (int)exp->GetEnd()));
	}
	break;
	default:
		break;
	}
}

void CLexerGenerator::ComputeStates(std::vector<PositionSet> followPos, std::shared_ptr<CRegularExpression> exp, std::vector<StateData> &stateData)
{
	//populate these
	std::vector<nodeData> dataAtPosition;
	std::vector<char> symbols;

	//using this function
	GetDataAtPositions(exp, dataAtPosition, symbols);

	//populate symbol IDs
	int nSymbols = (int)symbols.size();
	std::vector<int> symbolIDs(128, -1);
	int sind;
	for (sind = 0; sind < nSymbols; sind++)
	{
		symbolIDs[symbols[sind]] = sind;
	}

	int nStates = 0;
	int nMarkedStates = 0;
	std::vector<dState> DStates;
	std::map<std::vector<int>, int> DStateIDs;
	DStateIDs[exp->GetFirstPos()] = nStates;
	DStates.push_back(kEmptyState);
	dState &state = DStates.back();
	state.state = exp->GetFirstPos();
	nStates++;

	while (nMarkedStates < nStates)
	{
		int id = nMarkedStates;
		StateData d;
		d.m_announce = -1;
		for (int i = 0; i < 128; i++)
		{
			d.m_transitions[i] = -1;
		}

		for (int a = 0; a < nSymbols; a++)
		{
			std::vector<int> U;

			int istate;
			for (istate = 0; istate < (int)DStates[id].state.size(); istate++)
			{
				int p = DStates[id].state[istate];
				if (!dataAtPosition[p].m_bEnd)
				{
					if (dataAtPosition[p].m_dataID == symbols[a])
					{
						UMerge(U, followPos[p]);
					}
				}
			}

			if (U.size() == 0)
			{
				continue;
			}
			auto itState = DStateIDs.find(U);
			int stateID;
			if (itState == DStateIDs.end())
			{
				stateID = nStates;
				DStateIDs[U] = nStates;
				DStates.push_back(kEmptyState);
				dState &state = DStates.back();
				state.state = U;
				nStates++;
			}
			else
			{
				stateID = itState->second;
			}
			//this must be DStatesID instead of theState, as the vector may have changed
			d.m_transitions[symbols[a]] = stateID;
		}

		dState &theState = DStates[id];
		int ann;
		for (ann = 0; ann < (int)theState.state.size(); ann++)
		{
			int pos = theState.state[ann];
			nodeData &nd = dataAtPosition[pos];
			if (nd.m_bEnd)
			{
				d.m_announce = nd.m_dataID;
				break;
			}
		}
		nMarkedStates++;
		stateData.push_back(d);
		assert(nMarkedStates == stateData.size());
	}
}

void CLexerGenerator::UMerge(std::vector<int> &a, const std::vector<int> &b)
{
	auto itA = a.begin();
	auto itB = b.begin();
	for (;;)
	{
		if (itB == b.end())
		{
			break;
		}

		if (itA == a.end())
		{
			for (;;)
			{
				a.push_back(*itB);
				itB++;
				if (itB == b.end())
				{
					return;
				}
			}
		}

		if (*itB < *itA)
		{
			itA = a.insert(itA, *itB);
			itA++;
			itB++;
		}
		else if (*itB > *itA)
		{
			itA++;
		}
		else
		{
			assert(*itA == *itB);
			itA++;
			itB++;
		}
	}
}

void CLexerGenerator::Process()
{
	//TODO: make work if states contain 0 expressions, and
	//only an EOF.

	for (auto it = m_regularExpressions.begin(); it != m_regularExpressions.end(); it++)
	{
		std::string sname = it->first;
		std::shared_ptr<CRegularExpression> exp = it->second;
		int nIDs = AssignPositionIDs(exp, 0);
		Setnullptrable(exp);
		std::vector<PositionSet> followPos(nIDs, PositionSet());
		ComputeFollowPos(exp, followPos);
		ComputeStates(followPos, exp, m_stateData[it->first]);
	}
}

std::string CLexerGenerator::DecipherString(const std::string &s)
{
	std::string result;
	int index = 0;
	assert(s[index] == '"');
	int length = (int)s.length();
	for (index = 1; index < length; index++)
	{
		char c = s[index];
		if (c == '\"')
		{
			break;
		}
		assert(index < length - 1);
		if (c == '\\')
		{
			index++;
			c = Utils::EscapeChar(s[index]);
		}
		result.append(&c, 1);
	}
	return result;
}

bool CLexerGenerator::ReadVariable(const std::string &vName, std::string &vValue)
{
	auto it = m_vars.find(vName);
	if (it == m_vars.end())
	{
		return false;
	}
	vValue = DecipherString(it->second);
	return true;
}

void CLexerGenerator::PrintBanner(std::ostream &s, std::string &fname)
{
	s << "/*" << std::endl;
	s << "    " << fname << "\n    Generated by wbclex Scanner Generator (C) Phillip Voyle 2011 - 2021" << std::endl;
	s << "*/" << std::endl;
	s << std::endl;
}

void CLexerGenerator::Export()
{
	std::string sLexerName = "CLexigen";
	std::string sTableName = "CLexigenTable";
	std::string sHeaderOut = "lexigen.h";
	std::string sTableSource = "lexigen_table.cpp";
	std::string sTableHeader = "lexigen_table.h";

	ReadVariable("$LEXERNAME", sLexerName);
	ReadVariable("$TABLENAME", sTableName);
	ReadVariable("$HEADER", sHeaderOut);
	ReadVariable("$TABLEHEADER", sTableHeader);
	ReadVariable("$TABLESOURCE", sTableSource);

	std::ofstream fHeader(sHeaderOut.c_str());
	std::ofstream fTableSource(sTableSource.c_str());
	std::ofstream fTableHeader(sTableHeader.c_str());

	PrintBanner(fHeader, sHeaderOut);
	PrintBanner(fTableSource, sTableSource);
	PrintBanner(fTableHeader, sTableHeader);

	fTableSource << "#include \"" << sTableHeader << "\"\n\n";

	fTableHeader << "#pragma once" << std::endl;
	fTableHeader << std::endl;
	//
	fTableHeader << "class " << sTableName << "\n{\npublic:\n";
	fTableHeader << "   enum stateIDs\n";
	fTableHeader << "   {\n";
	int nNumStates = 0;
	auto itDVM = m_stateData.begin();
	for (; itDVM != m_stateData.end(); itDVM++)
	{
		auto &dv = itDVM->second;
		nNumStates += (int)dv.size();
		fTableHeader << "      " << DecipherString(itDVM->first) << ",\n";
	}
	fTableHeader << "      stNumStates\n";
	fTableHeader << "   };\n";
	fTableHeader << "\nprivate:\n";
	fTableHeader << "   static const int kStates = " << (int)m_stateData.size() << ";\n";
	fTableHeader << "   static const int kInnerStates = " << nNumStates << ";\n\n";
	fTableHeader << "   static const int s_dataOffsets[kStates];\n";
	fTableHeader << "   static const int s_announceOnEOF[kStates];\n";
	fTableHeader << "   static const int s_announceData[kInnerStates];\n";
	fTableHeader << "   static const int s_transitionData[kInnerStates][128];\n";
	fTableHeader << "\npublic:\n";
	fTableHeader << "   static int GetAnnounce(int state, int nInnerState);\n";
	fTableHeader << "   static int GetAnnounceOnEOF(int state);\n";
	fTableHeader << "   static int GetTransition(int state, int nInnerState, char c);\n";
	fTableHeader << "};\n"
				 << std::endl;

	fHeader << "#pragma once" << std::endl;
	fHeader << "#include <list>\n#include <iostream>\n#include <assert.h>\n#include <utility>\n"
			<< std::endl;
	fHeader << "#include \"" << sTableHeader << "\"\n\n";
	fHeader << "template <class T, class Table = " << sTableName << ">" << std::endl;
	fHeader << "class " << sLexerName << std::endl;
	fHeader << "   :public T\n";
	fHeader << "   ,public Table\n";
	fHeader << "{\n";
	fHeader << "   typedef typename Table::stateIDs stateIDs;\n";
	fHeader << "   stateIDs m_currentState;\n";
	fHeader << "   typedef typename T::lexiType lexiType;\n";
	fHeader << "   std::list<char> m_ungetBuffer;\npublic:\n";
	fHeader << "   template<typename...TArgs>\n";
	fHeader << "   " << sLexerName << "(TArgs...args):T(args...)\n";
	fHeader << "   {\n";
	fHeader << "       init();\n";
	fHeader << "   }\n";
	fHeader << "   void init()\n";
	fHeader << "   {\n";
	fHeader << "       m_currentState = Table::stStart;\n";
	fHeader << "       flush();\n";
	fHeader << "   }\n\n";
	fHeader << "   void flush()\n";
	fHeader << "   {\n";
	fHeader << "      m_ungetBuffer.clear();\n";
	fHeader << "   }\n\n";
	fHeader << "   void setState(stateIDs state)\n";
	fHeader << "   {\n";
	fHeader << "      m_currentState = state;\n";
	fHeader << "   }\n";
	fHeader << "   lexiType scan(std::istream& _inStream)\n";
	fHeader << "   {\n";
	fHeader << "      std::string lexeme;\n";
	fHeader << "      std::string sbuffer;\n";
	fHeader << "      int stateid = 0;\n";
	fHeader << "      int announce = -1;\n";
	fHeader << "      \n";
	fHeader << "      for(;;)\n";
	fHeader << "      {\n";
	fHeader << "         int newAnnounce = this->GetAnnounce(m_currentState, stateid);\n";
	fHeader << "         if(newAnnounce != -1)\n";
	fHeader << "         {\n";
	fHeader << "            lexeme = sbuffer;\n";
	fHeader << "            announce = newAnnounce;\n";
	fHeader << "         }\n";
	fHeader << "         \n";
	fHeader << "         char c;\n";
	fHeader << "         if(m_ungetBuffer.size() > 0)\n";
	fHeader << "         {\n";
	fHeader << "            c = m_ungetBuffer.front();\n";
	fHeader << "            m_ungetBuffer.pop_front();\n";
	fHeader << "         }\n";
	fHeader << "         else\n";
	fHeader << "         {\n";
	fHeader << "            for(;;)\n";
	fHeader << "            {\n";
	fHeader << "               _inStream.get(c);\n";
	fHeader << "               if(_inStream.eof())\n";
	fHeader << "               {\n";
	fHeader << "                  c = EOF;\n";
	fHeader << "               }\n";
	fHeader << "               else if(c < 0)\n";
	fHeader << "               {\n";
	fHeader << "                  _inStream.get(c);\n";
	fHeader << "                  continue;\n";
	fHeader << "               }\n";
	fHeader << "               break;\n";
	fHeader << "            }\n";
	fHeader << "         }\n";
	fHeader << "         \n";
	fHeader << "         if(c == EOF)\n";
	fHeader << "         {\n";
	fHeader << "            stateid = -1;\n";
	fHeader << "         }\n";
	fHeader << "         else\n";
	fHeader << "         {\n";
	fHeader << "            assert(c >= 0);\n";
	fHeader << "            assert(c < 128);\n";
	fHeader << "            stateid = this->GetTransition(m_currentState, stateid, c);\n";
	fHeader << "         }\n";
	fHeader << "         sbuffer.append(1, c);\n";
	fHeader << "         \n";
	fHeader << "         if(stateid == -1)\n";
	fHeader << "         {\n";
	fHeader << "            bool bQuit = false;\n";
	fHeader << "            if((sbuffer.size() == 1) && c == EOF)\n";
	fHeader << "            {\n";
	fHeader << "               bQuit = true;\n";
	fHeader << "               announce = this->GetAnnounceOnEOF(m_currentState);\n";
	fHeader << "            }\n";
	fHeader << "            \n";
	fHeader << "            int id;\n";
	fHeader << "            for(id = (int)sbuffer.size() - 1; id >= (int)lexeme.size(); id--)\n";
	fHeader << "            {\n";
	fHeader << "               m_ungetBuffer.push_front(sbuffer[id]);\n";
	fHeader << "            }\n";
	fHeader << "            sbuffer = \"\";\n";
	fHeader << "            stateid = 0;\n";
	fHeader << "            switch(announce)\n";
	fHeader << "            {\n";

	int iResponse;
	for (iResponse = 0; iResponse < (int)m_responses.size(); iResponse++)
	{
		fHeader << "            case " << iResponse << ":\n";
		fHeader << m_responses[iResponse] << "\n";
		fHeader << "               break;\n";
	}

	fHeader << "            default:\n";
	fHeader << "               return EOF;\n";
	fHeader << "            }\n";
	fHeader << "            announce = -1;\n";
	fHeader << "            lexeme = \"\";\n";
	fHeader << "            if(bQuit)\n";
	fHeader << "            {\n";
	fHeader << "               return EOF;\n";
	fHeader << "            }\n";
	fHeader << "         }\n";
	fHeader << "      }\n";
	fHeader << "   }\n";
	fHeader << "};\n";

	int wid = std::max<int>((int)ceilf(log10f((float)nNumStates)), 2);
	int nOffset = 0;
	fTableSource << "const int " << sTableName << "::s_dataOffsets[" << sTableName << "::kStates] =\n{";

	int index = 0;
	if (m_stateData.size() > 0)
	{
		itDVM = m_stateData.begin();
		for (;;)
		{
			if (index % NCOLS == 0)
			{
				fTableSource << "\n   ";
			}
			STATEDATAVECTOR &dv = itDVM->second;
			fTableSource << std::setiosflags(std::ios_base::right) << std::setw(wid) << nOffset;
			nOffset += (int)dv.size();
			itDVM++;
			if (itDVM == m_stateData.end())
			{
				fTableSource << "\n";
				break;
			}
			else
			{
				fTableSource << ", ";
			}
			index++;
		}
	}
	fTableSource << "};\n\n";

	fTableSource << "const int " << sTableName << "::s_announceOnEOF[" << sTableName << "::kStates] =\n{";
	int size = (int)m_stateData.size();
	index = 0;
	for (itDVM = m_stateData.begin(); itDVM != m_stateData.end(); itDVM++)
	{
		if (index % NCOLS == 0)
		{
			fTableSource << "\n   ";
		}
		STATEDATAVECTOR &dv = itDVM->second;
		auto itEOF = m_eofEvents.find(itDVM->first);
		if (itEOF != m_eofEvents.end())
		{
			fTableSource << std::setiosflags(std::ios_base::right) << std::setw(wid) << itEOF->second;
		}
		else
		{
			fTableSource << std::setiosflags(std::ios_base::right) << std::setw(wid) << -1;
		}
		index++;
		if (index != size)
		{
			fTableSource << ", ";
		}
		else
		{
			fTableSource << "\n";
		}
	}
	fTableSource << "};\n\n";

	fTableSource << "const int " << sTableName << "::s_announceData[" << sTableName << "::kInnerStates] =\n{";
	index = 0;
	for (itDVM = m_stateData.begin(); itDVM != m_stateData.end(); itDVM++)
	{
		STATEDATAVECTOR &dv = itDVM->second;

		auto itDV = dv.begin();
		for (; itDV != dv.end(); itDV++)
		{
			if (index % NCOLS == 0)
			{
				fTableSource << "\n   ";
			}

			fTableSource << std::setiosflags(std::ios_base::right) << std::setw(wid) << itDV->m_announce;

			index++;
			if (index != nNumStates)
			{
				fTableSource << ", ";
			}
			else
			{
				fTableSource << "\n";
			}
		}
	}
	fTableSource << "};\n\n";

	fTableSource << "const int " << sTableName << "::s_transitionData[" << sTableName << "::kInnerStates][128] =\n{\n";
	index = 0;
	for (itDVM = m_stateData.begin(); itDVM != m_stateData.end(); itDVM++)
	{
		STATEDATAVECTOR &dv = itDVM->second;

		STATEDATAVECTOR::iterator itDV;
		for (itDV = dv.begin(); itDV != dv.end(); itDV++)
		{
			fTableSource << "   {";
			int *transitions = itDV->m_transitions;
			int transition = 0;
			for (;;)
			{
				if (transition % NCOLS == 0)
				{
					fTableSource << "\n      ";
				}
				fTableSource << std::setiosflags(std::ios_base::right) << std::setw(wid) << transitions[transition];
				transition++;
				if (transition < 128)
				{
					fTableSource << ", ";
				}
				else
				{
					fTableSource << "\n";
					break;
				}
			}
			index++;
			if (index < nNumStates)
			{
				fTableSource << "   },\n";
			}
			else
			{
				fTableSource << "   }\n";
			}
		}
	}
	fTableSource << "};\n\n";

	fTableSource << "int " << sTableName << "::GetAnnounce(int state, int nInnerState)\n";
	fTableSource << "{\n";
	fTableSource << "   return s_announceData[s_dataOffsets[state] + nInnerState];\n";
	fTableSource << "}\n\n";
	fTableSource << "int " << sTableName << "::GetAnnounceOnEOF(int state)\n";
	fTableSource << "{\n";
	fTableSource << "   return s_announceOnEOF[state];\n";
	fTableSource << "}\n\n";
	fTableSource << "int " << sTableName << "::GetTransition(int state, int nInnerState, char c)\n";
	fTableSource << "{\n";
	fTableSource << "   return s_transitionData[s_dataOffsets[state]+ nInnerState][c];\n";
	fTableSource << "}\n";
}
