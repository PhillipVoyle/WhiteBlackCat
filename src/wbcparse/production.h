#pragma once
#include <string>
#include <memory>

class IToken
{
	friend class std::auto_ptr<IToken>; //auto_ptr is in sole responsibility for memory management
protected:
	virtual ~IToken() {}
	IToken() {};
public:
	static std::auto_ptr<IToken> Create(const std::string& name);
	virtual const std::string& GetName() = 0;

	virtual void SetID(unsigned) = 0;
	virtual unsigned GetID(void) = 0;
};

class ITokenList
{
	friend class std::auto_ptr<ITokenList>;
protected:
	virtual ~ITokenList() {}
	ITokenList() {};
public:
	static std::auto_ptr<ITokenList> Create(std::auto_ptr<IToken>& token, std::auto_ptr<ITokenList>& tokenList);
	virtual IToken* GetToken() = 0;
	virtual ITokenList* GetTokenList() = 0;

	virtual void SetIsTerminal(bool) = 0;
	virtual bool GetIsTerminal(void) = 0;
};

class IProduction
{
	friend class std::auto_ptr<IProduction>;
protected:
	virtual ~IProduction() {}
	IProduction() {};
public:
	static std::auto_ptr<IProduction> Create(std::auto_ptr<IToken> left, std::auto_ptr<ITokenList> right, const std::string& response);
	virtual IToken* GetLeft() = 0;
	virtual ITokenList* GetRight() = 0;
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
	friend class std::auto_ptr<IProductions>;
protected:
	virtual ~IProductions() {};
	IProductions() {};
public:
	static std::auto_ptr<IProductions> Create(std::auto_ptr<IProduction>& production, std::auto_ptr<IProductions>& productions);
	virtual IProduction* GetProduction() = 0;
	virtual IProductions* GetProductions() = 0;
	virtual void SetProductions(std::auto_ptr<IProductions>& productions) = 0;
};
