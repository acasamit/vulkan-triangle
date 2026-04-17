#include "VulkanEngine.hpp"

void VulkanEngine::createSurface() {
	VkResult result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
	if (result != VK_SUCCESS) throw std::runtime_error("failed to create window surface!");
}
