#pragma once

/*
   LRToken.h
   Typesafe LR Token Class. (c) Phillip Voyle 2005
   For use with Parsers Generated By ParserGenie.
   Files generated by ParserGenie will expect to find LRToken.h in the directory that they are
   compiled	in.
*/

#include <memory>
#include <assert.h>
#include <algorithm>

template<typename TCheck>
class MustBeVoid;

template<>
class MustBeVoid<void> {public: static void check(){}};

template<typename T, typename tc, typename sc>
class CLRTokenWithData;

template<typename T>
class CLRToken
{
	std::auto_ptr<CLRToken> m_next;
	int m_state;
	T m_tokenID;
protected:
	CLRToken(T tokenID):
		m_state(0),
		m_tokenID(tokenID)
	{
	}
public:
	typedef std::auto_ptr<CLRToken<T> > auto_ptr;

	void SetNext(auto_ptr ptr)
	{
		m_next = ptr;
	}
	auto_ptr& GetNext()
	{
		return m_next;
	}
	T GetTokenID()
	{
		return m_tokenID;
	}
	int GetState()
	{
		return m_state;
	}
	void SetState(int state)
	{
		m_state = state;
	}

  template<T t>
  class TokenType
  {
  public:
    typedef void transClass;
    typedef void storeClass;
  };
  
  template<T t>
  typename TokenType<t>::transClass GetData()
  {
    return static_cast<CLRTokenWithData<T, typename TokenType<t>::transClass, typename TokenType<t>::storeClass>*>(this)->GetData();
  }
  
  template<T t>
  static auto_ptr CreateToken(typename TokenType<t>::transClass c)
  {
    return auto_ptr(new CLRTokenWithData<T, typename TokenType<t>::transClass, typename TokenType<t>::storeClass>(t, c));
  }
  
	template<T t>
	static auto_ptr CreateToken_VOID()
	{
		MustBeVoid<typename TokenType<t>::storeClass>::check();
		MustBeVoid<typename TokenType<t>::transClass>::check();
		return auto_ptr(new CLRToken<T>(t));
    
	}
};

template<typename T, typename tc, typename sc>
class CLRTokenWithData: public CLRToken<T>
{
	typedef tc transClass;
	typedef sc storeClass;
	storeClass m_s;
public:
	CLRTokenWithData(T tokenID, transClass t)
		: CLRToken<T>(tokenID)
		, m_s(t)
	{
	}
	transClass GetData()
	{
		return m_s;
	}
};

