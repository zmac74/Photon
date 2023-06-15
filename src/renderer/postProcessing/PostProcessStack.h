#pragma once

#include <utils/collection/Buffer.h>
#include <scene/Shader.h>

namespace Renderer 
{
	namespace PostProcessing 
	{
		class PostProcessLayer
		{
		public:
			PostProcessLayer() = default;
			PostProcessLayer(const Shader shader) { shaders.Add(shader); }

			inline const ArrayList<Shader>& GetShaders() const { return shaders; }
			inline const int GetIterations() const { return iterations; }

		protected:
			PostProcessLayer(ArrayList<Shader> shaders, int iterations) : shaders(shaders), iterations(iterations) {}

		private:
			ArrayList<Shader> shaders = ArrayList<Shader>();
			int iterations = 1;
		};

		class PostProcessSequence : public PostProcessLayer
		{
		public:
			PostProcessSequence(ArrayList<Shader> shaders) : PostProcessLayer(shaders, 1) {}
			PostProcessSequence(ArrayList<Shader> shaders, int iterations) : PostProcessLayer(shaders, iterations) {}
		};

		struct PostProcessStack
		{
		public:
			ArrayList<PostProcessLayer> layers = ArrayList<PostProcessLayer>();

			void AddLayer(PostProcessLayer layer);
			void AddLayer(Shader shader);

			void Refresh();
		};
	}
}

using namespace Renderer;
using namespace PostProcessing;