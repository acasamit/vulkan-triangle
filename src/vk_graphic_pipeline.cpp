#include "VulkanEngine.hpp"

// Shader stages
ShaderStageResult VulkanEngine::createShaderStages() {
	auto vertShaderCode = readFile("spv/shader.vert.spv");
	auto fragShaderCode = readFile("spv/shader.frag.spv");

	VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
	VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

	VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	vertShaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage  = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName  = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	fragShaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage  = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName  = "main";

	return { { vertShaderStageInfo, fragShaderStageInfo }, vertShaderModule, fragShaderModule };
}

// Vertex input
VkPipelineVertexInputStateCreateInfo VulkanEngine::createVertexInputInfo() {
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount   = 0;
	vertexInputInfo.pVertexBindingDescriptions      = nullptr;
	vertexInputInfo.vertexAttributeDescriptionCount = 0;
	vertexInputInfo.pVertexAttributeDescriptions    = nullptr;
	return vertexInputInfo;
}

// Input assembly
VkPipelineInputAssemblyStateCreateInfo VulkanEngine::createInputAssembly() {
	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;
	return inputAssembly;
}

// Viewport state (dynamic)
VkPipelineViewportStateCreateInfo VulkanEngine::createViewportState() {
	VkPipelineViewportStateCreateInfo viewportState{};
	viewportState.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.scissorCount  = 1;
	return viewportState;
}

// Dynamic state
VkPipelineDynamicStateCreateInfo VulkanEngine::createDynamicState(std::vector<VkDynamicState>& dynamicStates) {
	dynamicStates = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

	VkPipelineDynamicStateCreateInfo dynamicState{};
	dynamicState.sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
	dynamicState.pDynamicStates    = dynamicStates.data();
	return dynamicState;
}

// Rasterizer
VkPipelineRasterizationStateCreateInfo VulkanEngine::createRasterizerState() {
	VkPipelineRasterizationStateCreateInfo rasterizer{};
	rasterizer.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable        = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode             = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth               = 1.0f;
	rasterizer.cullMode                = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace               = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable         = VK_FALSE;
	rasterizer.depthBiasConstantFactor = 0.0f;
	rasterizer.depthBiasClamp          = 0.0f;
	rasterizer.depthBiasSlopeFactor    = 0.0f;
	return rasterizer;
}

// Multisampling
VkPipelineMultisampleStateCreateInfo VulkanEngine::createMultisamplingState() {
	VkPipelineMultisampleStateCreateInfo multisampling{};
	multisampling.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable   = VK_FALSE;
	multisampling.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
	multisampling.minSampleShading      = 1.0f;
	multisampling.pSampleMask           = nullptr;
	multisampling.alphaToCoverageEnable = VK_FALSE;
	multisampling.alphaToOneEnable      = VK_FALSE;
	return multisampling;
}

// Color blending
VkPipelineColorBlendStateCreateInfo VulkanEngine::createColorBlendState(VkPipelineColorBlendAttachmentState& attachment) {
	attachment = {};
	attachment.colorWriteMask      = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
									 VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	attachment.blendEnable         = VK_TRUE;
	attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	attachment.colorBlendOp        = VK_BLEND_OP_ADD;
	attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	attachment.alphaBlendOp        = VK_BLEND_OP_ADD;

	VkPipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType             = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable     = VK_FALSE;
	colorBlending.logicOp           = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount   = 1;
	colorBlending.pAttachments      = &attachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;
	return colorBlending;
}

// Pipeline layout
void VulkanEngine::createPipelineLayout() {
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount         = 0;
	pipelineLayoutInfo.pSetLayouts            = nullptr;
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.pPushConstantRanges    = nullptr;

	VkResult result = vkCreatePipelineLayout(logicalDevice, &pipelineLayoutInfo, nullptr, &pipelineLayout);
	if (result != VK_SUCCESS) throw std::runtime_error("failed to create pipeline layout!");
}

// Graphics pipeline creator
void VulkanEngine::createGraphicsPipeline() {
	auto shaderResult = createShaderStages();

	auto vertexInputInfo = createVertexInputInfo();
	auto inputAssembly   = createInputAssembly();
	auto viewportState   = createViewportState();

	std::vector<VkDynamicState> dynamicStatesVec;
	auto dynamicState    = createDynamicState(dynamicStatesVec);

	auto rasterizer      = createRasterizerState();
	auto multisampling   = createMultisamplingState();

	VkPipelineColorBlendAttachmentState colorBlendAttachment;
	auto colorBlending   = createColorBlendState(colorBlendAttachment);

	createPipelineLayout();

	vkDestroyShaderModule(logicalDevice, shaderResult.fragModule, nullptr);
	vkDestroyShaderModule(logicalDevice, shaderResult.vertModule, nullptr);
}
