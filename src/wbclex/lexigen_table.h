/*
    lexigen_table.h
    Generated by Lexigen Scanner Generator (C) Phillip Voyle 2011
*/

#pragma once

class CLexerTable
{
public:
   enum stateIDs
   {
      stComment,
      stDef,
      stRegexp,
      stResponse,
      stStart,
      stNumStates
   };

private:
   static const int kStates = 5;
   static const int kInnerStates = 76;

   static const int s_dataOffsets[kStates];
   static const int s_announceOnEOF[kStates];
   static const int s_announceData[kInnerStates];
   static const int s_transitionData[kInnerStates][128];

public:
   static int GetAnnounce(int state, int nInnerState);
   static int GetAnnounceOnEOF(int state);
   static int GetTransition(int state, int nInnerState, char c);
};
