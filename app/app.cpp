#include "app.hpp"

#include <stdexcept>

namespace nugiEngine {

    EngineApp::EngineApp() {
        this->createPipelineLayout();
        this->createPipeline();
        this->createCommandBuffers();
    }

    EngineApp::~EngineApp() {
        vkDestroyPipelineLayout(this->device.device(), this->pipelineLayout, nullptr);
    }

    void EngineApp::run() {
        while (!this->window.shouldClose()) {
            this->window.pollEvents();
        }
    }

    void EngineApp::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;

        if (vkCreatePipelineLayout(this->device.device(), &pipelineLayoutInfo, nullptr, &this->pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    }

    void EngineApp::createPipeline() {
        auto pipelineConfig = EnginePipeline::defaultPipelineConfigInfo(this->WIDTH, this->HEIGHT);
        pipelineConfig.renderPass = this->swapChain.getRenderPass();
        pipelineConfig.pipelineLayout = this->pipelineLayout;

        this->pipeline = std::make_unique<EnginePipeline>(
            device, 
            "shader/simple_shader.frag.spv", 
            "shader/simple_shader.vert.spv", 
            pipelineConfig
        );
    }

    void EngineApp::createCommandBuffers() {

    }
    
    void EngineApp::drawFrame() {

    }
}