#pragma once

#include <string>
#include <vector>

#include "../device/device.hpp"

namespace nugiEngine {
	struct PipelineConfigInfo {
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;

		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
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