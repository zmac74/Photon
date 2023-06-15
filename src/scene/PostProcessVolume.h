#pragma once

#include <renderer/postProcessing/PostProcessStack.h>
#include <utils/collection/Buffer.h>

#include <scene/BoundingVolume.h>

namespace Scene 
{
	extern ArrayList<PostProcessVolume> postProcessVolumes;
	
	struct PostProcessVolume
	{
	public:
		PostProcessVolume() = default;
		PostProcessVolume(AABB aabb, bool boundless = false, int priority = 0, PostProcessStack postProcessStack = PostProcessStack{})
			: aabb(aabb), boundless(boundless), priority(priority), postProcessStack(postProcessStack) {}
	
		PostProcessStack postProcessStack;
		AABB aabb;

		bool boundless = false;
		int priority = 0;
	};

	PostProcessVolume* CreatePostProcessVolume(AABB aabb, bool boundless = false, int priority = 0, PostProcessStack postProcessStack = PostProcessStack{});
}

using namespace Scene;