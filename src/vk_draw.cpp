#include "VulkanEngine.hpp"

void VulkanEngine::waitForFrame() {
	vkWaitForFences(logicalDevice, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
	vkResetFences(logicalDevice, 1, &inFlightFence);
}

uint32_t VulkanEngine::acquireNextImage() {
	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(
		logicalDevice,
		swapChain,
		UINT64_MAX,
		imageAvailableSemaphore,
		VK_NULL_HANDLE,
		&imageIndex
	);

	if (result != VK_SUCCESS)
		throw std::runtime_error("failed to acquire swap chain image!");

	return imageIndex;
}

void VulkanEngine::recordCurrentFrame(uint32_t imageIndex) {
	vkResetCommandBuffer(commandBuffer, 0);
	recordCommandBuffer(commandBuffer, imageIndex);
}

void VulkanEngine::submitCurrentFrame() {
	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { imageAvailableSemaphore };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	VkSemaphore signalSemaphores[] = { renderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	VkResult result = vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFence);
	if (result != VK_SUCCESS)
		throw std::runtime_error("failed to submit draw command buffer!");
}

void VulkanEngine::presentCurrentFrame(uint32_t imageIndex) {
	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &renderFinishedSemaphore;

	VkSwapchainKHR swapChains[] = { swapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr;

	vkQueuePresentKHR(presentQueue, &presentInfo);
}

void VulkanEngine::drawFrame() {
	waitForFrame();

	uint32_t imageIndex = acquireNextImage();
	recordCurrentFrame(imageIndex);
	submitCurrentFrame();
	presentCurrentFrame(imageIndex);
}
