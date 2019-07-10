#pragma once

#include <map>
#include <vector>
#include <set>
#include "production.h"

class CErrorHandler;

class CLALRGenerator
{
public:
  typedef unsigned NonterminalID;
	typedef unsigned TerminalID;
	typedef unsigned LR0StateID;

private:
	CErrorHandler* m_errorHandler;
	std::map<std::string, std::string> m_variables;
	std::map<std::string, std::pair<std::string, std::string> > m_tokenTypes;

	static std::string DecipherString(const std::string& s);
	static char EscapeChar(char c);

	std::vector<IProduction*> m_productions;

	bool m_bError;

	IProductions* m_grammar;

	std::vector<std::string> m_Nonterminals;
	std::map<std::string, NonterminalID> m_NonterminalIDs;

	std::vector<std::string> m_Terminals;
	std::map<std::string, TerminalID> m_TerminalIDs;
	TerminalID m_endID;

	typedef std::pair<IProduction*, ITokenList*> LR0Item;
	typedef unsigned LR0ItemID;

	std::vector<LR0Item> m_LR0Items;
	std::map<LR0Item, LR0ItemID> m_LR0ItemIDs;

	LR0ItemID GetLR0ItemID(const LR0Item& item);

	typedef std::set<LR0ItemID> LR0State;
	
	struct LR0StateData
	{
		LR0State state;
		std::vector<LR0StateID> m_gotoOnTerminal;
		std::vector<LR0StateID> m_gotoOnNonterminal;
	};

	std::map<NonterminalID, std::set<TerminalID> > m_firstSets;
	void ComputeFirstSets();
	std::set<TerminalID> First(ITokenList* list, TerminalID terminal);

	std::vector<LR0State> m_LR0Kernels;
	std::vector<LR0StateData> m_LR0States;
	std::map<LR0State, LR0StateID> m_LR0StateIDs;

	LR0StateID GetLR0StateID(const LR0State& state);
	LR0StateID GetLR0Goto(LR0StateID id, const std::string& token);

	typedef std::map<LR0ItemID, std::set<TerminalID> > LR1State;

	std::map<std::pair<LR0StateID, LR0ItemID>, std::set<std::pair<LR0StateID, LR0ItemID> > > m_propagationTable;
	std::map<std::pair<LR0StateID, LR0ItemID>, std::set<TerminalID> > m_LALRItems;

	void ProcessSymbols();
	LR0State LR0Closure(const LR0State& I);
	void GenerateLR0Items();
	void ConvertLR0ItemsToKernels();

	LR1State LR1Closure(const LR1State& I);

	enum ActionType {aShift, aReduce};
	typedef std::pair<ActionType, unsigned> Action;
	typedef std::set<Action> ActionSet;
	typedef std::vector<ActionSet> StateActions;
	std::vector<StateActions> m_actions;

	void InitLALRTables();
	void DumpLALRPropogationTable();
	void DumpLALRLookAheads();
	void ComputeLALRLookAheads();
	void GenerateActions();
	void CheckActions();
	void DumpParseTables();
	void DumpLR0Gotos();


	void PrintLR0Item(LR0ItemID itemID);
	void DumpLR0States();
	void DumpLR0Kernels();
	void DumpFirstSets();

	//variables from parse
	bool ReadVariable(const std::string& strName, std::string& strValue);

	//token types from parse
	std::string getStoreType(const std::string& varName);
	std::string getTransType(const std::string& varName);

	ActionSet ComputeImportantActions(const ActionSet& aset);

public:
	void SetErrorHandler(CErrorHandler* errorHandler);
	void assignVariable(const std::string&,const std::string&);
	void setType(const std::string& varName, const std::string& storeType, const std::string& TransType);
	bool checkVar(const std::string& varName);
	CLALRGenerator();
	virtual ~CLALRGenerator();
	void GenerateParser(std::auto_ptr<IProductions> &parseTree);
};