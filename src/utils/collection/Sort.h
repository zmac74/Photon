#pragma once

#include <utils/collection/Buffer.h>

namespace Utils 
{
	namespace Collection 
	{
		template<typename Type>
		void BubbleSort(ArrayList<Type>& arrayList, bool(*comparator)(const Type&, const Type&))
		{
			for (int i = 0; i < arrayList.GetLength() - 1; i++) 
			{
				for (int j = 0; j < arrayList.GetLength() - i - 1; j++)
				{
					if (comparator(arrayList[j], arrayList[j + 1]))
					{
						Type tmp = arrayList[j + 1];
						arrayList[j + 1] = arrayList[i];
						arrayList[j] = tmp;
					}
				}
			}	
		}
	}
}

using namespace Utils;
using namespace Collection;