#pragma once
#include <string>
#include <memory>

class IToken
{
	friend class std::shared_ptr<IToken>;
protected:
	virtual ~IToken() {}
	IToken() {};
public:
	static std::shared_ptr<IToken> Create(const std::string& name);
	virtual const std::string& GetName() = 0;

	virtual void SetID(unsigned) = 0;
	virtual unsigned GetID(void) = 0;
};

class ITokenList
{
	friend class std::shared_ptr<ITokenList>;
protected:
	virtual ~ITokenList() {}
	ITokenList() {};
public:
	static std::shared_ptr<ITokenList> Create(std::shared_ptr<IToken>& token, std::shared_ptr<ITokenList>& tokenList);
	virtual std::shared_ptr<IToken> GetToken() = 0;
	virtual std::shared_ptr<ITokenList> GetTokenList() = 0;

	virtual void SetIsTerminal(bool) = 0;
	virtual bool GetIsTerminal(void) = 0;
};

class IProduction
{
	friend class std::shared_ptr<IProduction>;
protected:
	virtual ~IProduction() {}
	IProduction() {};
public:
	static std::shared_ptr<IProduction> Create(std::shared_ptr<IToken> left, std::shared_ptr<ITokenList> right, const std::string& response);
	virtual std::shared_ptr<IToken> GetLeft() = 0;
	virtual std::shared_ptr<ITokenList> GetRight() = 0;
	virtual const std::string& GetResponse() = 0;
	virtual void SetID(unsigned id) = 0;
	virtual unsigned GetID(void) = 0;

	virtual void SetPrecedence(int precedence) = 0;
	virtual int GetPrecedence() = 0;

	enum Associativity
	{
		asNone,
		asLeft,
		asRight
	};

	virtual void SetAssociativity(Associativity associativity) = 0;
	virtual Associativity GetAssociativity() = 0;
};

class IProductions
{
	friend class std::shared_ptr<IProductions>;
protected:
	virtual ~IProductions() {};
	IProductions() {};
public:
	static std::shared_ptr<IProductions> Create(std::shared_ptr<IProduction>& production, std::shared_ptr<IProductions>& productions);
	virtual std::shared_ptr<IProduction> GetProduction() = 0;
	virtual std::shared_ptr<IProductions> GetProductions() = 0;
	virtual void SetProductions(std::shared_ptr<IProductions> productions) = 0;
};
