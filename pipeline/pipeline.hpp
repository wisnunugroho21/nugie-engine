#pragma once

#include <string>
#include <vector>

namespace nugiEngine {
	class EnginePipeline
	{
		public:
			EnginePipeline(const std::string& vertFilePath, const std::string& fragFilePath);

		private:
			static std::vector<char> readFile(const std::string& filepath);
			void createGraphicPipeline(const std::string& vertFilePath, const std::string& fragFilePath);
	};
}