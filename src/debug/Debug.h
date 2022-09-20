#pragma once

#include <iostream>
#include <assert.h>

namespace Debug 
{
	template<typename Type>
	void log(Type type)
	{
		std::cout << type << std::endl;
	}

	template<typename Type>
	void forceShutdown(Type type)
	{
		log(type);
		assert(0);
	}

	void forceShutdown();
}

using namespace Debug;