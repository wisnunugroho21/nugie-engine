#include "pipeline.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace nugiEngine {
	EnginePipeline::EnginePipeline(const std::string& vertFilePath, const std::string& fragFilePath) {
		this->createGraphicPipeline(vertFilePath, fragFilePath);
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

	void EnginePipeline::createGraphicPipeline(const std::string& vertFilePath, const std::string& fragFilePath) {
		auto vertSize = this->readFile(vertFilePath);
		auto fragSize = this->readFile(fragFilePath);

		std::cout << "Vertex Size Code: " << vertSize.size() << '\n';
		std::cout << "Frag Size Code: " << fragSize.size() << '\n';
	}
} // namespace nugiEngine
