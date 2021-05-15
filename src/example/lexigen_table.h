/*
    lexigen_table.h
    Generated by wbclex Scanner Generator (C) Phillip Voyle 2011 - 2021
*/

#pragma once

class CLexigenTable
{
public:
   enum stateIDs
   {
      stStart,
      stNumStates
   };

private:
   static const int kStates = 1;
   static const int kInnerStates = 13;

   static const int s_dataOffsets[kStates];
   static const int s_announceOnEOF[kStates];
   static const bool s_canEarlyAnnounce[kInnerStates];
   static const int s_announceData[kInnerStates];

public:
   static int GetAnnounce(int state, int nInnerState);
   static bool CanEarlyAnnounce(int state, int nInnerState);
   static int GetAnnounceOnEOF(int state);
   static int GetTransition(int state, int nInnerState, char c);
};

