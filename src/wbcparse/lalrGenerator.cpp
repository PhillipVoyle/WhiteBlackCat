#include "lalrGenerator.h"
#include <algorithm>
#include <list>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <sstream>
#include "errorHandler.h"

const CLALRGenerator::NonterminalID ntStartSymbol = 0xFFFFFFFF;
const CLALRGenerator::TerminalID LookAheadID = 0xFFFFFFFF;
const CLALRGenerator::LR0StateID BADStateID = 0xFFFFFFFF;

CLALRGenerator::CLALRGenerator()
{
	m_bError = false;
	setType("$", "void", "void");
	setType("S'","void", "void");
	m_errorHandler = nullptr;
}

CLALRGenerator::~CLALRGenerator()
{
}

void CLALRGenerator::assignVariable(const std::string& varname, const std::string& value)
{
	if(m_variables.find(varname) != m_variables.end())
	{
		std::stringstream str;
		str << "variable " << varname << "already has a value";
		m_errorHandler->EmitError(str.str());
	}
	m_variables[varname] = value;
}


char CLALRGenerator::EscapeChar(char c)
{
	switch(c)
	{
	case 'a':
		return '\a';
	case 'b':
		return '\b';
	case 't':
		return '\t';
	case 'r':
		return '\r';
	case 'v':
		return '\v';
	case 'f':
		return '\f';
	case 'n':
		return '\n';
	default:
		return c;
	}
}
std::string CLALRGenerator::DecipherString(const std::string& s)
{
	std::string result;
	int index = 0;
	assert(s[index] == '"');
	int length = (int)s.length();
	for(index = 1; index < length; index++)
	{
		char c = s[index];
		if(c == '\"')
		{
			break;
		}
		assert(index < length - 1);
		if(c == '\\')
		{
			index++;
			c = EscapeChar(s[index]);
		}
		result.append(&c, 1);
	}
	return result;
}

bool CLALRGenerator::ReadVariable(const std::string& vName, std::string& vValue)
{
	std::map<std::string, std::string>::iterator it = m_variables.find(vName);
	if(it == m_variables.end())
	{
		return false;
	}
	vValue = DecipherString(it->second);
	return true;
}


void CLALRGenerator::GenerateParser(std::shared_ptr<IProductions> &parseTree)
{
	if(parseTree != nullptr && !m_bError)
	{
		std::string firstNonTerminal = parseTree->GetProduction()->GetLeft()->GetName();
		std::shared_ptr<ITokenList> rule = parseTree->GetProduction()->GetRight();

		//augment grammar with S' -> S
    std::shared_ptr<ITokenList> _empty;
    std::shared_ptr<IToken> _tokenTerm = IToken::Create(firstNonTerminal);
		std::shared_ptr<ITokenList> startSymbol = ITokenList::Create(_tokenTerm, _empty);
		std::shared_ptr<IProduction> startProduction = IProduction::Create(IToken::Create("S'"), startSymbol, "#");
		std::shared_ptr<IProductions> augmentedGrammar = IProductions::Create(startProduction, parseTree);

		m_grammar = augmentedGrammar;
		ProcessSymbols();
		GenerateLR0Items();
		//DumpLR0States();
		ConvertLR0ItemsToKernels();
		//DumpLR0Kernels();
		//DumpLR0Gotos();
		ComputeFirstSets();
		//DumpFirstSets();
		InitLALRTables();
		//DumpLALRLookAheads();
		ComputeLALRLookAheads();
		//DumpLALRPropogationTable();
		//DumpLALRLookAheads();
		GenerateActions();
		CheckActions();
		if(!m_bError)
		{
			DumpParseTables();
		}
		m_grammar = nullptr;
	}
}

void CLALRGenerator::ProcessSymbols()
{
	//first production is the augmented one anyhow
	std::shared_ptr<IProductions> list = m_grammar->GetProductions();
	while(list != nullptr)
	{
		std::shared_ptr<IProduction> production = list->GetProduction();
		const std::string& nonterminal = production->GetLeft()->GetName();
		std::map<std::string, NonterminalID>::iterator itNT = m_NonterminalIDs.find(nonterminal);
		if(itNT == m_NonterminalIDs.end())
		{
			NonterminalID id = (NonterminalID) m_Nonterminals.size();
			m_NonterminalIDs[nonterminal] = id;
			m_Nonterminals.push_back(nonterminal);
			production->GetLeft()->SetID(id);
		}
		else
		{
			production->GetLeft()->SetID(itNT->second);
		}
		list = list->GetProductions();
	}
	m_grammar->GetProduction()->GetLeft()->SetID(ntStartSymbol);

	list = m_grammar;
	int nProductions = 0;
	while(list != nullptr)
	{
		std::shared_ptr<IProduction> production = list->GetProduction();

		m_productions.push_back(production);
		std::shared_ptr<ITokenList> tokenList = production->GetRight();
		production->SetID(nProductions);
		nProductions++;
		while(tokenList != nullptr)
		{
			const std::string& token = tokenList->GetToken()->GetName();

			std::map<std::string, NonterminalID>::iterator itNT = m_NonterminalIDs.find(token);
			if(itNT == m_NonterminalIDs.end())
			{
				std::map<std::string, TerminalID>::iterator itT = m_TerminalIDs.find(token);
				if(itT == m_TerminalIDs.end())
				{
					TerminalID id = (TerminalID) m_TerminalIDs.size();
					m_Terminals.push_back(token);
					m_TerminalIDs[token] = id;
					tokenList->GetToken()->SetID(id);
				}
				else
				{
					tokenList->GetToken()->SetID(itT->second);
				}
				tokenList->SetIsTerminal(true);
			}
			else
			{
				tokenList->GetToken()->SetID(itNT->second);
				tokenList->SetIsTerminal(false);
			}

			tokenList = tokenList->GetTokenList();
		}
		list = list->GetProductions();
	}

	//add end terminal to the terminals
	m_endID = (TerminalID)m_Terminals.size();
	m_Terminals.push_back("$");
	m_TerminalIDs["$"] = m_endID;
}

CLALRGenerator::LR1State CLALRGenerator::LR1Closure(const LR1State& I)
{
	LR1State J = I;
	typedef std::pair<LR0ItemID, TerminalID> unmarked_pair;
	std::list<unmarked_pair> unmarked;

	LR1State::const_iterator itI;
	for(itI = I.begin(); itI != I.end(); itI++)
	{
		LR0ItemID itemID = itI->first;
		const std::set<TerminalID>& terminals = itI->second;
		std::set<TerminalID>::const_iterator itTerm;
		for(itTerm = terminals.begin(); itTerm != terminals.end(); itTerm++)
		{
			unmarked.push_back(unmarked_pair(itemID, *itTerm));
		}
	}
	while(unmarked.size() > 0)
	{
		unmarked_pair LR1item = unmarked.front();
		unmarked.pop_front();
		LR0ItemID LR0itemID = LR1item.first;
		const LR0Item& LR0item = m_LR0Items[LR0itemID];
		if(LR0item.second == nullptr)
		{
			continue;
		}
		if(!LR0item.second->GetIsTerminal())
		{
			NonterminalID nonterminalId = LR0item.second->GetToken()->GetID();
			std::set<TerminalID> first = First(LR0item.second->GetTokenList(), LR1item.second);
			std::shared_ptr<IProductions> list = m_grammar;
			while(list != nullptr)
			{
				std::shared_ptr<IProduction> production = list->GetProduction();
				if(production->GetLeft()->GetID() == nonterminalId)
				{
					LR0Item newLR0Item(production, production->GetRight());
					LR0ItemID newLR0ItemID = GetLR0ItemID(newLR0Item);
					std::set<TerminalID>::iterator itSet;
					for(itSet = first.begin(); itSet != first.end(); itSet++)
					{
						std::map<LR0ItemID, std::set<TerminalID> >::iterator itMap = J.find(newLR0ItemID);
						unmarked_pair newLR1Item(newLR0ItemID, *itSet);
						if(itMap == J.end() || itMap->second.find(*itSet) == itMap->second.end())
						{
							J[newLR0ItemID].insert(*itSet);
							unmarked.push_back(newLR1Item);
						}
					}
				}
				list = list->GetProductions();
			}
		}
	}

	return J;
}

CLALRGenerator::LR0State CLALRGenerator::LR0Closure(const LR0State &I)
{
	LR0State J = I;
/*
	// recreated original code - works the same as the implementation, below
	bool bDidSomething;
	do
	{
		bDidSomething = false;
		LR0State::iterator it;
		for(it = J.begin(); it != J.end(); it++)
		{
			LR0ItemID itemID = *it;
			LR0Item item = m_LR0Items[itemID];
			if(item.second != nullptr)
			{
				const std::string& token = item.second->GetToken()->GetName();
				std::shared_ptr<IProductions> list = m_grammar->GetProductions();
				while(list != nullptr)
				{
					std::shared_ptr<IProduction> production = list->GetProduction();
					if(production != nullptr && production->GetLeft()->GetName() == token)
					{
						LR0Item nextItem;
						nextItem.first = production;
						nextItem.second = production->GetRight();
						LR0ItemID nextItemID = GetLR0ItemID(nextItem);
						if(J.find(nextItemID) == J.end())
						{
							bDidSomething = true;
							J.insert(nextItemID);
						}
					}
					list = list->GetProductions();
				}
			}
		}
	}while(bDidSomething);
*/
	std::list<LR0ItemID> unmarked;
	std::copy(I.begin(), I.end(), std::back_insert_iterator<std::list<LR0ItemID> >(unmarked));

	while(unmarked.size() > 0)
	{
		LR0ItemID itemID = unmarked.front();
		unmarked.pop_front();
		LR0Item item = m_LR0Items[itemID];
		if(item.second != nullptr)
		{
			const std::string& token = item.second->GetToken()->GetName();
			std::shared_ptr<IProductions> list = m_grammar->GetProductions();
			while(list != nullptr)
			{
				std::shared_ptr<IProduction> production = list->GetProduction();
				if(production != nullptr && production->GetLeft()->GetName() == token)
				{
					LR0Item nextItem;
					nextItem.first = production;
					nextItem.second = production->GetRight();
					LR0ItemID nextItemID = GetLR0ItemID(nextItem);
					if(J.find(nextItemID) == J.end())
					{
						unmarked.push_back(nextItemID);
						J.insert(nextItemID);
					}
				}
				list = list->GetProductions();
			}
		}
	}
	return J;
}

CLALRGenerator::LR0ItemID CLALRGenerator::GetLR0ItemID(const CLALRGenerator::LR0Item &item)
{
	std::map<LR0Item, LR0ItemID>::iterator it = m_LR0ItemIDs.find(item);
	if(it == m_LR0ItemIDs.end())
	{
		LR0ItemID id = (LR0ItemID)m_LR0Items.size();
		m_LR0Items.push_back(item);
		m_LR0ItemIDs[item] = id;
		return id;
	}
	else
	{
		return it->second;
	}
}

CLALRGenerator::LR0StateID CLALRGenerator::GetLR0StateID(const LR0State& state)
{
	if(state.size() == 0)
	{
		return BADStateID;
	}
	std::map<LR0State, LR0StateID>::iterator it = m_LR0StateIDs.find(state);
	if(it == m_LR0StateIDs.end())
	{
		LR0StateID id = (LR0StateID) m_LR0States.size();
		LR0StateData kEmptyData;
		m_LR0States.push_back(kEmptyData);
		LR0StateData& stateData = m_LR0States.back();
		stateData.state = state;
		m_LR0StateIDs[state] = id;
		return id;
	}
	else
	{
		return it->second;
	}
}

CLALRGenerator::LR0StateID CLALRGenerator::GetLR0Goto(LR0StateID id, const std::string& token)
{
	LR0State newState;
	std::set<LR0ItemID>::iterator it;
	for(it = m_LR0States[id].state.begin(); it != m_LR0States[id].state.end(); it++)
	{
		const LR0Item& item = m_LR0Items[*it];
		if(item.second != nullptr)
		{
			if(token == item.second->GetToken()->GetName())
			{
				LR0Item newItem;
				newItem.first = item.first;
				newItem.second = item.second->GetTokenList();
				newState.insert(GetLR0ItemID(newItem));
			}
		}
	}

	LR0State closedState = LR0Closure(newState);
	return GetLR0StateID(closedState);
}


void CLALRGenerator::GenerateLR0Items()
{
	LR0Item firstItem;
	firstItem.first = m_grammar->GetProduction();
	firstItem.second = firstItem.first->GetRight();
	LR0State state0Kernel;
	state0Kernel.insert(GetLR0ItemID(firstItem));
	LR0State state0Closure = LR0Closure(state0Kernel);
	GetLR0StateID(state0Closure);
	int nMarkedStates = 0;
	while(nMarkedStates < (int)m_LR0States.size())
	{
		LR0StateID idI = (LR0StateID)nMarkedStates;
		nMarkedStates++;

		m_LR0States[idI].m_gotoOnNonterminal.resize(m_Nonterminals.size(), BADStateID);
		m_LR0States[idI].m_gotoOnTerminal.resize(m_Terminals.size(), BADStateID);

		const LR0State kEmptyState;
		std::vector<LR0State> gotoNT(m_Nonterminals.size(), kEmptyState);
		std::vector<LR0State> gotoT(m_Terminals.size(), kEmptyState);
		
		std::set<LR0ItemID>::iterator it;
		for(it = m_LR0States[idI].state.begin(); it != m_LR0States[idI].state.end(); it++)
		{
			const LR0Item item = m_LR0Items[*it];
			if(item.second != nullptr)
			{
				std::shared_ptr<ITokenList> tokens = item.second;
				LR0Item newItem;
				newItem.first = item.first;
				newItem.second = item.second->GetTokenList();
				LR0ItemID itemID = GetLR0ItemID(newItem); 
				if(tokens->GetIsTerminal())
				{
					TerminalID tID = tokens->GetToken()->GetID();
					gotoT[tID].insert(itemID);
				}
				else
				{
					NonterminalID ntID = item.second->GetToken()->GetID();
					gotoNT[ntID].insert(itemID);
				}
			}
		}
		
		for(int nonterminalID = 0; nonterminalID < (int)m_Nonterminals.size(); nonterminalID++)
		{
			LR0StateID stateOnGoto = GetLR0StateID(LR0Closure(gotoNT[nonterminalID]));
			m_LR0States[idI].m_gotoOnNonterminal[nonterminalID] = stateOnGoto;
		}
		for(int terminalid = 0; terminalid < (int)m_Terminals.size(); terminalid++)
		{
			LR0StateID stateOnGoto = GetLR0StateID(LR0Closure(gotoT[terminalid]));
			m_LR0States[idI].m_gotoOnTerminal[terminalid] = stateOnGoto;
		}
		/*
		//this stuff could be worded more efficiently (see above)
		//is now debug-only code that does a consistency check on the 
		for(int nonterminalID = 0; nonterminalID < (int)m_Nonterminals.size(); nonterminalID++)
		{
			const std::string& nonterminal = m_Nonterminals[nonterminalID];
			LR0StateID stateOnGotoDebug = GetLR0Goto(idI, nonterminal);
			LR0StateID stateOnGoto = m_LR0States[idI].m_gotoOnNonterminal[nonterminalID];
			assert(stateOnGotoDebug == stateOnGoto);
		}
		for(int terminalid = 0; terminalid < (int)m_Terminals.size(); terminalid++)
		{
			const std::string& terminal = m_Terminals[terminalid];
			LR0StateID stateOnGotoDebug = GetLR0Goto(idI, terminal);
			LR0StateID stateOnGoto = m_LR0States[idI].m_gotoOnTerminal[terminalid];
			assert(stateOnGotoDebug == stateOnGoto);
		}
		//*/
	}
}

void CLALRGenerator::PrintLR0Item(LR0ItemID itemID)
{
	const LR0Item& item = m_LR0Items[itemID];
	std::cout << item.first->GetLeft()->GetName();
	std::cout << " ->";
	std::shared_ptr<ITokenList> list = item.first->GetRight();
	for(;;)
	{
		if(list == item.second)
		{
			std::cout << " .";
		}
		if(list == nullptr)
		{
			break;
		}
		std::cout << " " << list->GetToken()->GetName();
		list = list->GetTokenList();
	}
}

void CLALRGenerator::DumpLR0States()
{
	std::cout << (unsigned)m_LR0States.size() << " states created" << std::endl;
	for(int stateID = 0; stateID < (int)m_LR0States.size(); stateID++)
	{
		std::cout << "State " << stateID << std::endl;
		LR0State::iterator it;
		for(it = m_LR0States[stateID].state.begin(); it !=  m_LR0States[stateID].state.end(); it++)
		{
			LR0ItemID id = *it;
			std::cout << "   ";
			PrintLR0Item(id);
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

void CLALRGenerator::DumpLR0Kernels()
{
	std::cout << (unsigned)m_LR0States.size() << " states created" << std::endl;
	for(int stateID = 0; stateID < (int)m_LR0States.size(); stateID++)
	{
		std::cout << "State " << stateID << std::endl;
		LR0State::iterator it;
		for(it = m_LR0Kernels[stateID].begin(); it !=  m_LR0Kernels[stateID].end(); it++)
		{
			LR0ItemID id = *it;
			std::cout << "   ";
			PrintLR0Item(id);
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

void CLALRGenerator::DumpLR0Gotos()
{
	for(int stateID = 0; stateID < (int)m_LR0States.size(); stateID++)
	{
		//std::cout << m_LR0States[stateID]
		int id;
		for(id = 0; id < (int)m_Terminals.size(); id++)
		{
			int gotoid = m_LR0States[stateID].m_gotoOnTerminal[id];
			if(gotoid != -1)
			{
				std::cout << "state " << stateID << " on " << m_Terminals[id] << " goto " << gotoid << std::endl;
			}
		}
		for(id = 0; id < (int)m_Nonterminals.size(); id++)
		{
			int gotoid = m_LR0States[stateID].m_gotoOnNonterminal[id];
			if(gotoid != -1)
			{
				std::cout << "state " << stateID << " on " << m_Nonterminals[id] << " goto " << gotoid << std::endl;
			}

		}
	}
}

void CLALRGenerator::ConvertLR0ItemsToKernels()
{
	for(int stateID = 0; stateID < (int) m_LR0States.size(); stateID++)
	{
		LR0State stateKernel;
		LR0State::iterator it;
		for(it = m_LR0States[stateID].state.begin(); it != m_LR0States[stateID].state.end(); it++)
		{
			LR0ItemID itemID = *it;
			const LR0Item& item = m_LR0Items[itemID];
			if(item.second != item.first->GetRight())
			{
				stateKernel.insert(itemID);
			}
			else if(item.first == m_grammar->GetProduction())
			{
				stateKernel.insert(itemID);
			}
		}
		m_LR0Kernels.push_back(stateKernel);
	}
}

void CLALRGenerator::ComputeFirstSets()
{
	std::shared_ptr<IProductions> list = m_grammar;
	while(list != nullptr)
	{
		std::shared_ptr<IProduction> production = list->GetProduction();
		NonterminalID sourceID = production->GetLeft()->GetID();
		if(production->GetRight() == nullptr)
		{
			m_firstSets[sourceID].insert(LookAheadID);
		}
		list = list->GetProductions();
	}
	
	bool bDidSomething;
	do
	{
		list = m_grammar;
		bDidSomething = false;
		while(list != nullptr)
		{
			std::shared_ptr<IProduction> production = list->GetProduction();
			NonterminalID sourceID = production->GetLeft()->GetID();
			std::shared_ptr<ITokenList> tokens = production->GetRight();
			while(tokens != nullptr)
			{
				unsigned tokenID = tokens->GetToken()->GetID();
				if(tokens->GetIsTerminal())
				{
					TerminalID ntid = tokenID;
					if(m_firstSets[sourceID].find(ntid) == m_firstSets[sourceID].end())
					{
						bDidSomething = true;
						m_firstSets[sourceID].insert(ntid);
					}
				}
				else
				{
					std::set<TerminalID> insertSet = m_firstSets[tokenID];
					std::set<TerminalID>::iterator itLoop;
					for(itLoop = insertSet.begin(); itLoop != insertSet.end(); itLoop++)
					{
						if(m_firstSets[sourceID].find(*itLoop) == m_firstSets[sourceID].end())
						{
							bDidSomething = true;
							m_firstSets[sourceID].insert(*itLoop);
						}
					}

					if(m_firstSets[tokenID].find(LookAheadID) != m_firstSets[tokenID].end())
					{
						tokens = tokens->GetTokenList();
						continue;
					}
				}
				break;
			}
			list = list->GetProductions();
		}
	}while(bDidSomething == true);
}


std::set<CLALRGenerator::TerminalID> CLALRGenerator::First(std::shared_ptr<ITokenList> list, TerminalID terminal)
{
	std::set<TerminalID> first;
	std::shared_ptr<ITokenList> tokens = list;
	while(tokens != nullptr)
	{
		unsigned tokenID = tokens->GetToken()->GetID();
		if(tokens->GetIsTerminal())
		{
			first.insert(tokenID);
			return first;
		}
		else
		{
			const std::set<TerminalID>& insertSet = m_firstSets[tokenID];
			std::set<TerminalID>::const_iterator itLoop;
			bool bLookAhead = false;
			for(itLoop = insertSet.begin(); itLoop != insertSet.end(); itLoop++)
			{
				if(*itLoop == LookAheadID)
				{
					bLookAhead = true;
				}
        else
        {
          first.insert(*itLoop); //MOD: 31 Aug 2011, only if it isnt LookAheadID
        }
			}

			if(bLookAhead)
			{
				tokens = tokens->GetTokenList();
				continue;
			}
		}
		return first;
	}

	first.insert(terminal);
	return first;
}

void CLALRGenerator::DumpFirstSets()
{
	std::cout << "Dumping FIRST sets" << std::endl;
	std::map<NonterminalID, std::set<TerminalID> >::iterator it;
	for(it = m_firstSets.begin(); it != m_firstSets.end(); it++)
	{
		NonterminalID id = it->first;
		std::cout << "FIRST(";
		if(id == ntStartSymbol)
		{
			std::cout << "S'";
		}
		else
		{
			if(id > m_Nonterminals.size())
			{
				std::cout << "0x" << (std::hex)<< id;
			}
			else
			{
				std::cout << m_Nonterminals[id];
			}
		}
		std::cout<< ") = {";
		const std::set<TerminalID>& firstSet = it->second;
		if(firstSet.size() > 0)
		{
			std::set<TerminalID>::const_iterator it = firstSet.begin();
			for(;;)
			{
				TerminalID terminalID = *it;
				if(terminalID != LookAheadID)
				{
					std::cout << m_Terminals[terminalID];
				}

				it++;
				if(it == firstSet.end())
				{
					break;
				}
				else
				{
					std::cout << ", ";
				}
			}
		}
		std::cout << "}" << std::endl;
	}
}

void CLALRGenerator::InitLALRTables()
{
	//intialise propagation table, and lookahead table from the LR1LookAheads
	LR0StateID stateID = 0;
	for(stateID = 0; stateID < m_LR0Kernels.size(); stateID++)
	{
		const LR0State& state = m_LR0Kernels[stateID];
		LR0State::const_iterator it;
		for(it = state.begin(); it != state.end(); it++)
		{
			LR0ItemID srcItemID = *it;
			std::pair<LR0StateID, LR0ItemID> sourceItem(stateID, srcItemID);
			LR1State j;
			j[srcItemID].insert(LookAheadID);
			const LR1State jprime = LR1Closure(j);
			LR1State::const_iterator jpIt;
			for(jpIt = jprime.begin(); jpIt != jprime.end(); jpIt++)
			{
				const LR0ItemID itemID = jpIt->first;
				const LR0Item& item = m_LR0Items[itemID];
        //todo: I'm not sure if this is right?
				if(item.second == nullptr)
				{
					const std::set<TerminalID>& terminals = jpIt->second;
					std::set<TerminalID>::const_iterator itTerminal;
					for(itTerminal = terminals.begin(); itTerminal != terminals.end(); itTerminal++)
					{
						TerminalID id = *itTerminal;
						std::pair<LR0StateID, LR0ItemID> targetItem(stateID, itemID);

						if(id == LookAheadID)
						{
							m_propagationTable[sourceItem].insert(targetItem);
						}
						else
						{
							m_LALRItems[targetItem].insert(id);
						}
					}
				}
				else
				{
					bool bTerminal = item.second->GetIsTerminal();
					std::shared_ptr<IToken> token = item.second->GetToken();
					std::shared_ptr<ITokenList> tokenList = item.second->GetTokenList();

					const LR0Item successor(item.first, tokenList);
					LR0ItemID successorID = GetLR0ItemID(successor);

					LR0StateID nextStateID = BADStateID;
					if(bTerminal)
					{
						nextStateID = m_LR0States[stateID].m_gotoOnTerminal[token->GetID()];
					}
					else
					{
						nextStateID = m_LR0States[stateID].m_gotoOnNonterminal[token->GetID()];
					}
					std::pair<LR0StateID, LR0ItemID> targetItem(nextStateID, successorID);
					const std::set<TerminalID>& terminals = jpIt->second;
					std::set<TerminalID>::const_iterator itTerminal;
					for(itTerminal = terminals.begin(); itTerminal != terminals.end(); itTerminal++)
					{
						TerminalID id = *itTerminal;
						if(id == LookAheadID)
						{
							m_propagationTable[sourceItem].insert(targetItem);
						}
						else
						{
							m_LALRItems[targetItem].insert(id);
						}
					}
				}
			}
		}
	}


	//insert it as a lookahead for the base item
	std::shared_ptr<IProduction> startProduction = m_grammar->GetProduction();
	std::shared_ptr<ITokenList> startRight = startProduction->GetRight();

	LR0Item firstItem(startProduction, startRight);
	LR0ItemID firstItemID = GetLR0ItemID(firstItem);
	std::pair<LR0StateID, LR0ItemID> endIndex(0, firstItemID);
	m_LALRItems[endIndex].insert(m_endID);
}

void CLALRGenerator::DumpLALRPropogationTable()
{
	std::map<std::pair<LR0StateID, LR0ItemID>, std::set<std::pair<LR0StateID, LR0ItemID> > >::iterator it;
	for(it = m_propagationTable.begin(); it != m_propagationTable.end(); it++)
	{
		std::cout << "From I" << it->first.first <<": ";
		PrintLR0Item(it->first.second);
		std::cout << std::endl;
		std::set<std::pair<LR0StateID, LR0ItemID> >::const_iterator setIt;
		for(setIt = it->second.begin(); setIt != it->second.end(); setIt++)
		{
			std::cout << "   I" << setIt->first << ": ";
			PrintLR0Item(setIt->second);
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

void CLALRGenerator::DumpLALRLookAheads()
{
	std::map<std::pair<LR0StateID, LR0ItemID>, std::set<TerminalID> >::iterator it;
	for(it = m_LALRItems.begin(); it != m_LALRItems.end(); it++)
	{
		const std::pair<LR0StateID, LR0ItemID>& index = it->first;
		const std::set<TerminalID>& terminals = it->second;
		std::cout << "I" << index.first << ":";
		PrintLR0Item(index.second);
		std::cout << " {";

		std::set<TerminalID>::const_iterator itSet = terminals.begin();
		for(;;)
		{
			TerminalID terminalId = *itSet;
			std::cout << m_Terminals[terminalId];
			itSet++;
			if(itSet == terminals.end())
			{
				break;
			}
			else
			{
				std::cout << ", ";
			}
		}
		std::cout << "}" << std::endl;
	}
}

void CLALRGenerator::ComputeLALRLookAheads()
{
	bool bChanged;
	do
	{
		bChanged = false;
		std::map<std::pair<LR0StateID, LR0ItemID>, std::set<std::pair<LR0StateID, LR0ItemID> > >::iterator it;
		for(it = m_propagationTable.begin(); it != m_propagationTable.end(); it++)
		{
			const std::pair<LR0StateID, LR0ItemID> src = it->first;
			const std::set<std::pair<LR0StateID, LR0ItemID> > &targets = it->second;
			std::set<std::pair<LR0StateID, LR0ItemID> >::const_iterator itTgts;
			const std::set<TerminalID>& srcSet = m_LALRItems[src];
			for(itTgts = targets.begin(); itTgts != targets.end(); itTgts++)
			{
				const std::pair<LR0StateID, LR0ItemID> tgt = *itTgts;
				std::set<TerminalID>::const_iterator itSetSrc;

				const std::set<TerminalID> kEmptySet;
				const std::pair<std::pair<LR0StateID, LR0ItemID>, std::set<TerminalID> > kEmptyItem(tgt,kEmptySet);

				for(itSetSrc = srcSet.begin(); itSetSrc != srcSet.end(); itSetSrc++)
				{
					TerminalID id = *itSetSrc;

					std::pair<std::map<std::pair<LR0StateID, LR0ItemID>, std::set<TerminalID> >::iterator, bool> insertResult;
					insertResult = m_LALRItems.insert(kEmptyItem);
					std::map<std::pair<LR0StateID, LR0ItemID>, std::set<TerminalID> >::iterator itFind = insertResult.first;

					std::set<TerminalID>& tgtTerminals = itFind->second;
					if(tgtTerminals.find(id) == tgtTerminals.end())
					{
						tgtTerminals.insert(id);
						bChanged = true;
					}
				}
			}
		}
	}
	while(bChanged);
}

void CLALRGenerator::GenerateActions()
{
	//setup action function as empty.
	const ActionSet kEmptyActionSet;
	const unsigned nTerminals = (unsigned)m_Terminals.size();
	const StateActions kEmptyStateActions(nTerminals, kEmptyActionSet);
	const unsigned nStates = (unsigned)m_LR0States.size();
	m_actions.resize(nStates, kEmptyStateActions);

	//compute action function.
	unsigned stateID;
	for(stateID = 0; stateID < nStates; stateID++)
	{
		unsigned terminalID;
		for(terminalID = 0; terminalID < nTerminals; terminalID ++)
		{
			unsigned shiftID = m_LR0States[stateID].m_gotoOnTerminal[terminalID];
			if(shiftID != BADStateID)
			{
				m_actions[stateID][terminalID].insert(Action(aShift, shiftID));
			}
		}
	}

	std::map<std::pair<LR0StateID, LR0ItemID>, std::set<TerminalID> >::iterator it;
	for(it = m_LALRItems.begin(); it != m_LALRItems.end(); it++)
	{
		const std::pair<LR0StateID, LR0ItemID> index = it->first;
		LR0Item item = m_LR0Items[index.second];
		unsigned stateID = index.first;
		if(item.second == nullptr)
		{
			int reductionID = item.first->GetID();
			const std::set<TerminalID>& terminals = it->second;
			std::set<TerminalID>::const_iterator itSet;
			for(itSet = terminals.begin(); itSet != terminals.end(); itSet++)
			{
				unsigned terminalID = *itSet;
				m_actions[stateID][terminalID].insert(Action(aReduce, reductionID));
			}
		}
	}
}

CLALRGenerator::ActionSet CLALRGenerator::ComputeImportantActions(const CLALRGenerator::ActionSet& aset)
{
	int bestPrecedence = -1;
	bool bestShifts = true;
	ActionSet bestActions;
	IProduction::Associativity bestAssociativity = IProduction::asNone;
	bestActions.clear();
	ActionSet::const_iterator it;
	for(it = aset.begin(); it != aset.end(); it++)
	{
		bool bCommit = false;
		bool bShifts = false;
		Action a = *it;

		int precedence = -1;
		IProduction::Associativity associativity = IProduction::asNone;
		if(a.first == aShift)
		{
			bShifts = true;
			const LR0State &state = m_LR0Kernels[a.second];
			LR0State::const_iterator itState;
			for(itState = state.begin(); itState != state.end(); itState++)
			{
				int itemID = *itState;
				const LR0Item& item = m_LR0Items[itemID];
				int shiftPrecedence = item.first->GetPrecedence();
				if(shiftPrecedence > precedence)
				{
					precedence = shiftPrecedence;
					associativity = item.first->GetAssociativity();
				}
			}
		}
		else if(a.first == aReduce)
		{
			precedence = m_productions[a.second]->GetPrecedence();
			associativity = m_productions[a.second]->GetAssociativity();
		}

		if(bestActions.size() == 0)
		{
			bCommit = true;
		}
		else if(precedence > bestPrecedence)
		{
			bestActions.clear();
			bCommit = true;
		}
		else if(precedence == bestPrecedence)
		{
			if(associativity == IProduction::asLeft)
			{
				if(bestShifts)
				{
					bCommit = true;
					//if the best actions found so far are shifts
					//then if we have a reduce, we prefer it, so clear
					//them out. otherwise just add the extra shift.
					if(!bShifts)
					{
						bestActions.clear();
					}
				}
				else
				{
					//if the best actions found so far are reductions
					//then if we have a reduction add it,
					//otherwise ignore it, we prefer reductions.
					if(!bShifts)
					{
						bCommit = true;
					}
				}
			}
			else if(associativity == IProduction::asRight)
			{
				if(bestShifts)
				{
					//if the best action found so far is a shift
					//
					if(bShifts)
					{
						bCommit = true;
					}
				}
				else
				{
					bCommit = true;
					if(bShifts)
					{
						bestActions.clear();
					}
				}
			}
			else
			{
				bCommit = true;
			}
		}

		if(bCommit)
		{
			bestActions.insert(a);
			bestAssociativity = associativity;
			bestPrecedence = precedence;
			bestShifts = bShifts;
		}
	}
	return bestActions;
}

void CLALRGenerator::CheckActions()
{
	const unsigned nTerminals = (unsigned)m_Terminals.size();
	const unsigned nStates = (unsigned)m_LR0States.size();

	unsigned stateID;
	for(stateID = 0; stateID < nStates; stateID++)
	{
		bool bConflict = false;
		unsigned terminalID;
		for(terminalID = 0; terminalID < nTerminals; terminalID ++)
		{
			const ActionSet& aset = m_actions[stateID][terminalID];
			if(aset.size() > 1)
			{
				ActionSet iaset = ComputeImportantActions(aset);
				if(iaset.size() > 1)
				{
					bConflict = true;
					std::stringstream str;
					str << "CONFLICT at state " << stateID << " on input " << m_Terminals[terminalID];
					ActionSet::iterator it;
					for(it = iaset.begin(); it != iaset.end(); it++)
					{
						str << std::endl;
						Action a = *it;
						switch(a.first)
						{
						case aShift:
							str << " Shift " << a.second;
							break;
						case aReduce:
							
							str << " Reduce ";
							std::shared_ptr<IProduction> production = m_productions[a.second];
							std::shared_ptr<ITokenList> list = production->GetRight();
							str << production->GetLeft()->GetName() << " ->";
							for(;;)
							{
								if(list == nullptr)
								{
									break;
								}
								str <<" "<< list->GetToken()->GetName();
								list = list->GetTokenList();
							}
							break;
						}
					}
					m_errorHandler->EmitError(str.str());
				}
				else
				{
					m_actions[stateID][terminalID] = iaset;
				}
			}
		}
		if(bConflict)
		{
			const LR0State& state = m_LR0States[stateID].state;
			LR0State::const_iterator it;
			std::cerr << "State " << stateID <<":\n";
			for(it = state.begin(); it != state.end(); it++)
			{
				LR0ItemID id = *it;
				const LR0Item& item = m_LR0Items[id];
				std::shared_ptr<IProduction> production = item.first;
				std::shared_ptr<ITokenList> list = production->GetRight();
				std::shared_ptr<ITokenList> tokens = item.second;
				std::cerr << production->GetLeft()->GetName() << " ->";
				for(;;)
				{
					if(list == tokens)
					{
						std::cerr << " .";
					}
					if(list == nullptr)
					{
						break;
					}
					std::cerr <<" "<< list->GetToken()->GetName();
					list = list->GetTokenList();
				}
				std::cerr << std::endl;
			}
		}
	}
}

void PrintHeader(std::ostream& os, const std::string& filename)
{
	os << "/*\n   " << filename << ", generated by wbcparse (c) Phillip Voyle 2005 - 2021.\n*/\n" << std::endl;

}

void CLALRGenerator::DumpParseTables()
{
	const unsigned nTerminals = (unsigned)m_Terminals.size();
	const unsigned nNonterminals = (unsigned)m_Nonterminals.size();
	const unsigned nStates = (unsigned)m_LR0States.size();

	std::string sParserName = "CLALRGenParser";
	std::string sParserHeader = "LALRGenParser.h";

	std::string sTableName = "CLALRGenParserTable";
	std::string sTableHeader = "LALRGenParserTable.h";
	std::string sTableSource = "LALRGenParserTable.cpp";

	ReadVariable("$PARSERNAME", sParserName);
	ReadVariable("$PARSERHEADER", sParserHeader);

	ReadVariable("$TABLENAME", sTableName);
	ReadVariable("$TABLEHEADER", sTableHeader);
	ReadVariable("$TABLESOURCE", sTableSource);

	std::ofstream fParserHeader(sParserHeader.c_str());

	std::ofstream fTableSource(sTableSource.c_str());
	std::ofstream fTableHeader(sTableHeader.c_str());

	fTableHeader << "#pragma once\n\n";
	fParserHeader << "#pragma once\n\n";

	PrintHeader(fParserHeader, sParserHeader);
	PrintHeader(fTableHeader, sTableHeader);
	PrintHeader(fTableSource, sTableSource);

	fTableHeader << "#include <utility>\n";
	fTableHeader << "#include <string>\n";
	fTableHeader << "class " << sTableName << std::endl;
	fTableHeader << "{\n";
	fTableHeader << "public:\n";
	fTableHeader << "   enum ActionID {aShift, aReduce, aError};\n";
	fTableHeader << "   enum TokenID{\n";

  int nTokenID = 0;
	for(unsigned terminalID = 0; terminalID < nTerminals; terminalID ++)
	{
		fTableHeader << "      "<< m_Terminals[terminalID] << " = " << (nTokenID ++);
		if(terminalID + 1 != nTerminals + nNonterminals)
		{
			fTableHeader << ",";
		}
		fTableHeader << "\n";
	}
	for(unsigned nonterminalID = 0; nonterminalID < nNonterminals; nonterminalID ++)
	{
		fTableHeader << "      "<< m_Nonterminals[nonterminalID] << " = " << (nTokenID ++);
		if(nonterminalID + 1 != nNonterminals)
		{
			fTableHeader << ",";
		}
		fTableHeader << "\n";
	}
	fTableHeader << "   };\n";

	fTableHeader << "   typedef std::pair<ActionID, unsigned> Action;\n";
	fTableHeader << "private:\n";
	fTableHeader << "   static const unsigned kTerminals = "<< nTerminals << ";\n";
	fTableHeader << "   static const unsigned kNonterminals = " << nNonterminals << ";\n";
	fTableHeader << "   static const unsigned kStates = " << nStates << ";\n";
	fTableHeader << "   static const Action s_actionTable[kStates][kTerminals];\n";
	fTableHeader << "   static const int s_gotoTable[kStates][kNonterminals];\n";
  fTableHeader << "   static const int s_earlyReduce[kStates];\n";
  fTableHeader << "   static const std::string s_tokenNames[kTerminals + kNonterminals];\n";
	fTableHeader << "public:\n";
	fTableHeader << "   static const Action& GetAction(int nStateID, int nTerminalID);\n";
	fTableHeader << "   static int GetGoto(int nStateID, int nNonterminalID);\n";
  fTableHeader << "   static int GetEarlyReduce(int nStateID);\n";
  fTableHeader << "   static std::string GetTokenName(TokenID id);\n";
	fTableHeader << "};\n\n";

	fTableSource << "#include <assert.h>\n";
	fTableSource << "#include \"" << sTableHeader <<"\"\n\n";
	fTableSource << "const " << sTableName << "::Action "<< sTableName << "::s_actionTable[" << sTableName << "::kStates][" << sTableName << "::kTerminals] = {" << std::endl;
	unsigned stateID;
  
  std::vector<int> m_earlyReduce;
  
	for(stateID = 0; stateID < nStates; stateID++)
	{
		fTableSource << "   {";
		unsigned terminalID;
    std::set<int> reductionSet;
            
		for(terminalID = 0; terminalID < nTerminals; terminalID ++)
		{
			const ActionSet& aset = m_actions[stateID][terminalID];
			fTableSource << sTableName << "::Action(" ;
			if(aset.size() > 0)
			{
				Action action = *(aset.begin());
				switch(action.first)
				{
				case aShift:
					fTableSource << sTableName << "::aShift";
          reductionSet.insert(-1);
					break;
				case aReduce:
					fTableSource << sTableName << "::aReduce";
          reductionSet.insert(action.second);
					break;
				}
				fTableSource << ", " << action.second;

			}
			else
			{
				fTableSource << sTableName << "::aError, 0";
			}
			fTableSource << ")";
			if(terminalID + 1 < nTerminals)
			{
				fTableSource << ", ";
			}
		}
		fTableSource << "}";
		if(stateID + 1 < nStates)
		{
			fTableSource << ", ";
		}
		fTableSource << std::endl;
    
    if(reductionSet.size() == 1)
    {
      m_earlyReduce.push_back(*reductionSet.begin());
    }
    else
    {
      m_earlyReduce.push_back(-1);
    }
	}
	fTableSource << "};\n" << std::endl;

  fTableSource << "const " << "int " << sTableName << "::s_gotoTable[" << sTableName << "::kStates][" << sTableName << "::kNonterminals] = {" << std::endl;  
	for(stateID = 0; stateID < nStates; stateID++)
	{
		fTableSource << "   {";
		unsigned nonterminalID;
		for(nonterminalID = 0; nonterminalID < nNonterminals; nonterminalID ++)
		{
			fTableSource << (int)(m_LR0States[stateID].m_gotoOnNonterminal[nonterminalID]);
			if(nonterminalID + 1 < nNonterminals)
			{
				fTableSource << ", ";
			}
		}
		fTableSource << "}";
		if(stateID + 1 < nStates)
		{
			fTableSource << ", ";
		}
		fTableSource << std::endl;
	}
  fTableSource << "};\n\n" << std::endl;
	
  fTableSource << "const int " << sTableName << "::s_earlyReduce[" << sTableName<< "::kStates] = {" << std::endl;
  for(stateID = 0; stateID < nStates; stateID++)
  {
		fTableSource << "   ";
    fTableSource << m_earlyReduce[stateID];
		if(stateID + 1 < nStates)
    {
      fTableSource << ", ";
    }
    fTableSource << std::endl;
  }
  
	fTableSource << "};\n\n" << std::endl;
  fTableSource << "const std::string " << sTableName << "::s_tokenNames["<< sTableName << "::kTerminals + " << sTableName << "::kNonterminals] = {\n";

	for(unsigned terminalID = 0; terminalID < nTerminals; terminalID ++)
	{
		fTableSource << "      \""<< m_Terminals[terminalID] << "\"";
		if(terminalID + 1 != nTerminals + nNonterminals)
		{
			fTableSource << ",";
		}
		fTableSource << "\n";
	}
	for(unsigned nonterminalID = 0; nonterminalID < nNonterminals; nonterminalID ++)
	{
		fTableSource << "      \""<< m_Nonterminals[nonterminalID] << "\"";
		if(nonterminalID + 1 != nNonterminals)
		{
			fTableSource << ",";
		}
		fTableSource << "\n";
	}
  
  fTableSource << "};\n\n" << std::endl;
	fTableSource << "const " << sTableName << "::Action& " << sTableName << "::GetAction(int stateID, int tokenID)\n";
	fTableSource << "{\n";
	fTableSource << "   assert(stateID >= 0 && stateID < kStates);\n";
	fTableSource << "   assert(tokenID >= 0 && tokenID < kTerminals);\n";
	fTableSource << "   return s_actionTable[stateID][tokenID];\n";
	fTableSource << "}\n\n";
	fTableSource << "int " << sTableName << "::GetGoto(int stateID, int tokenID)\n";
	fTableSource << "{\n";
	fTableSource << "   assert(stateID >= 0 && stateID < kStates);\n";
	fTableSource << "   assert(tokenID >= kTerminals && tokenID < kTerminals + kNonterminals);\n";
	fTableSource << "   return s_gotoTable[stateID][tokenID - kTerminals];\n";
	fTableSource << "}\n\n";
	fTableSource << "int " << sTableName << "::GetEarlyReduce(int stateID)\n";
	fTableSource << "{\n";
	fTableSource << "   assert(stateID >= 0 && stateID < kStates);\n";
	fTableSource << "   return s_earlyReduce[stateID];\n";
	fTableSource << "}\n\n";
  
  fTableSource << "std::string " << sTableName << "::GetTokenName(" << sTableName << "::TokenID id)\n";
  fTableSource << "{\n";
  fTableSource << "   assert(id >= 0 && id < kTerminals + kNonterminals);\n";
  fTableSource << "   return s_tokenNames[id];\n";
  fTableSource << "}\n\n";
  
	fParserHeader << "#include \"LRToken.h\"\n";
	fParserHeader << "#include \"" << sTableHeader << "\"\n";
	fParserHeader << "#include <assert.h>\n\n";

  fParserHeader << "/*\n   Type Definitions:\n   wbcparse generates type defining classes for each\n";
	fParserHeader << "*/\n";
  for(unsigned terminalID = 0; terminalID < nTerminals; terminalID ++)
	{
		fParserHeader << "template<>\n";
		fParserHeader << "template<>\n";
		fParserHeader << "class CLRToken<" << sTableName << "::TokenID>::TokenType<" << sTableName << "::" << m_Terminals[terminalID] << ">\n";
		fParserHeader << "{\n";
		fParserHeader << "public:\n";
		fParserHeader << "   typedef " << getStoreType(m_Terminals[terminalID]) << " storeClass;\n";
		fParserHeader << "   typedef " << getTransType(m_Terminals[terminalID]) << " transClass;\n";
		fParserHeader << "};\n\n";
	}
  
	for(unsigned nonterminalID = 0; nonterminalID < nNonterminals; nonterminalID ++)
	{
		fParserHeader << "template<>\n";
		fParserHeader << "template<>\n";
		fParserHeader << "class CLRToken<" << sTableName << "::TokenID>::TokenType<" << sTableName << "::" << m_Nonterminals[nonterminalID] << ">\n";
		fParserHeader << "{\n";
		fParserHeader << "public:\n";
		fParserHeader << "   typedef " << getStoreType(m_Nonterminals[nonterminalID]) << " storeClass;\n";
		fParserHeader << "   typedef " << getTransType(m_Nonterminals[nonterminalID]) << " transClass;\n";
		fParserHeader << "};\n\n";
	}
  
	fParserHeader << "template <class TBase>\n";
	fParserHeader << "class " << sParserName << std::endl;
	fParserHeader << "   :public TBase\n";
	fParserHeader << "{\n";
	fParserHeader << "public:\n";
	fParserHeader << "   typedef " << sTableName << "::TokenID TokenID;\n";
	fParserHeader << "   typedef CLRToken<" << sTableName << "::TokenID> Token;\n";
	fParserHeader << "   typedef Token::TokenPtr TokenPtr;\n";
	fParserHeader << "private:\n";
	fParserHeader << "   typedef " << sTableName << "::ActionID ActionID;\n";
	fParserHeader << "   TokenPtr m_stack;\n";
	fParserHeader << "public:\n";
	fParserHeader << "   template<typename...TArgs>\n";
  fParserHeader << "   " << sParserName << "(TArgs...args):TBase(args...)\n";
	fParserHeader << "   {\n";
	fParserHeader << "      init();\n";
	fParserHeader << "   }\n";
  fParserHeader << "   bool reduce(int nReduce)\n";
  fParserHeader << "   {\n";
	fParserHeader << "      TokenPtr reduced;\n";
	fParserHeader << "      int nextState = -1;\n";
	fParserHeader << "      switch(nReduce)\n";
	fParserHeader << "      {\n";
  
	std::shared_ptr<IProductions> productions = m_grammar;
	int nProductionID = 0;
	while(productions != nullptr)
	{
		std::shared_ptr<IProduction> production = productions->GetProduction();
		fParserHeader << "      case " << nProductionID << ":\n";
		fParserHeader << "      {\n";
		std::string storeType = getStoreType(production->GetLeft()->GetName());
		if(storeType != "void")
		{
			fParserHeader << "         " << storeType << " $$;\n";
		}
		std::shared_ptr<ITokenList> tokens = production->GetRight();
		if(nProductionID == 0)
		{
			std::shared_ptr<IToken> token = tokens->GetToken();
			std::string sstoreType = getStoreType(token->GetName());
			fParserHeader << "         this->Accept(";
			if(sstoreType != "void")
			{
				fParserHeader << "m_stack->GetData<" << sTableName << "::" << token->GetName() <<">()";
			}
			fParserHeader << ");\n";
			fParserHeader << "         m_stack = TokenPtr();\n";
			fParserHeader << "         return false;\n";
			fParserHeader << "      }\n";
		}
		else
		{
			std::vector<std::shared_ptr<IToken>> tokenVec;
			while(tokens != nullptr)
			{
				tokenVec.push_back(tokens->GetToken());
				tokens = tokens->GetTokenList();
			}
			while(!tokenVec.empty())
			{
				std::shared_ptr<IToken> token = tokenVec.back();
				std::string sstoreType = getStoreType(token->GetName());
				if(sstoreType != "void")
				{
					fParserHeader << "         " << sstoreType << " $" << (int)tokenVec.size();
					fParserHeader << " = m_stack->GetData<" << sTableName << "::" << token->GetName() <<">();\n";
				}
				fParserHeader << "         m_stack = m_stack->GetNext();//pop " << token->GetName() <<"\n";
				tokenVec.pop_back();
			}

			fParserHeader << production->GetResponse() << std::endl;
			fParserHeader << "         nextState = " << sTableName << "::GetGoto(m_stack->GetState(), " << sTableName << "::" << production->GetLeft()->GetName() << ");\n";
			if (storeType == "void")
			{
				fParserHeader << "         reduced = Token::CreateToken_VOID<" << sTableName << "::" << production->GetLeft()->GetName() << ">(";
			}
			else
			{
				fParserHeader << "         reduced = Token::CreateToken<" << sTableName << "::" <<  production->GetLeft()->GetName()  <<">(";
				fParserHeader << "$$";
			}
			fParserHeader << ");\n";
			fParserHeader << "         }\n";
			fParserHeader << "         break;\n";
		}
		productions = productions->GetProductions();
		nProductionID ++;
	}
	fParserHeader << "      default:\n";
	fParserHeader << "         return false;\n";
	fParserHeader << "      }\n";
	fParserHeader << "      if(nextState == -1)\n";
	fParserHeader << "      {\n";
	fParserHeader << "         this->ParserError(reduced);\n";
	fParserHeader << "      }\n";
	fParserHeader << "      else\n";
	fParserHeader << "      {\n";
	fParserHeader << "         reduced->SetState(nextState);\n";
	fParserHeader << "         reduced->SetNext(m_stack);\n";
	fParserHeader << "         m_stack = reduced;\n";
	fParserHeader << "      }\n";
  fParserHeader << "      return true;\n";
  fParserHeader << "   }\n";
  
  fParserHeader << "   void perform_early_reductions()\n";
  fParserHeader << "   {\n";
  fParserHeader << "     int nEarlyReduce = 0;\n";
  fParserHeader << "     do\n";
  fParserHeader << "     {\n";
  fParserHeader << "        nEarlyReduce = " << sTableName << "::GetEarlyReduce(m_stack->GetState());\n";
  fParserHeader << "        if(nEarlyReduce < 1)\n";
  fParserHeader << "        {\n";
  fParserHeader << "           return;\n";
  fParserHeader << "        }\n";
  fParserHeader << "      }while(reduce(nEarlyReduce));\n";
  fParserHeader << "   }\n\n";
	fParserHeader << "   void init()\n";
	fParserHeader << "   {\n";
	fParserHeader << "      m_stack = Token::CreateToken_VOID<" << sTableName << "::$>(); //init stack with state 0.\n";
	fParserHeader << "      m_stack->SetState(0);\n";
	fParserHeader << "   }\n";
	fParserHeader << "   void step(TokenPtr ptr)\n";
	fParserHeader << "   {\n";
	fParserHeader << "      const TokenID token = ptr->GetTokenID();\n";
	fParserHeader << "      for(;;)\n";
	fParserHeader << "      {\n";
	fParserHeader << "         const " << sTableName << "::Action action = " << sTableName << "::GetAction(m_stack->GetState(), token);\n";
	fParserHeader << "         switch(action.first)\n";
	fParserHeader << "         {\n";
	fParserHeader << "         case " << sTableName << "::aShift:\n";
	fParserHeader << "            ptr->SetNext(m_stack);\n";
	fParserHeader << "            ptr->SetState(action.second);\n";
	fParserHeader << "            m_stack = ptr;\n";
  fParserHeader << "            perform_early_reductions();\n";
	fParserHeader << "            return;\n";
	fParserHeader << "         case " << sTableName << "::aReduce:\n";
	fParserHeader << "            {\n";
  fParserHeader << "               if(!reduce(action.second))\n";
  fParserHeader << "               {\n";
  fParserHeader << "                  return;\n";
  fParserHeader << "               }\n";
	fParserHeader << "            }\n";
	fParserHeader << "            break;\n";
	fParserHeader << "         case " << sTableName << "::aError:\n";
	fParserHeader << "         default:\n";
	fParserHeader << "            this->ParserError(ptr);\n";
	fParserHeader << "            return;\n";
	fParserHeader << "         }\n";
	fParserHeader << "      }\n";
	fParserHeader << "   }\n";
	fParserHeader << "};\n\n";
}


void CLALRGenerator::setType(const std::string& varName, const std::string &storeType, const std::string& transType)
{
	m_tokenTypes[varName] = std::pair<std::string, std::string>(storeType, transType);
}

bool CLALRGenerator::checkVar(const std::string& varName)
{
	return m_tokenTypes.find(varName) != m_tokenTypes.end();
}

std::string CLALRGenerator::getStoreType(const std::string& varName)
{
	std::map<std::string, std::pair<std::string, std::string> >::iterator it = m_tokenTypes.find(varName);
	if(it != m_tokenTypes.end())
	{
		return it->second.first;
	}
	else
	{
		std::stringstream str;
		str << "token " << varName << " not defined";
		m_errorHandler->EmitError(str.str());
		return "void";
	}
}

std::string CLALRGenerator::getTransType(const std::string& varName)
{
	std::map<std::string, std::pair<std::string, std::string> >::iterator it = m_tokenTypes.find(varName);
	if(it != m_tokenTypes.end())
	{
		return it->second.second;
	}
	else
	{
		std::stringstream str;
		str << "token " << varName << " not defined";
		m_errorHandler->EmitError(str.str());
		return "void";
	}
}

void CLALRGenerator::SetErrorHandler(CErrorHandler* errorHandler)
{
	m_errorHandler = errorHandler;
}
