#pragma once

#include <iostream>
#include <sstream>
#include "ecsTypes.h"

class CBase
{
public:
	CBase(const Component& l_type)
		: m_type(l_type)
	{
	}

	virtual ~CBase()
	{
	}

	Component GetType()
	{
		return m_type;
	}

	friend std::stringstream& operator>>(std::stringstream& l_stream, CBase& b)
	{
		b.ReadIn(l_stream);
		return l_stream;
	}

	virtual void ReadIn(std::stringstream& l_stream) = 0;
protected:
	Component m_type;
};