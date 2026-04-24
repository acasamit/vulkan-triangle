#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <optional>
#include <set>
#include <cstdint>
#include <limits>
#include <algorithm>
#include <fstream>
#include <array>

// window size
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats; // pixel format, color space supported for surface
	std::vector<VkPresentModeKHR> presentModes;
};

struct ShaderStageResult {
	std::array<VkPipelineShaderStageCreateInfo, 2> stages;
	VkShaderModule vertModule;
	VkShaderModule fragModule;
};

class VulkanEngine {
public:
	void run();

private:
	GLFWwindow* window;
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkSurfaceKHR surface;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice logicalDevice;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	uint32_t currentFrame = 0;

	// Debug
	static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
	void setupDebugMessenger();
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
	bool checkValidationLayerSupport();

	// vk_main.cpp
	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();

	// vk_instance.cpp
	void createInstance();
	void populateAppInfo(VkApplicationInfo& appInfo);
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	std::vector<const char*> getRequiredExtensions();

	// vk_surface.cpp
	void createSurface();

	// vk_device.cpp
	void pickPhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	void createLogicalDevice();

	// vk_swapchain.cpp
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createSwapChain();

	// vk_image_views.cpp
	void createImageViews();

	// vk_render_passes.cpp
	VkAttachmentDescription createColorAttachmentDescription();
	VkAttachmentReference createColorAttachmentReference();
	VkSubpassDescription createSubpass(const VkAttachmentReference& colorAttachmentRef);
	VkSubpassDependency createDependency();
	void createRenderPass();

	// vk_graphic_pipeline.cpp
	ShaderStageResult createShaderStages();
	VkPipelineVertexInputStateCreateInfo    createVertexInputInfo();
	VkPipelineInputAssemblyStateCreateInfo  createInputAssembly();
	VkPipelineViewportStateCreateInfo       createViewportState();
	VkPipelineDynamicStateCreateInfo        createDynamicState(std::vector<VkDynamicState>& dynamicStates);
	VkPipelineRasterizationStateCreateInfo  createRasterizerState();
	VkPipelineMultisampleStateCreateInfo    createMultisamplingState();
	VkPipelineColorBlendStateCreateInfo     createColorBlendState(VkPipelineColorBlendAttachmentState& attachment);
	void                                    createPipelineLayout();
	void                                    createGraphicsPipeline();

	// vk_shaders.cpp
	static std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);

	// vk_framebuffer.cpp
	void createFramebuffers();

	// vk_command.cpp
	void createCommandPool();
	void createCommandBuffers();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	// vk_sync.cpp
	void createSyncObjects();

	// vk_draw.cpp
	void waitForFrame();
	uint32_t acquireNextImage();
	void recordCurrentFrame(uint32_t imageIndex);
	void submitCurrentFrame();
	void presentCurrentFrame(uint32_t imageIndex);
	void drawFrame();
};
