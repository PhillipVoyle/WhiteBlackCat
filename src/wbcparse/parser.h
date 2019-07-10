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
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tSemicolon>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

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
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tToken>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tTokenType>
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
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tComma>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tProduction>
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
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tLeft>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tRight>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::tNone>
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
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::program>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntVariables>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntAssignVariable>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntTokenDefs>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntTokenDef>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntTokenType>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntTokenNames>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntTokenNameList>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntRules>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntRule>
{
public:
   typedef void storeClass;
   typedef void transClass;
};

template<>
template<>
class CLRToken<CParserTable::TokenID>::TokenType<CParserTable::ntRightSide>
{
public:
   typedef syntax_string_list_t storeClass;
   typedef syntax_string_list_t transClass;
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
         m_stack = m_stack->GetNext();//pop ntRules
         m_stack = m_stack->GetNext();//pop ntTokenDefs
         m_stack = m_stack->GetNext();//pop ntVariables
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::program);
         reduced = Token::CreateToken_VOID<CParserTable::program>();
         }
         break;
      case 2:
      {
         m_stack = m_stack->GetNext();//pop tSemicolon
         m_stack = m_stack->GetNext();//pop ntAssignVariable
         m_stack = m_stack->GetNext();//pop ntVariables
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntVariables);
         reduced = Token::CreateToken_VOID<CParserTable::ntVariables>();
         }
         break;
      case 3:
      {
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntVariables);
         reduced = Token::CreateToken_VOID<CParserTable::ntVariables>();
         }
         break;
      case 4:
      {
         std::string $3 = m_stack->GetData<CParserTable::tLiteral>();
         m_stack = m_stack->GetNext();//pop tLiteral
         m_stack = m_stack->GetNext();//pop tAssign
         std::string $1 = m_stack->GetData<CParserTable::tVariableName>();
         m_stack = m_stack->GetNext();//pop tVariableName
{this->assignVariable($1, $3);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntAssignVariable);
         reduced = Token::CreateToken_VOID<CParserTable::ntAssignVariable>();
         }
         break;
      case 5:
      {
         m_stack = m_stack->GetNext();//pop ntTokenDefs
         m_stack = m_stack->GetNext();//pop ntTokenDef
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntTokenDefs);
         reduced = Token::CreateToken_VOID<CParserTable::ntTokenDefs>();
         }
         break;
      case 6:
      {
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntTokenDefs);
         reduced = Token::CreateToken_VOID<CParserTable::ntTokenDefs>();
         }
         break;
      case 7:
      {
         m_stack = m_stack->GetNext();//pop ntTokenNames
         m_stack = m_stack->GetNext();//pop ntTokenType
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntTokenDef);
         reduced = Token::CreateToken_VOID<CParserTable::ntTokenDef>();
         }
         break;
      case 8:
      {
         std::string $2 = m_stack->GetData<CParserTable::tTokenType>();
         m_stack = m_stack->GetNext();//pop tTokenType
         m_stack = m_stack->GetNext();//pop tToken
{this->setTokenType($2);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntTokenType);
         reduced = Token::CreateToken_VOID<CParserTable::ntTokenType>();
         }
         break;
      case 9:
      {
         m_stack = m_stack->GetNext();//pop tSemicolon
         m_stack = m_stack->GetNext();//pop ntTokenNameList
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntTokenNames);
         reduced = Token::CreateToken_VOID<CParserTable::ntTokenNames>();
         }
         break;
      case 10:
      {
         m_stack = m_stack->GetNext();//pop tSemicolon
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntTokenNames);
         reduced = Token::CreateToken_VOID<CParserTable::ntTokenNames>();
         }
         break;
      case 11:
      {
         std::string $1 = m_stack->GetData<CParserTable::tIdentifier>();
         m_stack = m_stack->GetNext();//pop tIdentifier
{this->addToken($1);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntTokenNameList);
         reduced = Token::CreateToken_VOID<CParserTable::ntTokenNameList>();
         }
         break;
      case 12:
      {
         std::string $3 = m_stack->GetData<CParserTable::tIdentifier>();
         m_stack = m_stack->GetNext();//pop tIdentifier
         m_stack = m_stack->GetNext();//pop tComma
         m_stack = m_stack->GetNext();//pop ntTokenNameList
{this->addToken($3);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntTokenNameList);
         reduced = Token::CreateToken_VOID<CParserTable::ntTokenNameList>();
         }
         break;
      case 13:
      {
         m_stack = m_stack->GetNext();//pop ntRules
         m_stack = m_stack->GetNext();//pop ntRule
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRules);
         reduced = Token::CreateToken_VOID<CParserTable::ntRules>();
         }
         break;
      case 14:
      {
{}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRules);
         reduced = Token::CreateToken_VOID<CParserTable::ntRules>();
         }
         break;
      case 15:
      {
         std::string $4 = m_stack->GetData<CParserTable::tResponse>();
         m_stack = m_stack->GetNext();//pop tResponse
         syntax_string_list_t $3 = m_stack->GetData<CParserTable::ntRightSide>();
         m_stack = m_stack->GetNext();//pop ntRightSide
         m_stack = m_stack->GetNext();//pop tProduction
         std::string $1 = m_stack->GetData<CParserTable::tIdentifier>();
         m_stack = m_stack->GetNext();//pop tIdentifier
{this->addRule($1, $3, $4);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRule);
         reduced = Token::CreateToken_VOID<CParserTable::ntRule>();
         }
         break;
      case 16:
      {
         m_stack = m_stack->GetNext();//pop tLeft
{this->setAssocLeft();}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRule);
         reduced = Token::CreateToken_VOID<CParserTable::ntRule>();
         }
         break;
      case 17:
      {
         m_stack = m_stack->GetNext();//pop tRight
{this->setAssocRight();}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRule);
         reduced = Token::CreateToken_VOID<CParserTable::ntRule>();
         }
         break;
      case 18:
      {
         m_stack = m_stack->GetNext();//pop tNone
{this->setAssocNone();}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRule);
         reduced = Token::CreateToken_VOID<CParserTable::ntRule>();
         }
         break;
      case 19:
      {
         syntax_string_list_t $$;
         syntax_string_list_t $2 = m_stack->GetData<CParserTable::ntRightSide>();
         m_stack = m_stack->GetNext();//pop ntRightSide
         std::string $1 = m_stack->GetData<CParserTable::tIdentifier>();
         m_stack = m_stack->GetNext();//pop tIdentifier
{$$ = this->addSyntaxStringToList($1, $2);}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRightSide);
         reduced = Token::CreateToken<CParserTable::ntRightSide>($$);
         }
         break;
      case 20:
      {
         syntax_string_list_t $$;
{$$ = this->syntaxStringList();}
         nextState = CParserTable::GetGoto(m_stack->GetState(), CParserTable::ntRightSide);
         reduced = Token::CreateToken<CParserTable::ntRightSide>($$);
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

