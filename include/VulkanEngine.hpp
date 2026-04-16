#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

// window size
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class VulkanEngine {
public:
	void run();

private:
	GLFWwindow* window;

	void initWindow();

	void initVulkan();

	void mainLoop();

	void cleanup();
};
