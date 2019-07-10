#include "production.h"

class CToken:public IToken
{
	std::string m_identifier;
	unsigned m_id;
public:
	CToken(const std::string& identifier):
	  m_identifier(identifier),
	  m_id(0)
	{
	}
	const std::string& GetName()
	{
		return m_identifier;
	}

	void SetID(unsigned id)
	{
		m_id = id;
	}

	unsigned GetID(void)
	{
		return m_id;
	}
};

std::auto_ptr<IToken> IToken::Create(const std::string& identifier)
{
	return std::auto_ptr<IToken>(new CToken(identifier));
}

class CTokenList:public ITokenList
{
	std::auto_ptr<IToken> m_token;
	std::auto_ptr<ITokenList> m_tokenList;
	bool m_isTerminal;
public:
	CTokenList(std::auto_ptr<IToken>& token, std::auto_ptr<ITokenList>& tokenList):
	  m_token(token),
	  m_tokenList(tokenList),
	  m_isTerminal(true)
	{
	}

	IToken* GetToken()
	{
		return m_token.get();
	}

	ITokenList* GetTokenList()
	{
		return m_tokenList.get();
	}

	void SetIsTerminal(bool isTerminal)
	{
        m_isTerminal = isTerminal;
	}

	bool GetIsTerminal(void)
	{
		return m_isTerminal;
	}
};

std::auto_ptr<ITokenList> ITokenList::Create(std::auto_ptr<IToken>& token, std::auto_ptr<ITokenList>& tokenList)
{
	return std::auto_ptr<ITokenList>(new CTokenList(token, tokenList));
}

class CProduction:public IProduction
{
	std::auto_ptr<IToken> m_left;
	std::auto_ptr<ITokenList> m_right;
	std::string m_response;
	unsigned m_id;
	int m_precedence;
	Associativity m_associativity;
	int m_orderID;
public:
	CProduction(std::auto_ptr<IToken>& left, std::auto_ptr<ITokenList>& right, const std::string& response):
		m_left(left),
		m_right(right),
		m_response(response)
	{
		m_precedence = 0;
		m_associativity = asNone;
		m_orderID = -1;
	}

	IToken* GetLeft()
	{
		return m_left.get();
	}

	ITokenList* GetRight()
	{
		return m_right.get();
	}

	const std::string& GetResponse()
	{
		return m_response;
	}

	void SetID(unsigned id)
	{
		m_id = id;
	}

	unsigned GetID()
	{
		return m_id;
	}

	void SetPrecedence(int precedence)
	{
		m_precedence = precedence;
	}

	int GetPrecedence()
	{
		return m_precedence;
	}

	void SetAssociativity(Associativity associativity)
	{
		m_associativity = associativity;
	}
	
	Associativity GetAssociativity()
	{
		return m_associativity;
	}

	void SetOrderID(int id)
	{
		m_orderID = id;
	}

	int GetOrderID()
	{
		return m_orderID;
	}
};

std::auto_ptr<IProduction> IProduction::Create(std::auto_ptr<IToken> left, std::auto_ptr<ITokenList> right, const std::string& response)
{
	return std::auto_ptr<IProduction>(new CProduction(left, right, response));
}

class CProductions:public IProductions
{
	std::auto_ptr<IProduction> m_production;
	std::auto_ptr<IProductions> m_productions;
public:
	CProductions(std::auto_ptr<IProduction> &production, std::auto_ptr<IProductions>& productions):
		m_production(production),
		m_productions(productions)
	{
	}

	IProduction* GetProduction()
	{
		return m_production.get();
	}

	IProductions* GetProductions()
	{
		return m_productions.get();
	}
	void SetProductions(std::auto_ptr<IProductions>& productions)
	{
		m_productions = productions;
	}
};

std::auto_ptr<IProductions> IProductions::Create(std::auto_ptr<IProduction> &production, std::auto_ptr<IProductions>& productions)
{
	return std::auto_ptr<IProductions>(new CProductions(production, productions));
}