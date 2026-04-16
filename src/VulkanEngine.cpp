#include "VulkanEngine.hpp"

void VulkanEngine::run() {
	initWindow();
	initVulkan();
	mainLoop();
	cleanup();
}

void VulkanEngine::initWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // we are not using opengl
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // disable resizable window

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan - Triangle", nullptr, nullptr);
}

void VulkanEngine::initVulkan() {

}

void VulkanEngine::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
	}
}

void VulkanEngine::cleanup() {
	glfwDestroyWindow(window);

	glfwTerminate();
}
