#include "pipeline.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace nugiEngine {
	EnginePipeline::EnginePipeline(
		EngineDevice& device, 
		const std::string& vertFilePath, 
		const std::string& fragFilePath, 
		const PipelineConfigInfo& configInfo
	) : engineDevice{device} {
		this->createGraphicPipeline(vertFilePath, fragFilePath, configInfo);
	}

	EnginePipeline::~EnginePipeline() {

	}

	std::vector<char> EnginePipeline::readFile(const std::string& filepath) {
		std::ifstream file{filepath, std::ios::ate | std::ios::binary};

		if (!file.is_open()) {
			throw std::runtime_error("failed to open file");
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();
		return buffer;
	}

	void EnginePipeline::createGraphicPipeline(
		const std::string& vertFilePath, 
		const std::string& fragFilePath,
		const PipelineConfigInfo& configInfo
	) {
		auto vertSize = this->readFile(vertFilePath);
		auto fragSize = this->readFile(fragFilePath);

		std::cout << "Vertex Size Code: " << vertSize.size() << '\n';
		std::cout << "Frag Size Code: " << fragSize.size() << '\n';
	}

	void EnginePipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule) {
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const u_int32_t*>(code.data());

		if (vkCreateShaderModule(this->engineDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
			throw std::runtime_error("failed to create shader module");
		}
	}

	PipelineConfigInfo EnginePipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height) {
		PipelineConfigInfo configInfo;

		return configInfo;
	}
} // namespace nugiEngine
