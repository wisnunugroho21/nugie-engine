#include "app.hpp"

#include <stdexcept>
#include <array>

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
				this->drawFrame();
			}

			vkDeviceWaitIdle(this->device.device());
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
				"shader/simple_shader.vert.spv",
				"shader/simple_shader.frag.spv",
				pipelineConfig
			);
    }

    void EngineApp::createCommandBuffers() {
			this->commandBuffers.resize(this->swapChain.imageCount());

			VkCommandBufferAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			allocInfo.commandPool = this->device.getCommandPool();
			allocInfo.commandBufferCount = static_cast<uint32_t>(this->commandBuffers.size());

			if (vkAllocateCommandBuffers(this->device.device(), &allocInfo, this->commandBuffers.data()) != VK_SUCCESS) {
				throw std::runtime_error("failed to allocate command buffer");
			}

			for (int i = 0; i < this->commandBuffers.size(); i++) {
				VkCommandBufferBeginInfo commandBeginInfo{};
				commandBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

				if (vkBeginCommandBuffer(this->commandBuffers[i], &commandBeginInfo) != VK_SUCCESS) {
					throw std::runtime_error("failed to begin command buffer " + i);
				}

				VkRenderPassBeginInfo renderBeginInfo{};
				renderBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
				renderBeginInfo.renderPass = this->swapChain.getRenderPass();
				renderBeginInfo.framebuffer = this->swapChain.getFrameBuffer(i);

				renderBeginInfo.renderArea.offset = {0, 0};
				renderBeginInfo.renderArea.extent = this->swapChain.getSwapChainExtent();

				std::array<VkClearValue, 2> clearValues{};
				clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
				clearValues[1].depthStencil = {1.0f, 0};
				renderBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
				renderBeginInfo.pClearValues = clearValues.data();

				vkCmdBeginRenderPass(this->commandBuffers[i], &renderBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

				pipeline->bind(this->commandBuffers[i]);
				vkCmdDraw(this->commandBuffers[i], 3, 1, 0, 0);

				vkCmdEndRenderPass(this->commandBuffers[i]);
				if (vkEndCommandBuffer(this->commandBuffers[i]) != VK_SUCCESS) {
					throw std::runtime_error("failed to record command buffer");
				}
			}
    }
    
    void EngineApp::drawFrame() {
			uint32_t imageIndex;
			auto result = this->swapChain.acquireNextImage(&imageIndex);

			if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
				throw std::runtime_error("failed to acquire swap chain image");
			}

			result = this->swapChain.submitCommandBuffers(&this->commandBuffers[imageIndex], &imageIndex);
			if (result != VK_SUCCESS) {
				throw std::runtime_error("failed to present swap chain image");
			}
    }
}