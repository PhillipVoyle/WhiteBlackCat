#pragma once

#include <memory>
#include <string>
#include <assert.h>
#include <vector>

class CRegularExpression
{
public:
	typedef std::auto_ptr<CRegularExpression> auto_ptr;

	enum typeID {charNode, starNode, catNode, orNode, endNode, errorNode};
	typeID m_typeID;
	auto_ptr m_a;
	auto_ptr m_b;
	char m_c;
	unsigned m_endID;
	CRegularExpression(){m_typeID = errorNode;}
	bool m_bNullable;
	int m_positionID;
	std::vector<int> m_firstPos;
	std::vector<int> m_lastPos;

	static auto_ptr CreateEndNode(unsigned endID)
	{
		auto_ptr newExp(new CRegularExpression());
		newExp->m_typeID = endNode;
		newExp->m_endID = endID;
		return newExp;
	}
	static auto_ptr CreateCharNode(char c)
	{
		auto_ptr newExp(new CRegularExpression());
		newExp->m_typeID = charNode;
		newExp->m_c = c;
		return newExp;
	}
	static auto_ptr CreateStarNode(auto_ptr& a)
	{
		auto_ptr newExp(new CRegularExpression());
		newExp->m_typeID = starNode;
		newExp->m_a = a;
		return newExp;
	}
	static auto_ptr CreateCatNode(auto_ptr& a, auto_ptr& b)
	{
		auto_ptr newExp(new CRegularExpression());
		newExp->m_typeID = catNode;
		newExp->m_a = a;
		newExp->m_b = b;
		return newExp;
	}
	static auto_ptr CreateOrNode(auto_ptr& a, auto_ptr& b)
	{
		auto_ptr newExp(new CRegularExpression());
		newExp->m_typeID = orNode;
		newExp->m_a = a;
		newExp->m_b = b;
		return newExp;
	}
	static auto_ptr CreatePlusNode(auto_ptr& a)
	{
		if(a.get() == NULL)
		{
			return auto_ptr();
		}
		else
		{
			auto_ptr clone = a->clone();
			auto_ptr starNode = CreateStarNode(a);
			return CreateCatNode(clone, starNode);
		}
	}
	static auto_ptr CreateQMarkNode(auto_ptr& a)
	{
		if(a.get() == NULL)
		{
			return auto_ptr();
		}
    auto_ptr aptr;
		return CreateOrNode(aptr, a);
	}
	typeID GetTypeID(){return m_typeID;}
	CRegularExpression* GetA() {return m_a.get();}
	CRegularExpression* GetB() {return m_b.get();}
	char GetC(){return m_c;}
	unsigned GetEnd(){return m_endID;}
	void SetID(int positionID){m_positionID = positionID;}
	int GetID(){return m_positionID;}

	void SetNullable(bool bNullable) {m_bNullable = bNullable;}
	bool GetNullable() {return m_bNullable;}

	void SetFirstPos(const std::vector<int>& firstPos)
	{
		m_firstPos = firstPos;
	}

	std::vector<int>& GetFirstPos()
	{
		return m_firstPos;
	}

	void SetLastPos(const std::vector<int>& lastPos)
	{
		m_lastPos = lastPos;
	}

	std::vector<int>& GetLastPos()
	{
		return m_lastPos;
	}

	auto_ptr clone()
	{
		auto_ptr newExp(new CRegularExpression());
		newExp->m_typeID = m_typeID;
		if(GetA() != NULL)
		{
			newExp->m_a = m_a->clone();
		}
		if(GetB() != NULL)
		{
			newExp->m_b = m_b->clone();
		}
		newExp->m_c = m_c;
		newExp->m_endID = m_endID;

		return newExp;
	}
};

typedef std::auto_ptr<CRegularExpression> regularExpressionPtr;
