#ifndef SCREENSPELL_GPU_QUEUE_INDICES_H
#define SCREENSPELL_GPU_QUEUE_INDICES_H

#include <vulkan/vulkan.h>

#include "screenspell/common.h"

/**
 * Expands to `4`, as ideally, a GPU would have four separate queue families.  See `GpuQueueFamilyIndices` for more details.
 */
#define IDEAL_QUEUE_FAMILY_COUNT 4

/**
 * Stores GPU queue family indices.
 * 
 * If no dedicated queues exist, `transferIndex` or `computeIndex` may be the same as `graphicsIndex`
 * (this happens in integrated graphics).
 */
typedef struct {
  u32 graphicsIndex;
  u32 presentIndex;
  u32 transferIndex;
  u32 computeIndex;

  bool hasDedicatedTransfer;
  bool hasDedicatedCompute;
} GpuQueueFamilyIndices;

/**
 * Finds all queue families of `device` and stores their indices in `familyIndices`.
 * 
 * Returns whether the `device` is usable, i.e. whether it has at least a graphics and a present queue family.
 */
bool findGpuQueueFamilyIndices(VkPhysicalDevice device, VkSurfaceKHR surface, GpuQueueFamilyIndices *familyIndices);

/**
 * Deduplicates queue indices if there are duplicates, e.g. if the transfer queue and the graphics queue share the same indices.
 * This is useful for the `VkDeviceQueueCreateInfo` step, as having multiple `VkDeviceQueueCreateInfo`s for the same queue index makes Vulkan go silly.
 * 
 * Returns how many unique queue indices remained after the deduplication.
 */
u32 deduplicateQueueFamilyIndices(const GpuQueueFamilyIndices *indices, u32 *deduplicatedIndices);

#endif