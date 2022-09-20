#pragma once

#include <iostream>
#include <assert.h>

namespace Debug 
{
	template<typename Type>
	void Log(Type type)
	{
		std::cout << type << std::endl;
	}

	template<typename Type>
	void Assert(Type type)
	{
		Log(type);
		assert(0);
	}

	void Assert();
}

using namespace Debug;