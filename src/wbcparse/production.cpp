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

std::shared_ptr<IToken> IToken::Create(const std::string& identifier)
{
	return std::make_shared<CToken>(identifier);
}

class CTokenList:public ITokenList
{
	std::shared_ptr<IToken> m_token;
	std::shared_ptr<ITokenList> m_tokenList;
	bool m_isTerminal;
public:
	CTokenList(std::shared_ptr<IToken>& token, std::shared_ptr<ITokenList>& tokenList):
	  m_token(token),
	  m_tokenList(tokenList),
	  m_isTerminal(true)
	{
	}

	std::shared_ptr<IToken> GetToken()
	{
		return m_token;
	}

	std::shared_ptr<ITokenList> GetTokenList()
	{
		return m_tokenList;
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

std::shared_ptr<ITokenList> ITokenList::Create(std::shared_ptr<IToken>& token, std::shared_ptr<ITokenList>& tokenList)
{
	return std::make_shared<CTokenList>(token, tokenList);
}

class CProduction:public IProduction
{
	std::shared_ptr<IToken> m_left;
	std::shared_ptr<ITokenList> m_right;
	std::string m_response;
	unsigned m_id;
	int m_precedence;
	Associativity m_associativity;
	int m_orderID;
public:
	CProduction(std::shared_ptr<IToken>& left, std::shared_ptr<ITokenList>& right, const std::string& response):
		m_left(left),
		m_right(right),
		m_response(response)
	{
		m_precedence = 0;
		m_associativity = asNone;
		m_orderID = -1;
	}

	std::shared_ptr<IToken> GetLeft()
	{
		return m_left;
	}

	std::shared_ptr<ITokenList> GetRight()
	{
		return m_right;
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

std::shared_ptr<IProduction> IProduction::Create(std::shared_ptr<IToken> left, std::shared_ptr<ITokenList> right, const std::string& response)
{
	return std::make_shared<CProduction>(left, right, response);
}

class CProductions:public IProductions
{
	std::shared_ptr<IProduction> m_production;
	std::shared_ptr<IProductions> m_productions;
public:
	CProductions(std::shared_ptr<IProduction> &production, std::shared_ptr<IProductions>& productions):
		m_production(production),
		m_productions(productions)
	{
	}

	std::shared_ptr<IProduction> GetProduction()
	{
		return m_production;
	}

	std::shared_ptr<IProductions> GetProductions()
	{
		return m_productions;
	}
	void SetProductions(std::shared_ptr<IProductions> productions)
	{
		m_productions = productions;
	}
};

std::shared_ptr<IProductions> IProductions::Create(std::shared_ptr<IProduction> &production, std::shared_ptr<IProductions>& productions)
{
	return std::make_shared<CProductions>(production, productions);
}