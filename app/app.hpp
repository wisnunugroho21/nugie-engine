#pragma once

#include "../window/window.hpp"
#include "../device/device.hpp"
#include "../pipeline/pipeline.hpp"

namespace nugiEngine {
	class EngineApp
	{
		public:
			static constexpr int WIDTH = 800;
			static constexpr int HEIGHT = 600;

			void run();

		private:
			EngineWindow window{WIDTH, HEIGHT, "Testing vulkan"};
			EngineDevice device{window};
			EnginePipeline pipeline{"bin/shaders/simple_shader.frag.spv", "bin/shaders/simple_shader.vert.spv"};
	};
	
}