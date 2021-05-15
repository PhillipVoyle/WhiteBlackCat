/*
    lexigen.h
    Generated by wbclex Scanner Generator (C) Phillip Voyle 2011 - 2021
*/

#pragma once
#include <list>
#include <iostream>
#include <assert.h>
#include <utility>

#include "lexigen_table.h"

template <class T, class Table = CLexigenTable>
class CLexigen
   :public T
   ,public Table
{
   typedef typename Table::stateIDs stateIDs;
   stateIDs m_currentState;
   typedef typename T::lexiType lexiType;
   std::list<char> m_ungetBuffer;
public:
   template<typename...TArgs>
   CLexigen(TArgs...args):T(args...)
   {
       init();
   }
   void init()
   {
       m_currentState = Table::stStart;
       flush();
   }

   void flush()
   {
      m_ungetBuffer.clear();
   }

   void setState(stateIDs state)
   {
      m_currentState = state;
   }
   lexiType scan(std::istream& _inStream)
   {
      std::string lexeme;
      std::string sbuffer;
      int stateid = 0;
      int announce = -1;
      
      for(;;)
      {
         int newAnnounce = this->GetAnnounce(m_currentState, stateid);
         bool earlyAnnounce = false;
         char c = '\0';
         if(newAnnounce != -1)
         {
            lexeme = sbuffer;
            announce = newAnnounce;
         }
         
         if (this->CanEarlyAnnounce(m_currentState, stateid)) {
            stateid = -1;
            earlyAnnounce = true;
         } else {
            if(m_ungetBuffer.size() > 0)
            {
               c = m_ungetBuffer.front();
               m_ungetBuffer.pop_front();
            }
            else
            {
               for(;;)
               {
                  _inStream.get(c);
                  if(_inStream.eof())
                  {
                     c = EOF;
                  }
                  else if(c < 0)
                  {
                     _inStream.get(c);
                     continue;
                  }
                  break;
               }
            }
            
            if(c == EOF)
            {
               stateid = -1;
            }
            else
            {
               assert(c >= 0);
               assert(c < 128);
               stateid = this->GetTransition(m_currentState, stateid, c);
            }
            sbuffer.append(1, c);
         }
         if(stateid == -1)
         {
            bool bQuit = false;
            if(!earlyAnnounce && (sbuffer.size() == 1) && c == EOF)
            {
               bQuit = true;
               announce = this->GetAnnounceOnEOF(m_currentState);
            }
            
            int id;
            for(id = (int)sbuffer.size() - 1; id >= (int)lexeme.size(); id--)
            {
               m_ungetBuffer.push_front(sbuffer[id]);
            }
            sbuffer = "";
            stateid = 0;
            switch(announce)
            {
            case 0:
{ this->numberToken(lexeme); }
               break;
            case 1:
{ this->add(); }
               break;
            case 2:
{ this->sub(); }
               break;
            case 3:
{ this->mul(); }
               break;
            case 4:
{ this->div(); }
               break;
            case 5:
{ this->left_parenthesis(); }
               break;
            case 6:
{ this->right_parenthesis(); }
               break;
            case 7:
{ this->endline(); }
               break;
            case 8:
{ this->whitespace(); }
               break;
            case 9:
{this->eof(); }
               break;
            case 10:
{this->unexpected(lexeme);}
               break;
            default:
               return EOF;
            }
            announce = -1;
            lexeme = "";
            if(bQuit)
            {
               return EOF;
            }
         }
      }
   }
};