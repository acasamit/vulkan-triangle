#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class VulkanEngine {
public:
	void run();

private:
	void initVulkan();

	void mainLoop();

	void cleanup();
};
