#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include <stdexcept>

namespace nugiEngine {
	class EngineWindow
	{
		public:
			EngineWindow(int w, int h, std::string name);
			~EngineWindow();

			EngineWindow(const EngineWindow&) = delete;
			EngineWindow& operator = (const EngineWindow&) = delete;

			bool shouldClose();
			void pollEvents();
			void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

		private:
			const int width;
			const int height;

			std::string name;
			GLFWwindow *window;

			void init();
			void destroy();
	};
}
