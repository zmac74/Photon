#pragma once

#include <string>

namespace Utils 
{
	namespace Generic 
	{
		class String
		{
		public:
			String() = default;
			String(const char* string) : str(string) {}

			inline void Append(const String& string) { str.append(string.str); }
			inline void Append(const char* ptr) { str.append(ptr); }
			inline void Erase(int index) { str.erase(); }
			inline void Clear() { str.clear(); }

			inline int Compare(const String& string) const { return str.compare(string.str); }
			inline bool operator < (const String& string) const { return str < string.str; }
			inline bool operator > (const String& string) const { return str > string.str; }

			inline String operator + (const String& string) { return String((str + string.str).c_str()); }
			inline String operator + (const char* ptr) { return String((str + ptr).c_str()); }
			inline void operator += (const String& string) { str += string.str; }
			inline void operator += (const char* ptr) { str += ptr; }

			inline char& operator[] (int index) { return str[index]; }

			inline bool operator == (const String& string) const { return str == string.str; }
			inline bool operator != (const String& string) const { return str != string.str; }

			inline const char& GetFirstChar() const { return str.front(); }
			inline const char& GetLastChar() const { return str.back(); }

			inline int GetCapacity() const { return str.capacity(); }
			inline bool IsEmpty() const { return str.empty(); }

			inline void Reserve(int capacity) { str.reserve(capacity); }

			inline bool StartsWith(const char* sequence) const { return str.starts_with(sequence); }
			inline bool StartsWith(char character) const { return str.starts_with(character); }
			inline bool EndsWith(const char* sequence) const { return str.ends_with(sequence); }
			inline bool EndsWith(char character) const { return str.ends_with(character); }

			inline String SubStr(int startPos, int endPos) const { return String(str.substr(startPos, endPos - startPos).c_str()); }

			inline int Find(const String& sequence) const { return str.find(sequence.str.c_str()); }
			inline int Find(const String& sequence, int index) const { return str.find(sequence.str.c_str(), index); }
			inline int Find(const char* sequence) const { return str.find(sequence); }
			inline int Find(const char* sequence, int index) const { return str.find(sequence, index); }

			inline int FindFirstOf(const String& sequence) const { return str.find_first_of(sequence.str.c_str()); }
			inline int FindFirstOf(const String& sequence, int index) const { return str.find_first_of(sequence.str.c_str(), index); }
			inline int FindFirstOf(const char* sequence) const { return str.find_first_of(sequence); }
			inline int FindFirstOf(const char* sequence, int index) const { return str.find_first_of(sequence, index); }
			
			inline int FindLastOf(const String& sequence) const { return str.find_last_of(sequence.str.c_str()); }
			inline int FindLastOf(const String& sequence, int index) const { return str.find_last_of(sequence.str.c_str(), index); }
			inline int FindLastOf(const char* sequence) const { return str.find_last_of(sequence); }
			inline int FindLastOf(const char* sequence, int index) const { return str.find_last_of(sequence, index); }

			inline int FindFirstNotOf(const String& sequence) const { return str.find_first_not_of(sequence.str.c_str()); }
			inline int FindFirstNotOf(const String& sequence, int index) const { return str.find_first_not_of(sequence.str.c_str(), index); }
			inline int FindFirstNotOf(const char* sequence) const { return str.find_first_not_of(sequence); }
			inline int FindFirstNotOf(const char* sequence, int index) const { return str.find_first_not_of(sequence, index); }

			inline int FindLastNotOf(const String& sequence) const { return str.find_last_not_of(sequence.str.c_str()); }
			inline int FindLastNotOf(const String& sequence, int index) const { return str.find_last_not_of(sequence.str.c_str(), index); }
			inline int FindLastNotOf(const char* sequence) const { return str.find_last_not_of(sequence); }
			inline int FindLastNotOf(const char* sequence, int index) const { return str.find_last_not_of(sequence, index); }

			inline int ReverseFind(const String& sequence) const { return str.rfind(sequence.str.c_str()); }
			inline int ReverseFind(const String& sequence, int index) const { return str.rfind(sequence.str.c_str(), index); }
			inline int ReverseFind(const char* sequence) const { return str.rfind(sequence); }
			inline int ReverseFind(const char* sequence, int index) const { return str.rfind(sequence, index); }

			inline const char* GetBuffer() const { return str.c_str(); }
			inline int GetLength() const { return str.length(); }
			inline int GetBytes() const { return str.length(); }

		private:
			std::string str;
		};

		inline String ToString(int value) { return String(std::to_string(value).c_str()); }
		inline String ToString(double value) { return String(std::to_string(value).c_str()); }
		inline String ToString(float value) { return String(std::to_string(value).c_str()); }
		inline String ToString(unsigned int value) { return String(std::to_string(value).c_str()); }
		inline String ToString(unsigned long int value) { return String(std::to_string(value).c_str()); }

		inline int ParseInt(const String& string) { return std::stoi(string.GetBuffer()); }
		inline int ParseDouble(const String& string) { return std::stod(string.GetBuffer()); }
		inline int ParseFloat(const String& string) { return std::stof(string.GetBuffer()); }
		inline int ParseLong(const String& string) { return std::stol(string.GetBuffer()); }
	}
}

using namespace Utils;
using namespace Generic;