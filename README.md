# Vulkan Triangle
A simple triangle rendered with Vulkan

![Vulkan Triangle](https://imgur.com/Q64jcz6.png)

## What do this project do
- window init (using GLFW)
- instance creation
- validation layers
- physical device selection
- logical device creation
- queue families and presentation support
- swapchain creation and recreation
- image views
- render pass setup
- graphics pipeline creation
- framebuffers
- command buffers
- synchronization primitives
- frame rendering loop

## Requirements
- Make
- gcc (c++)
- Vulkan-SDK
- glfw3
- glslc

## How to build
```bash
git clone https://github.com/acasamit/vulkan-triangle.git
cd vulkan-triangle
make
./vulkan_engine
```

You can also use `make release` to disable Validation Layers

## Ressources
To achieve the same result you should check the [Vulkan Drawing Triangle Tutorial](https://vulkan-tutorial.com/Drawing_a_triangle)
