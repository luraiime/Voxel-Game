#ifndef SCREENSPELL_GPU_HANDLE_H
#define SCREENSPELL_GPU_HANDLE_H

#include <vulkan/vulkan.h>

#include "screenspell/instance/instance.h"
#include "screenspell/gpu/queue/gpu_queue_indices.h"

/**
 * Stores the logical GPU information before VkDevice creation.
 */
typedef struct {
  VkPhysicalDevice physicalGpu;

  GpuQueueFamilyIndices queueFamilyIndices;
} GpuInfo;

/**
 * Finds the first usable GPU in the list of available GPUs, that is, the first GPU to have both a graphics and present channel.
 * 
 * Returns false if no such GPU was found, while also logging a debug message.
 */
bool initGpuInfo(const ScreenspellInstance *instance, VkSurfaceKHR surface, GpuInfo *gpuInfo);

#endif