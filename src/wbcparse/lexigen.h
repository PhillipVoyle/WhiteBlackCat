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

template <class T, class Table = CLexerTable>
class CLexer
   :public T
   ,public Table
{
   typedef typename Table::stateIDs stateIDs;
   stateIDs m_currentState;
   typedef typename T::lexiType lexiType;
   std::list<char> m_ungetBuffer;
public:
   template<typename...TArgs>
   CLexer(TArgs...args):T(args...)
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
{}
               break;
            case 1:
{setState(Table::stComment);}
               break;
            case 2:
{this->EOL();}
               break;
            case 3:
{this->m_parser.step(Token::CreateToken_VOID<CParserTable::tAssign>());}
               break;
            case 4:
{this->m_parser.step(Token::CreateToken_VOID<CParserTable::tSemicolon>());}
               break;
            case 5:
{setState(Table::stType); this->m_nDepth = 1; this->m_string = "";}
               break;
            case 6:
{this->m_parser.step(Token::CreateToken_VOID<CParserTable::tProduction>());}
               break;
            case 7:
{this->m_parser.step(Token::CreateToken_VOID<CParserTable::tComma>());}
               break;
            case 8:
{this->m_parser.step(Token::CreateToken_VOID<CParserTable::tToken>());}
               break;
            case 9:
{this->m_parser.step(Token::CreateToken_VOID<CParserTable::tLeft>());}
               break;
            case 10:
{this->m_parser.step(Token::CreateToken_VOID<CParserTable::tRight>());}
               break;
            case 11:
{this->m_parser.step(Token::CreateToken_VOID<CParserTable::tNone>());}
               break;
            case 12:
{this->m_parser.step(Token::CreateToken<CParserTable::tVariableName>(lexeme));}
               break;
            case 13:
{this->m_parser.step(Token::CreateToken<CParserTable::tLiteral>(lexeme));}
               break;
            case 14:
{setState(Table::stResponse); this->m_nDepth = 1; this->m_string = lexeme;}
               break;
            case 15:
{this->m_parser.step(Token::CreateToken<CParserTable::tIdentifier>(lexeme));}
               break;
            case 16:
{this->unrecognized(lexeme);}
               break;
            case 17:
{this->m_parser.step(Token::CreateToken_VOID<CParserTable::$>());}
               break;
            case 18:
{
						this->m_nDepth--;
						if(this->m_nDepth == 0)
						{
							setState(Table::stStart);
							this->m_parser.step(Token::CreateToken<CParserTable::tTokenType>(this->m_string));
						}
						else
						{
							this->m_string.append(lexeme);
						}
					}
               break;
            case 19:
{this->m_string.append(lexeme); this->m_nDepth++;}
               break;
            case 20:
{this->m_string.append(lexeme);}
               break;
            case 21:
{this->m_string.append(lexeme);}
               break;
            case 22:
{this->typeEOL(); this->m_string.append(lexeme);}
               break;
            case 23:
{this->typeEOF(); this->m_parser.step(Token::CreateToken_VOID<CParserTable::$>());}
               break;
            case 24:
{
						this->m_string.append(lexeme);
						this->m_nDepth--;
						if(this->m_nDepth == 0)
						{
							setState(Table::stStart);
							this->m_parser.step(Token::CreateToken<CParserTable::tResponse>(this->m_string));
						}
					}
               break;
            case 25:
{this->m_string.append(lexeme); this->m_nDepth++;}
               break;
            case 26:
{this->m_string.append(lexeme);}
               break;
            case 27:
{this->m_string.append(lexeme);}
               break;
            case 28:
{this->respEOL(); this->m_string.append(lexeme);}
               break;
            case 29:
{this->respEOF(); this->m_parser.step(Token::CreateToken_VOID<CParserTable::$>());}
               break;
            case 30:
{setState(Table::stStart);}
               break;
            case 31:
{}
               break;
            case 32:
{this->commentEOL();}
               break;
            case 33:
{this->commentEOF();}
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
