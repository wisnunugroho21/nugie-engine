#pragma once

#include <string>
#include <vector>

#include "../device/device.hpp"

namespace nugiEngine {
	struct PipelineConfigInfo
	{
		/* data */
	};
	
	class EnginePipeline
	{
		public:
			EnginePipeline(
				EngineDevice& device, 
				const std::string& vertFilePath, 
				const std::string& fragFilePath, 
				const PipelineConfigInfo& configInfo
			);
			~EnginePipeline();

			EnginePipeline(const EnginePipeline&) = delete;
			void operator =(const EngineDevice&) = delete;

			static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

		private:
			EngineDevice& engineDevice;
			VkPipeline graphicPipeline;
			VkShaderModule vertShaderModule;
			VkShaderModule fragShaderModule;
			
			static std::vector<char> readFile(const std::string& filepath);
			void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);
			void createGraphicPipeline(
				const std::string& vertFilePath, 
				const std::string& fragFilePath, 
				const PipelineConfigInfo& configInfo
			);
	};
}