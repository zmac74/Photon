#pragma once

#include <chrono>

namespace Debug 
{
	namespace Profiler 
	{
		extern float lastScopeTime;
		
		class ScopeTimer 
		{
		public:
			ScopeTimer();
			~ScopeTimer();

		private:
			std::chrono::steady_clock::time_point startTime;
		};
	}
}

using namespace Debug;
using namespace Profiler;