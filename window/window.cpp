#include "window.hpp"

namespace nugiEngine {
  EngineWindow::EngineWindow(int w, int h, std::string name) : width{w}, height{h}, name{name} {
    this->init();
  }

  EngineWindow::~EngineWindow() {
    this->destroy();
  }

  void EngineWindow::init() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->window = glfwCreateWindow(this->width, this->height, this->name.c_str(), nullptr, nullptr);
  }

  void EngineWindow::destroy() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
  }

  bool EngineWindow::shouldClose() {
    return glfwWindowShouldClose(this->window);
  }

  void EngineWindow::pollEvents() {
    glfwPollEvents();
  }

  void EngineWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
    if (glfwCreateWindowSurface(instance, this->window, nullptr, surface) != VK_SUCCESS) {
      throw std::runtime_error("failed to create window surface");
    }
  }

  VkExtent2D EngineWindow::getExtent() {
    return { static_cast<uint32_t>(this->width), static_cast<uint32_t>(this->height) };
  }
}