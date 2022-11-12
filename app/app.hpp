#pragma once

#include "../window/window.hpp"
#include "../device/device.hpp"
#include "../pipeline/pipeline.hpp"
#include "../swap_chain/swap_chain.hpp"

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
			EngineSwapChain swapChain{device, window.getExtent()};
			EnginePipeline pipeline{
				device, 
				"shader/simple_shader.frag.spv", 
				"shader/simple_shader.vert.spv", 
				EnginePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)
			};
	};
	
}