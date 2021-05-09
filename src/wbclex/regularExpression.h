#pragma once

#include <memory>
#include <string>
#include <assert.h>
#include <vector>

class CRegularExpression
{
public:
	typedef std::shared_ptr<CRegularExpression> ExpressionPtr;

	enum typeID {charNode, starNode, catNode, orNode, endNode, errorNode};
	typeID m_typeID;
	ExpressionPtr m_a;
	ExpressionPtr m_b;
	char m_c;
	unsigned m_endID;
	CRegularExpression(){m_typeID = errorNode;}
	bool m_bnullable;
	int m_positionID;
	std::vector<int> m_firstPos;
	std::vector<int> m_lastPos;

	static ExpressionPtr CreateEndNode(unsigned endID)
	{
		ExpressionPtr newExp = std::make_shared<CRegularExpression>();
		newExp->m_typeID = endNode;
		newExp->m_endID = endID;
		return newExp;
	}
	static ExpressionPtr CreateCharNode(char c)
	{
		ExpressionPtr newExp = std::make_shared<CRegularExpression>();
		newExp->m_typeID = charNode;
		newExp->m_c = c;
		return newExp;
	}
	static ExpressionPtr CreateStarNode(ExpressionPtr& a)
	{
		ExpressionPtr newExp = std::make_shared<CRegularExpression>();
		newExp->m_typeID = starNode;
		newExp->m_a = a;
		return newExp;
	}
	static ExpressionPtr CreateCatNode(ExpressionPtr& a, ExpressionPtr& b)
	{
		ExpressionPtr newExp = std::make_shared<CRegularExpression>();
		newExp->m_typeID = catNode;
		newExp->m_a = a;
		newExp->m_b = b;
		return newExp;
	}
	static ExpressionPtr CreateOrNode(ExpressionPtr& a, ExpressionPtr& b)
	{
		ExpressionPtr newExp = std::make_shared<CRegularExpression>();
		newExp->m_typeID = orNode;
		newExp->m_a = a;
		newExp->m_b = b;
		return newExp;
	}
	static ExpressionPtr CreatePlusNode(ExpressionPtr& a)
	{
		if(a == nullptr)
		{
			return ExpressionPtr();
		}
		else
		{
			ExpressionPtr clone = a->clone();
			ExpressionPtr starNode = CreateStarNode(a);
			return CreateCatNode(clone, starNode);
		}
	}
	static ExpressionPtr CreateQMarkNode(ExpressionPtr& a)
	{
		if(a == nullptr)
		{
			return ExpressionPtr();
		}
    	ExpressionPtr aptr;
		return CreateOrNode(aptr, a);
	}
	typeID GetTypeID(){return m_typeID;}
	std::shared_ptr<CRegularExpression> GetA() {return m_a;}
	std::shared_ptr<CRegularExpression> GetB() {return m_b;}
	char GetC(){return m_c;}
	unsigned GetEnd(){return m_endID;}
	void SetID(int positionID){m_positionID = positionID;}
	int GetID(){return m_positionID;}

	void SetNullable(bool bnullable) {m_bnullable = bnullable;}
	bool GetNullable() {return m_bnullable;}

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

	ExpressionPtr clone()
	{
		ExpressionPtr newExp = std::make_shared<CRegularExpression>();
		newExp->m_typeID = m_typeID;
		if(GetA() != nullptr)
		{
			newExp->m_a = m_a->clone();
		}
		if(GetB() != nullptr)
		{
			newExp->m_b = m_b->clone();
		}
		newExp->m_c = m_c;
		newExp->m_endID = m_endID;

		return newExp;
	}
};

typedef std::shared_ptr<CRegularExpression> regularExpressionPtr;
