#pragma once

namespace Core 
{
	namespace System 
	{
		double GetUpTime();
		double GetUpTimeMillis();
		double GetUpTimeMicros();
		double GetUpTimeNanos();

		double GetDeltaTime();
		double GetDeltaTimeMillis();
		double GetDeltaTimeMicros();
		double GetDeltaTimeNanos();
		
		void CalculateFrameTime();
	}
}

using namespace Core;
using namespace System;