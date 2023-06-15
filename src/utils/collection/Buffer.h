#pragma once

#include <stdlib.h>
#include <initializer_list>
#include <unordered_map>
#include <map>

#include <debug/Debug.h>
#include <core/Memory.h>

namespace Utils
{
	namespace Collection
	{
		template<typename Type>
		using InitializerList = std::initializer_list<Type>;

		template<typename... Types>
		class Tuple
		{
		public:
			Tuple() = default;
			Tuple(const Types&... types) : tuple(types...) {}

			constexpr int GetTypeCount() const { return sizeof...(Types); }

			constexpr int GetSize() const { return (sizeof(Types) + ... + 0); }

			template<int index>
			inline auto& Get() const { return std::get<index>(tuple); }

			template<int index>
			inline void Set(const auto& value) { std::get<index>(tuple) = value; }

		private:
			std::tuple<Types...> tuple;
		};

		template<typename Type>
		class ArrayList
		{
		public:
			ArrayList() {}

			ArrayList(int capacity) : capacity(capacity)
			{
				if (capacity == 0) Assert("Error: Arraylist has capacity of zero.");
			}

			ArrayList(const InitializerList<Type>& initializationList)
			{
				elements = initializationList.size();
				allocatedElements = initializationList.size();

				data = new Type[elements];
				Copy(initializationList.begin(), data, elements);
			}

			ArrayList(Type* data, int length, int capacity)
			{
				if (capacity == 0) Assert("Error: Arraylist has capacity of zero.");

				elements = length;
				allocatedElements = length;
				this->capacity = capacity;

				this->data = new Type[elements];
				Copy(data, this->data, elements);
			}

			ArrayList(const ArrayList<Type>& src) : capacity(src.capacity), allocatedElements(src.allocatedElements), elements(src.elements)
			{
				data = new Type[src.allocatedElements];
				Copy(src.data, data, src.elements);
			}

			~ArrayList()
			{
				if (allocatedElements != 0) delete[] data;
			}

			ArrayList<Type>& operator = (const ArrayList<Type>& src)
			{
				capacity = src.capacity;
				allocatedElements = src.allocatedElements;
				elements = src.elements;

				data = new Type[src.allocatedElements];
				Copy(src.data, data, src.elements);

				return *this;
			}

			void Add(const Type& element)
			{
				if (elements == allocatedElements)
				{
					Type* newAlloc = new Type[elements + capacity];
					Copy(data, newAlloc, elements);
					if (allocatedElements != 0) delete[] data;

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

			void Set(int index, const Type& type)
			{
				if (index >= elements) Assert("Error: Arraylist index out of bounds.");
				data[index] = type;
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

			inline Type* GetBuffer() const { return data; }


		private:
			Type* data = nullptr;

			int capacity = 1;
			int allocatedElements = 0;
			int elements = 0;
		};

		template<typename... Types>
		class TupleList
		{
		public:
			TupleList() {}

			TupleList(int capacity) { arrayList = ArrayList<Tuple<Types...>>(capacity); }

			inline TupleList<Types...>& operator = (const TupleList<Types...>& src) 
			{ 
				arrayList = src.arrayList; 
				return *this;
			}

			inline void Add(const Types&... types) { arrayList.Add(Tuple<Types...>(types...)); }

			inline void Reserve(int elements) { arrayList.Reserve(elements); }

			inline void Set(int index, const Types&... types) { arrayList.Set(index, Tuple<Types...>(types...)); }

			inline Tuple<Types...>& Get(int index) const { return arrayList.Get(index); }
			
			template<int tupleIndex>
			inline auto& Get(int index) const { return arrayList.Get(index).Get<tupleIndex>(); }

			inline Tuple<Types...>& operator[](int index) const { return arrayList.Get(index); }

			inline Tuple<Types...>& GetLastElement() const { return arrayList.GetLastElement(); }

			template<int tupleIndex>
			inline auto& GetLastElement() const { return std::get<tupleIndex>(arrayList.GetLastElement()); }

			inline Tuple<Types...>& GetFirstElement() const { return arrayList.GetFirstElement(); }

			template<int tupleIndex>
			inline auto& GetFirstElement() const { return std::get<tupleIndex>(arrayList.GetFirstElement()); }

			
			inline int GetLength() const { return arrayList.GetLength(); }

			inline int GetAllocatedLength() const { return arrayList.GetAllocatedLength(); }

			inline int GetSize() const { return arrayList.GetSize(); }

			inline int GetTupleSize() const { return (sizeof(Types) + ... + 0); }

			inline int GetAllocatedSize() const { return arrayList.GetAllocatedSize(); }

			inline int GetCapacity() const { return arrayList.GetCapacity(); }

		private:
			ArrayList<Tuple<Types...>> arrayList;
		};

		template<typename Type>
		class LinkedList
		{
		public:
			LinkedList() {}

			LinkedList(int capacity) : capacity(capacity)
			{
				if (capacity == 0) Assert("Error: Linkedlist has capacity of zero.");
			}

			LinkedList(const InitializerList<Type>& initializationList)
			{
				elements = initializationList.size();
				allocatedElements = initializationList.size();

				for (int i = 0; i < elements; i++)
				{
					Type* pointer = new Type[1];
					Copy(initializationList.begin() + i, pointer, 1);
					pointers.Add(pointer);
				}
			}

			LinkedList(Type* data, int length, int capacity)
			{
				if (capacity == 0) Assert("Error: Linkedlist has capacity of zero.");

				elements = length;
				this->capacity = capacity;

				int blockAmount = (length / capacity) + 1;
				allocatedElements = blockAmount * capacity;

				for (int i = 0; i < blockAmount; i++)
				{
					int blockWriteAmount = (i == blockAmount - 1) ? elements % capacity : capacity;

					Type* pointer = new Type[capacity];
					Copy(data + (i * capacity), pointer, blockWriteAmount);
					pointers.Add(pointer);
				}
			}

			LinkedList(const LinkedList<Type>& src) : elements(src.elements), allocatedElements(src.allocatedElements), capacity(src.capacity)
			{
				pointers = src.pointers;
				for (int i = 0; i < pointers.GetLength(); i++)
				{
					pointers[i] = new Type[capacity];
					Copy(src.pointers[i], pointers[i], src.capacity);
				}
			}

			~LinkedList()
			{
				for (int i = 0; i < pointers.GetLength(); i++) delete[] pointers[i];
			}

			LinkedList<Type>& operator = (const LinkedList<Type>& src)
			{
				capacity = src.capacity;
				allocatedElements = src.allocatedElements;
				elements = src.elements;

				pointers = src.pointers;
				for (int i = 0; i < pointers.GetLength(); i++)
				{
					pointers[i] = new Type[capacity];
					Copy(src.pointers[i], pointers[i], src.capacity);
				}

				return *this;
			}

			void Add(const Type& element)
			{
				if (elements == allocatedElements)
				{
					Type* pointer = new Type[capacity];
					pointers.Add(pointer);
					allocatedElements += capacity;
				}

				pointers.GetLastElement()[elements % capacity] = element;
				elements++;
			}

			void Set(int index, const Type& type)
			{
				if (index >= elements) Assert("Error: Linkedlist index out of bounds.");
				pointers[(int)(index / capacity)][index % capacity] = type;
			}

			Type& Get(int index) const
			{
				if (index >= elements) Assert("Error: Linkedlist index out of bounds.");
				return pointers[(int)(index / capacity)][index % capacity];
			}

			Type& operator[](int index) const
			{
				if (index >= elements) Assert("Error: Linkedlist index out of bounds.");
				return pointers[(int)(index / capacity)][index % capacity];
			}

			Type& GetLastElement() const
			{
				if (elements == 0) Assert("Error: Linkedlist size is zero.");
				return pointers.GetLastElement()[capacity - 1];
			}

			Type& GetFirstElement() const
			{
				if (elements == 0) Assert("Error: Linkedlist size is zero.");
				return pointers.GetFirstElement()[0];
			}

			inline int GetLength() const { return elements; }

			inline int GetAllocatedLength() const { return allocatedElements; }

			inline int GetSize() const { return elements * sizeof(Type); }

			inline int GetAllocatedSize() const { return allocatedElements * sizeof(Type); }

			inline int GetCapacity() const { return capacity; }

			inline int GetBlockCount() const { return pointers.GetLength(); }

			inline Type** GetBufferBlocks() const { return pointers.GetBuffer(); }
			inline Type* GetBuffer(int index) const { return pointers.GetBuffer()[index]; }

		private:
			ArrayList<Type*> pointers = ArrayList<Type*>(4);

			int capacity = 1;
			int allocatedElements = 0;
			int elements = 0;
		};

		template<typename Type>
		class Stack
		{
		public:
			Stack(int capacity) : capacity(capacity)
			{
				if (capacity == 0) Assert("Error: Stack has capacity of zero.");
				data = (Type*)malloc(sizeof(Type) * capacity);
			}

			void Push(const Type& element)
			{
				if (elements == capacity) Assert("Error: Stack overflow.");
				data[elements] = element;
				elements++;
			}

			Type& Pop()
			{
				if (elements == 0) Assert("Error: Stack is empty.");
				elements--;
				return data[elements];
			}

			Type& Front() const
			{
				if (elements == 0) Assert("Error: Stack is empty.");
				return data[elements - 1];
			}

			Type& Back() const
			{
				if (elements == 0) Assert("Error: Stack is empty.");
				return data[0];
			}

			Type& Peek(int index) const
			{
				if (index >= elements) Assert("Error: Stack index out of bounds.");
				return data[index];
			}

			Type& operator[](int index) const
			{
				if (index >= elements) Assert("Error: Stack index out of bounds.");
				return data[index];
			}

			inline int GetCapacity() const { return capacity; }

			inline int GetLength() const { return elements; }

			inline bool IsFull() const { return (elements == capacity); }

		private:
			Type* data;

			int capacity;
			int elements = 0;
		};

		template<typename Key, typename Value>
		class Map
		{
		public:
			Map() {}

			void Add(const Key& key, const Value& value)
			{
				map.insert(std::make_pair(key, value));
				elements++;
			}

			void Delete(const Key& key)
			{
				map.erase(key);
				elements--;
			}

			inline bool Has(const Key& key) const
			{
				return map.contains(key);
			}

			inline Value& Set(const Key& key, const Value& value)
			{
				return map[key] = value;
			}

			inline Value& Get(const Key& key)
			{
				return map[key];
			}

			inline Value& operator[](const Key& key)
			{
				return map[key];
			}

			inline void Clear() 
			{
				map.clear();
			}

			inline bool IsEmpty(){ map.empty(); }

			inline int GetLength() const { return elements; }

			inline int GetSize() const { return elements * (sizeof(Key) + sizeof(Value)); }

		private:
			std::map<Key, Value> map;
			int elements = 0;
		};

		template<typename Key, typename Value>
		class HashMap 
		{
		public:
			void Add(const Key& key, const Value& value)
			{
				map.insert(std::make_pair(key, value));
				elements++;
			}

			void Delete(const Key& key)
			{
				map.erase(key);
				elements--;
			}

			inline bool Has(const Key& key) const
			{
				return map.contains(key);
			}

			inline Value& Set(const Key& key, const Value& value)
			{
				return map[key] = value;
			}

			inline Value& Get(const Key& key)
			{
				return map[key];
			}

			inline Value& operator[](const Key& key)
			{
				return map[key];
			}

			inline void Clear()
			{
				map.clear();
			}

			inline bool IsEmpty() { map.empty(); }

			inline int GetLength() const { return elements; }

			inline int GetSize() const { return elements * (sizeof(Key) + sizeof(Value)); }

		private:
			std::unordered_map<Key, Value> map;
			int elements = 0;
		};

		struct FloatBuffer
		{
		public:
			FloatBuffer() : buffer(nullptr), length(0) {}
			FloatBuffer(float* buffer, int length) : buffer(buffer), length(length) {}

			float* buffer = nullptr;
			int length = 0;
		};

		struct IntBuffer
		{
		public:
			IntBuffer() : buffer(nullptr), length(0) {}
			IntBuffer(int* buffer, int length) : buffer(buffer), length(length) {}

			int* buffer = nullptr;
			int length = 0;
		};

		template<typename Type>
		class Array 
		{
		public:
			Array() : buffer(nullptr), length(0) {}
			Array(Type* buffer, int length) : buffer(buffer), length(length) {}

			Array(const InitializerList<Type>& initializationList) 
			{
				buffer = initializationList.begin();
				length = initializationList.size();
			}

			Array(const ArrayList<Type>& arrayList)
			{
				buffer = arrayList.GetBuffer();
				length = arrayList.GetLength();
			}

			inline Type* GetBuffer() const { return buffer; }
			inline Type* GetLength() const { return length; }

		private:
			Type* buffer;
			int length;
		};
	}
}

using namespace Utils;
using namespace Collection;