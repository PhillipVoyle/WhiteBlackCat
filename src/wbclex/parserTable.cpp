/*
   parserTable.cpp, generated by wbcparse (c) Phillip Voyle 2005 - 2021.
*/

#include <assert.h>
#include "parserTable.h"

const CParserTable::Action CParserTable::s_actionTable[CParserTable::kStates][CParserTable::kTerminals] = {
   {CParserTable::Action(CParserTable::aReduce, 4), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 4), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 4), CParserTable::Action(CParserTable::aReduce, 4), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 4)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 0)}, 
   {CParserTable::Action(CParserTable::aShift, 4), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 6), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 6), CParserTable::Action(CParserTable::aReduce, 6), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 6)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 8), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 12), CParserTable::Action(CParserTable::aReduce, 12), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 12)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 9), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 11), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 1)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 7), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 7)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 10), CParserTable::Action(CParserTable::aShift, 13), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 10)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 14), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 15), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 12), CParserTable::Action(CParserTable::aReduce, 12), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 12)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 17), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 11), CParserTable::Action(CParserTable::aReduce, 11), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 11)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 18), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 19), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 20), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aReduce, 3), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 3), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 3), CParserTable::Action(CParserTable::aReduce, 3), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 3)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 8), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 8)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 21), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aShift, 23), CParserTable::Action(CParserTable::aShift, 24), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 25), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aShift, 23), CParserTable::Action(CParserTable::aShift, 24), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 9), CParserTable::Action(CParserTable::aReduce, 9), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 9)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 28), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 29), CParserTable::Action(CParserTable::aShift, 30), CParserTable::Action(CParserTable::aShift, 31), CParserTable::Action(CParserTable::aShift, 32), CParserTable::Action(CParserTable::aShift, 23), CParserTable::Action(CParserTable::aShift, 24), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 20), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 20), CParserTable::Action(CParserTable::aReduce, 20), CParserTable::Action(CParserTable::aReduce, 20), CParserTable::Action(CParserTable::aReduce, 20), CParserTable::Action(CParserTable::aReduce, 20), CParserTable::Action(CParserTable::aReduce, 20), CParserTable::Action(CParserTable::aReduce, 20), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aShift, 23), CParserTable::Action(CParserTable::aShift, 24), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 14), CParserTable::Action(CParserTable::aReduce, 14), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 14)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 34), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 29), CParserTable::Action(CParserTable::aShift, 30), CParserTable::Action(CParserTable::aShift, 31), CParserTable::Action(CParserTable::aShift, 32), CParserTable::Action(CParserTable::aShift, 23), CParserTable::Action(CParserTable::aShift, 24), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 16), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 16), CParserTable::Action(CParserTable::aShift, 30), CParserTable::Action(CParserTable::aShift, 31), CParserTable::Action(CParserTable::aShift, 32), CParserTable::Action(CParserTable::aShift, 23), CParserTable::Action(CParserTable::aShift, 24), CParserTable::Action(CParserTable::aReduce, 16), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 35), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aShift, 23), CParserTable::Action(CParserTable::aShift, 24), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 17), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 17), CParserTable::Action(CParserTable::aReduce, 17), CParserTable::Action(CParserTable::aReduce, 17), CParserTable::Action(CParserTable::aReduce, 17), CParserTable::Action(CParserTable::aReduce, 17), CParserTable::Action(CParserTable::aReduce, 17), CParserTable::Action(CParserTable::aReduce, 17), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 18), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 18), CParserTable::Action(CParserTable::aReduce, 18), CParserTable::Action(CParserTable::aReduce, 18), CParserTable::Action(CParserTable::aReduce, 18), CParserTable::Action(CParserTable::aReduce, 18), CParserTable::Action(CParserTable::aReduce, 18), CParserTable::Action(CParserTable::aReduce, 18), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 19), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 19), CParserTable::Action(CParserTable::aReduce, 19), CParserTable::Action(CParserTable::aReduce, 19), CParserTable::Action(CParserTable::aReduce, 19), CParserTable::Action(CParserTable::aReduce, 19), CParserTable::Action(CParserTable::aReduce, 19), CParserTable::Action(CParserTable::aReduce, 19), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 29), CParserTable::Action(CParserTable::aShift, 30), CParserTable::Action(CParserTable::aShift, 31), CParserTable::Action(CParserTable::aShift, 32), CParserTable::Action(CParserTable::aShift, 23), CParserTable::Action(CParserTable::aShift, 24), CParserTable::Action(CParserTable::aShift, 37), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 5), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 5), CParserTable::Action(CParserTable::aReduce, 5), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 5)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 13), CParserTable::Action(CParserTable::aReduce, 13), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 13)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 15), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 15), CParserTable::Action(CParserTable::aShift, 30), CParserTable::Action(CParserTable::aShift, 31), CParserTable::Action(CParserTable::aShift, 32), CParserTable::Action(CParserTable::aShift, 23), CParserTable::Action(CParserTable::aShift, 24), CParserTable::Action(CParserTable::aReduce, 15), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 21), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 21), CParserTable::Action(CParserTable::aReduce, 21), CParserTable::Action(CParserTable::aReduce, 21), CParserTable::Action(CParserTable::aReduce, 21), CParserTable::Action(CParserTable::aReduce, 21), CParserTable::Action(CParserTable::aReduce, 21), CParserTable::Action(CParserTable::aReduce, 21), CParserTable::Action(CParserTable::aError, 0)}
};

const int CParserTable::s_gotoTable[CParserTable::kStates][CParserTable::kNonterminals] = {
   {1, -1, 2, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, 3, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, 5, -1, 6, 7, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, 10, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, 12}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, 16, 7, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, 22, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, 26, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, 27, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, 33, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, 27, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, 27, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, 36, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, 27, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, 27, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1}
};


const int CParserTable::s_earlyReduce[CParserTable::kStates] = {
   4, 
   0, 
   -1, 
   -1, 
   -1, 
   -1, 
   7, 
   -1, 
   -1, 
   -1, 
   12, 
   -1, 
   11, 
   -1, 
   -1, 
   3, 
   8, 
   -1, 
   -1, 
   -1, 
   -1, 
   9, 
   -1, 
   20, 
   -1, 
   14, 
   -1, 
   -1, 
   -1, 
   -1, 
   17, 
   18, 
   19, 
   -1, 
   5, 
   13, 
   -1, 
   21
};


const std::string CParserTable::s_tokenNames[CParserTable::kTerminals + CParserTable::kNonterminals] = {
      "tVariableName",
      "tAssign",
      "tLiteral",
      "tIdentifier",
      "tBeginRegexp",
      "tFinishedRegexp",
      "tState",
      "tOn",
      "tResponse",
      "tEOF",
      "tOr",
      "tPlus",
      "tStar",
      "tQMark",
      "tRegexp",
      "tOpen",
      "tClose",
      "$",
      "ntProgram",
      "ntRegexp",
      "ntAssignVariables",
      "ntAssignDefinitions",
      "ntInitStates",
      "ntStateAssignment",
      "ntInitOneState",
      "ntEvents",
      "ntEvent"
};


const CParserTable::Action& CParserTable::GetAction(int stateID, int tokenID)
{
   assert(stateID >= 0 && stateID < kStates);
   assert(tokenID >= 0 && tokenID < kTerminals);
   return s_actionTable[stateID][tokenID];
}

int CParserTable::GetGoto(int stateID, int tokenID)
{
   assert(stateID >= 0 && stateID < kStates);
   assert(tokenID >= kTerminals && tokenID < kTerminals + kNonterminals);
   return s_gotoTable[stateID][tokenID - kTerminals];
}

int CParserTable::GetEarlyReduce(int stateID)
{
   assert(stateID >= 0 && stateID < kStates);
   return s_earlyReduce[stateID];
}

std::string CParserTable::GetTokenName(CParserTable::TokenID id)
{
   assert(id >= 0 && id < kTerminals + kNonterminals);
   return s_tokenNames[id];
}

