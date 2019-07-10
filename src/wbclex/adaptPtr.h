#pragma once
#include <memory>

template <class T>
class CAdaptPtr
{
public:
	std::auto_ptr<T> m_ptr;
	CAdaptPtr()
	{
	}

	CAdaptPtr(const CAdaptPtr& ptr)
	{
		m_ptr = const_cast<CAdaptPtr&>(ptr).m_ptr;
	}

	void operator=(const CAdaptPtr& ptr)
	{
		m_ptr = const_cast<CAdaptPtr&>(ptr).m_ptr;
	}

};