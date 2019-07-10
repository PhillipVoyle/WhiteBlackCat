/*
   parserTable.cpp, generated by ParserGenie (c) Phillip Voyle 2005.
*/

#include <assert.h>
#include "parserTable.h"

const CParserTable::Action CParserTable::s_actionTable[CParserTable::kStates][CParserTable::kTerminals] = {
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 3), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 3), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 3), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 3), CParserTable::Action(CParserTable::aReduce, 3), CParserTable::Action(CParserTable::aReduce, 3), CParserTable::Action(CParserTable::aReduce, 3)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 7), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 8), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 6), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 6), CParserTable::Action(CParserTable::aReduce, 6), CParserTable::Action(CParserTable::aReduce, 6), CParserTable::Action(CParserTable::aReduce, 6)}, 
   {CParserTable::Action(CParserTable::aShift, 9), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 12), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 13), CParserTable::Action(CParserTable::aShift, 14), CParserTable::Action(CParserTable::aShift, 15), CParserTable::Action(CParserTable::aReduce, 14)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 8), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 6), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 6), CParserTable::Action(CParserTable::aReduce, 6), CParserTable::Action(CParserTable::aReduce, 6), CParserTable::Action(CParserTable::aReduce, 6)}, 
   {CParserTable::Action(CParserTable::aShift, 19), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 20), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 21), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 22), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2), CParserTable::Action(CParserTable::aReduce, 2)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 1)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 12), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 13), CParserTable::Action(CParserTable::aShift, 14), CParserTable::Action(CParserTable::aShift, 15), CParserTable::Action(CParserTable::aReduce, 14)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 24), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 16), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 16), CParserTable::Action(CParserTable::aReduce, 16), CParserTable::Action(CParserTable::aReduce, 16), CParserTable::Action(CParserTable::aReduce, 16)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 17), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 17), CParserTable::Action(CParserTable::aReduce, 17), CParserTable::Action(CParserTable::aReduce, 17), CParserTable::Action(CParserTable::aReduce, 17)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 18), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 18), CParserTable::Action(CParserTable::aReduce, 18), CParserTable::Action(CParserTable::aReduce, 18), CParserTable::Action(CParserTable::aReduce, 18)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 5), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 5), CParserTable::Action(CParserTable::aReduce, 5), CParserTable::Action(CParserTable::aReduce, 5), CParserTable::Action(CParserTable::aReduce, 5)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 7), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 7), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 7), CParserTable::Action(CParserTable::aReduce, 7), CParserTable::Action(CParserTable::aReduce, 7), CParserTable::Action(CParserTable::aReduce, 7)}, 
   {CParserTable::Action(CParserTable::aShift, 25), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 26), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 10), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 10), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 10), CParserTable::Action(CParserTable::aReduce, 10), CParserTable::Action(CParserTable::aReduce, 10), CParserTable::Action(CParserTable::aReduce, 10)}, 
   {CParserTable::Action(CParserTable::aReduce, 11), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 11), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 27), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aReduce, 8), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 8), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 13)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 29), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 20), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 9), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 9), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 9), CParserTable::Action(CParserTable::aReduce, 9), CParserTable::Action(CParserTable::aReduce, 9), CParserTable::Action(CParserTable::aReduce, 9)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 30), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aReduce, 4), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 31), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aShift, 29), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 20), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aReduce, 12), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 12), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 15), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 15), CParserTable::Action(CParserTable::aReduce, 15), CParserTable::Action(CParserTable::aReduce, 15), CParserTable::Action(CParserTable::aReduce, 15)}, 
   {CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aReduce, 19), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0), CParserTable::Action(CParserTable::aError, 0)}
};

const int CParserTable::s_gotoTable[CParserTable::kStates][CParserTable::kNonterminals] = {
   {1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, 3, 4, 5, 6, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, 10, 11, -1}, 
   {-1, -1, -1, 16, 5, 6, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, 17, 18, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, 23, 11, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 28}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 32}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};


const int CParserTable::s_earlyReduce[CParserTable::kStates] = {
   3, 
   0, 
   -1, 
   -1, 
   -1, 
   -1, 
   -1, 
   -1, 
   -1, 
   2, 
   1, 
   -1, 
   -1, 
   16, 
   17, 
   18, 
   5, 
   7, 
   -1, 
   10, 
   11, 
   -1, 
   8, 
   13, 
   -1, 
   9, 
   -1, 
   4, 
   -1, 
   -1, 
   12, 
   15, 
   19
};


const char* CParserTable::s_tokenNames[CParserTable::kTerminals + CParserTable::kNonterminals] = {
      "tSemicolon",
      "tVariableName",
      "tAssign",
      "tLiteral",
      "tToken",
      "tTokenType",
      "tIdentifier",
      "tComma",
      "tProduction",
      "tResponse",
      "tLeft",
      "tRight",
      "tNone",
      "$",
      "program",
      "ntVariables",
      "ntAssignVariable",
      "ntTokenDefs",
      "ntTokenDef",
      "ntTokenType",
      "ntTokenNames",
      "ntTokenNameList",
      "ntRules",
      "ntRule",
      "ntRightSide"
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

const char* CParserTable::GetTokenName(CParserTable::TokenID id)
{
   assert(id >= 0 && id < kTerminals + kNonterminals);
   return s_tokenNames[id];
}

