#include "VulkanEngine.hpp"

std::vector<char> VulkanEngine::readFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);
	if (!file.is_open()) throw std::runtime_error("failed to open file!");

	size_t fileSize = (size_t) file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();
	return buffer;
}

VkShaderModule VulkanEngine::createShaderModule(const std::vector<char>& code) {
	VkShaderModule shaderModule;
	VkShaderModuleCreateInfo createInfo{};

	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkResult result = vkCreateShaderModule(logicalDevice, &createInfo, nullptr, &shaderModule);
	if (result != VK_SUCCESS) throw std::runtime_error("failed to create shader module!");

	return shaderModule;
}
