#pragma once

/*
   parserTable.h, generated by ParserGenie (c) Phillip Voyle 2005.
*/

#include <utility>
class CParserTable
{
public:
   enum ActionID {aShift, aReduce, aError};
   enum TokenID{
      tSemicolon = 0,
      tVariableName = 1,
      tAssign = 2,
      tLiteral = 3,
      tToken = 4,
      tTokenType = 5,
      tIdentifier = 6,
      tComma = 7,
      tProduction = 8,
      tResponse = 9,
      tLeft = 10,
      tRight = 11,
      tNone = 12,
      $ = 13,
      program = 14,
      ntVariables = 15,
      ntAssignVariable = 16,
      ntTokenDefs = 17,
      ntTokenDef = 18,
      ntTokenType = 19,
      ntTokenNames = 20,
      ntTokenNameList = 21,
      ntRules = 22,
      ntRule = 23,
      ntRightSide = 24
   };
   typedef std::pair<ActionID, unsigned> Action;
private:
   static const unsigned kTerminals = 14;
   static const unsigned kNonterminals = 11;
   static const unsigned kStates = 33;
   static const Action s_actionTable[kStates][kTerminals];
   static const int s_gotoTable[kStates][kNonterminals];
   static const int s_earlyReduce[kStates];
   static const char* s_tokenNames[kTerminals + kNonterminals];
public:
   static const Action& GetAction(int nStateID, int nTerminalID);
   static int GetGoto(int nStateID, int nNonterminalID);
   static int GetEarlyReduce(int nStateID);
   static const char* GetTokenName(TokenID id);
};

