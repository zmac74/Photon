#include <chrono>

#include <debug/profiler/Timer.h>

float Debug::Profiler::lastScopeTime = 0;

ScopeTimer::ScopeTimer() 
{
	startTime = std::chrono::high_resolution_clock::now();
}

ScopeTimer::~ScopeTimer() 
{
	std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - startTime;
	Debug::Profiler::lastScopeTime = duration.count();
}