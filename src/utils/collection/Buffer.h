#pragma once

#include <stdlib.h>
#include <malloc.h>

#include <debug/Debug.h>

namespace Utils 
{
	namespace Collection 
	{
		template<typename Type>
		class ArrayList 
		{
		public:
			ArrayList() {}

			ArrayList(int capacity) : capacity(capacity)
			{
				if (capacity == 0) Assert("Error: Arraylist has capacity of zero.");
			}

			~ArrayList() 
			{
				//if (allocatedElements != 0) free(data);
			}

			void Add(Type element)
			{
				if (elements == allocatedElements)
				{
					Type* newAlloc = (Type*)malloc((sizeof(Type) * elements) + (sizeof(Type) * capacity));
					std::memcpy(newAlloc, data, elements * sizeof(Type));
					if (allocatedElements != 0) free(data);
					
					data = newAlloc;
					allocatedElements += capacity;
				}

				data[elements] = element;
				elements++;
			}

			void Reserve(int elements)
			{
				if (elements == 0) Assert("Error: Arraylist has capacity of zero.");
				capacity = elements;
			}

			Type& Get(int index) const
			{
				if (index >= elements) Assert("Error: Arraylist index out of bounds.");
				return data[index];
			}

			Type& operator[](int index) const
			{
				if (index >= elements) Assert("Error: Arraylist index out of bounds.");
				return data[index];
			}

			Type& GetLastElement() const 
			{
				if (elements == 0) Assert("Error: Arraylist size is zero.");
				return data[elements - 1];
			}

			Type& GetFirstElement() const
			{
				if (elements == 0) Assert("Error: Arraylist size is zero.");
				return data[0];
			}

			inline int GetLength() const { return elements; }

			inline int GetAllocatedLength() const { return allocatedElements; }

			inline int GetSize() const { return elements * sizeof(Type); }

			inline int GetAllocatedSize() const { return allocatedElements * sizeof(Type); }

			inline int GetCapacity() const { return capacity; }


		private:
			Type* data = nullptr;

			int capacity = 1;
			int allocatedElements = 0;
			int elements = 0;
		};
		
		struct FloatBuffer 
		{
		public:
			FloatBuffer(float* buffer, int length) : buffer(buffer), length(length) {}

			float* buffer = nullptr;
			int length = 0;
		};

		struct IntBuffer
		{
		public:
			IntBuffer(int* buffer, int length) : buffer(buffer), length(length) {}

			int* buffer = nullptr;
			int length = 0;
		};
	}
}

using namespace Utils;
using namespace Collection;