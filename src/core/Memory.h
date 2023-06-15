#pragma once

#include <algorithm>

namespace Core 
{
	inline void* Allocate(int bytes) 
	{
		return operator new[](bytes);
	}

	template<typename Type>
	inline void Construct(Type* address)
	{
		new (address) Type();
	}

	template<typename Type>
	inline void Construct(Type* address, const Type& src)
	{
		new (address) Type(src);
	}

	template<typename Type>
	inline void ConstructBuffer(Type* address, int elements)
	{
		for (int i = 0; i < elements; i++) new (address + i) Type();

	}

	template<typename Type>
	inline void ConstructBuffer(Type* address, Type* buffer, int length)
	{
		for (int i = 0; i < length; i++) new (address + i) Type(buffer[i]);
	}
	
	inline void MemCopy(void* src, void* dest, int bytes)
	{
		std::memcpy(dest, src, bytes);
	}
	
	template<typename Source, typename Destination>
	inline void Copy(Source src, Destination dest, int length)
	{
		std::copy(src, &src[length], dest);
	}

	template<typename Type>
	inline void Destruct(Type* address)
	{
		address->~Type();
	}

	template<typename Type>
	inline void DestructBuffer(Type* address, int length)
	{
		for (int i = length - 1; i >= 0; i--) address[i]->~Type();
	}

	inline void Free(void* buffer) 
	{
		operator delete[](buffer);
	}
}

using namespace Core;