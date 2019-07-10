#pragma once

/*
   parser.h, generated by ParserGenie (c) Phillip Voyle 2005.
*/

#include "LRToken.h"
#include "parserTable.h"
#include <assert.h>

/*
   Type Definitions:
   ParserGenie generates type defining classes for each
*/
template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tVariableName>
{
public:
   typedef std::string storeClass;
   typedef std::string transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tAssign>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tLiteral>
{
public:
   typedef std::string storeClass;
   typedef std::string transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tIdentifier>
{
public:
   typedef std::string storeClass;
   typedef std::string transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tBeginRegexp>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tFinishedRegexp>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tState>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tOn>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tResponse>
{
public:
   typedef std::string storeClass;
   typedef std::string transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tEOF>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tOr>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tPlus>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tStar>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tQMark>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tRegexp>
{
public:
   typedef regularExpressionPtr storeClass;
   typedef regularExpressionPtr transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tOpen>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tClose>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::$>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntProgram>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntRegexp>
{
public:
   typedef regularExpressionPtr storeClass;
   typedef regularExpressionPtr transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntAssignVariables>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntAssignDefinitions>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntInitStates>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntStateAssignment>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntInitOneState>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntEvents>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntEvent>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template <class TBase>
class CParser
   :public TBase
{
public:
   typedef CParserTable::TokenID TokenID;
   typedef CLRToken<CParserTable::TokenID> Token;
   typedef Token::auto_ptr TokenPtr;
private:
   typedef CParserTable::ActionID ActionID;
   TokenPtr m_stack;
public:
   template<typename...TArgs>
   CParser(TArgs...args):TBase(args...)
   {
      init();
   }
   bool reduce(int nReduce)
   {
      TokenPtr reduced;
      int nextState = -1;
      switch(nReduce)
      {
      case 0:
      {
         this->Accept();
         m_stack = TokenPtr();
         return false;
      }
      case 1:
      {
         m_stack = m_stack->GetNext();//pop ntInitStates
         m_stack = m_stack->GetNext();//pop ntAssignDefinitions
         m_stack = m_stack->GetNext();//pop ntAssignVariables
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntProgram);
         reduced = Token::CreateToken_VOID<CParserTable::ntProgram>();
         }
         break;
      case 2:
      {
         regularExpressionPtr $$;
{$$ = this->regNil();}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRegexp);
         reduced = Token::CreateToken<CParserTable::ntRegexp>($$);
         }
         break;
      case 3:
      {
         std::string $4 = m_stack->GetData<CParserTable::tLiteral>();
         m_stack = m_stack->GetNext();//pop tLiteral
         m_stack = m_stack->GetNext();//pop tAssign
         std::string $2 = m_stack->GetData<CParserTable::tVariableName>();
         m_stack = m_stack->GetNext();//pop tVariableName
         m_stack = m_stack->GetNext();//pop ntAssignVariables
{this->assignVar($2, $4);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntAssignVariables);
         reduced = Token::CreateToken_VOID<CParserTable::ntAssignVariables>();
         }
         break;
      case 4:
      {
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntAssignVariables);
         reduced = Token::CreateToken_VOID<CParserTable::ntAssignVariables>();
         }
         break;
      case 5:
      {
         m_stack = m_stack->GetNext();//pop tFinishedRegexp
         regularExpressionPtr $5 = m_stack->GetData<CParserTable::ntRegexp>();
         m_stack = m_stack->GetNext();//pop ntRegexp
         m_stack = m_stack->GetNext();//pop tBeginRegexp
         m_stack = m_stack->GetNext();//pop tAssign
         std::string $2 = m_stack->GetData<CParserTable::tIdentifier>();
         m_stack = m_stack->GetNext();//pop tIdentifier
         m_stack = m_stack->GetNext();//pop ntAssignDefinitions
{this->assignDef($2, $5);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntAssignDefinitions);
         reduced = Token::CreateToken_VOID<CParserTable::ntAssignDefinitions>();
         }
         break;
      case 6:
      {
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntAssignDefinitions);
         reduced = Token::CreateToken_VOID<CParserTable::ntAssignDefinitions>();
         }
         break;
      case 7:
      {
         m_stack = m_stack->GetNext();//pop ntInitOneState
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntInitStates);
         reduced = Token::CreateToken_VOID<CParserTable::ntInitStates>();
         }
         break;
      case 8:
      {
         m_stack = m_stack->GetNext();//pop ntInitOneState
         m_stack = m_stack->GetNext();//pop ntStateAssignment
         m_stack = m_stack->GetNext();//pop ntInitStates
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntInitStates);
         reduced = Token::CreateToken_VOID<CParserTable::ntInitStates>();
         }
         break;
      case 9:
      {
         std::string $3 = m_stack->GetData<CParserTable::tLiteral>();
         m_stack = m_stack->GetNext();//pop tLiteral
         m_stack = m_stack->GetNext();//pop tAssign
         m_stack = m_stack->GetNext();//pop tState
{this->setState($3);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntStateAssignment);
         reduced = Token::CreateToken_VOID<CParserTable::ntStateAssignment>();
         }
         break;
      case 10:
      {
         m_stack = m_stack->GetNext();//pop ntEvents
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntInitOneState);
         reduced = Token::CreateToken_VOID<CParserTable::ntInitOneState>();
         }
         break;
      case 11:
      {
         m_stack = m_stack->GetNext();//pop ntEvent
         m_stack = m_stack->GetNext();//pop ntEvents
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntEvents);
         reduced = Token::CreateToken_VOID<CParserTable::ntEvents>();
         }
         break;
      case 12:
      {
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntEvents);
         reduced = Token::CreateToken_VOID<CParserTable::ntEvents>();
         }
         break;
      case 13:
      {
         std::string $5 = m_stack->GetData<CParserTable::tResponse>();
         m_stack = m_stack->GetNext();//pop tResponse
         m_stack = m_stack->GetNext();//pop tFinishedRegexp
         regularExpressionPtr $3 = m_stack->GetData<CParserTable::ntRegexp>();
         m_stack = m_stack->GetNext();//pop ntRegexp
         m_stack = m_stack->GetNext();//pop tBeginRegexp
         m_stack = m_stack->GetNext();//pop tOn
{this->addEvent($3, $5);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntEvent);
         reduced = Token::CreateToken_VOID<CParserTable::ntEvent>();
         }
         break;
      case 14:
      {
         std::string $3 = m_stack->GetData<CParserTable::tResponse>();
         m_stack = m_stack->GetNext();//pop tResponse
         m_stack = m_stack->GetNext();//pop tEOF
         m_stack = m_stack->GetNext();//pop tOn
{this->addEOFEvent($3);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntEvent);
         reduced = Token::CreateToken_VOID<CParserTable::ntEvent>();
         }
         break;
      case 15:
      {
         regularExpressionPtr $$;
         regularExpressionPtr $3 = m_stack->GetData<CParserTable::ntRegexp>();
         m_stack = m_stack->GetNext();//pop ntRegexp
         m_stack = m_stack->GetNext();//pop tOr
         regularExpressionPtr $1 = m_stack->GetData<CParserTable::ntRegexp>();
         m_stack = m_stack->GetNext();//pop ntRegexp
{$$ = this->regOr($1, $3);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRegexp);
         reduced = Token::CreateToken<CParserTable::ntRegexp>($$);
         }
         break;
      case 16:
      {
         regularExpressionPtr $$;
         regularExpressionPtr $2 = m_stack->GetData<CParserTable::ntRegexp>();
         m_stack = m_stack->GetNext();//pop ntRegexp
         regularExpressionPtr $1 = m_stack->GetData<CParserTable::ntRegexp>();
         m_stack = m_stack->GetNext();//pop ntRegexp
{$$ = this->regCat($1, $2);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRegexp);
         reduced = Token::CreateToken<CParserTable::ntRegexp>($$);
         }
         break;
      case 17:
      {
         regularExpressionPtr $$;
         m_stack = m_stack->GetNext();//pop tPlus
         regularExpressionPtr $1 = m_stack->GetData<CParserTable::ntRegexp>();
         m_stack = m_stack->GetNext();//pop ntRegexp
{$$ = this->regPlus($1);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRegexp);
         reduced = Token::CreateToken<CParserTable::ntRegexp>($$);
         }
         break;
      case 18:
      {
         regularExpressionPtr $$;
         m_stack = m_stack->GetNext();//pop tStar
         regularExpressionPtr $1 = m_stack->GetData<CParserTable::ntRegexp>();
         m_stack = m_stack->GetNext();//pop ntRegexp
{$$ = this->regStar($1);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRegexp);
         reduced = Token::CreateToken<CParserTable::ntRegexp>($$);
         }
         break;
      case 19:
      {
         regularExpressionPtr $$;
         m_stack = m_stack->GetNext();//pop tQMark
         regularExpressionPtr $1 = m_stack->GetData<CParserTable::ntRegexp>();
         m_stack = m_stack->GetNext();//pop ntRegexp
{$$ = this->regQMark($1);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRegexp);
         reduced = Token::CreateToken<CParserTable::ntRegexp>($$);
         }
         break;
      case 20:
      {
         regularExpressionPtr $$;
         regularExpressionPtr $1 = m_stack->GetData<CParserTable::tRegexp>();
         m_stack = m_stack->GetNext();//pop tRegexp
{$$ = $1;}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRegexp);
         reduced = Token::CreateToken<CParserTable::ntRegexp>($$);
         }
         break;
      case 21:
      {
         regularExpressionPtr $$;
         m_stack = m_stack->GetNext();//pop tClose
         regularExpressionPtr $2 = m_stack->GetData<CParserTable::ntRegexp>();
         m_stack = m_stack->GetNext();//pop ntRegexp
         m_stack = m_stack->GetNext();//pop tOpen
{ $$ = $2;}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRegexp);
         reduced = Token::CreateToken<CParserTable::ntRegexp>($$);
         }
         break;
      default:
         return false;
      }
      if(nextState == -1)
      {
         this->ParserError(reduced);
      }
      else
      {
         reduced->SetState(nextState);
         reduced->SetNext(m_stack);
         m_stack = reduced;
      }
      return true;
   }
   void perform_early_reductions()
   {
     int nEarlyReduce = 0;
     do
     {
        nEarlyReduce = CParserTable::GetEarlyReduce(m_stack->GetState());
        if(nEarlyReduce < 1)
        {
           return;
        }
      }while(reduce(nEarlyReduce));
   }

   void init()
   {
      m_stack = Token::CreateToken_VOID<CParserTable::$>(); //init stack with state 0.
      m_stack->SetState(0);
   }
   void step(TokenPtr ptr)
   {
      const TokenID token = ptr->GetTokenID();
      for(;;)
      {
         const CParserTable::Action action = CParserTable::GetAction(m_stack->GetState(), token);
         switch(action.first)
         {
         case CParserTable::aShift:
            ptr->SetNext(m_stack);
            ptr->SetState(action.second);
            m_stack = ptr;
            perform_early_reductions();
            return;
         case CParserTable::aReduce:
            {
               if(!reduce(action.second))
               {
                  return;
               }
            }
            break;
         case CParserTable::aError:
         default:
            this->ParserError(ptr);
            return;
         }
      }
   }
};

