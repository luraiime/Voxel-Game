#include "screenspell/gpu/queue/gpu_queue_indices.h"

#include <stdlib.h>

/**
 * Expands to `queueFlags & flag`, determining whether the given bit flag is present in `queueFlags`.
 */
#define QUEUE_HAS_FLAG(queueFlags, bitFlag) ((queueFlags) & (bitFlag))

/**
 * Checks the presence of specific queue families in `device` and initializes the fields of `familyIndices` as it does.
 * 
 * Returns whether `device` has enough properties for our usage, that is, if it has a graphics and a present queue family.
 */
static bool identifyQueueFamilies(GpuQueueFamilyIndices *familyIndices, VkQueueFamilyProperties *queueFamilyProperties, u32 queueFamilyCount, VkPhysicalDevice device, VkSurfaceKHR surface) {
  bool foundGraphics = false;
  bool foundPresent = false;
  bool foundTransfer = false;
  bool foundCompute = false;

  for (u32 currentFamilyIndex = 0; currentFamilyIndex < queueFamilyCount; currentFamilyIndex++) {
    VkQueueFlags queueFlags = queueFamilyProperties[currentFamilyIndex].queueFlags;

    if (!foundGraphics && QUEUE_HAS_FLAG(queueFlags, VK_QUEUE_GRAPHICS_BIT)) {
      familyIndices->graphicsIndex = currentFamilyIndex;
      foundGraphics = true;
    }

    if (!foundPresent) {
      VkBool32 supportsPresent = VK_FALSE;
      vkGetPhysicalDeviceSurfaceSupportKHR(device, currentFamilyIndex, surface, &supportsPresent);

      if (supportsPresent) {
        familyIndices->presentIndex = currentFamilyIndex;
        foundPresent = true;
      }
    }

    if (!foundTransfer && QUEUE_HAS_FLAG(queueFlags, VK_QUEUE_TRANSFER_BIT) && !QUEUE_HAS_FLAG(queueFlags, VK_QUEUE_GRAPHICS_BIT)) {
      familyIndices->transferIndex = currentFamilyIndex;
      familyIndices->hasDedicatedTransfer = true;
      foundTransfer = true;
    }

    if (!foundCompute && QUEUE_HAS_FLAG(queueFlags, VK_QUEUE_COMPUTE_BIT) && !QUEUE_HAS_FLAG(queueFlags, VK_QUEUE_GRAPHICS_BIT)) {
      familyIndices->computeIndex = currentFamilyIndex;
      familyIndices->hasDedicatedCompute = true;
      foundCompute = true;
    }
  }

  if (!foundTransfer) {
    familyIndices->transferIndex = familyIndices->graphicsIndex;
    familyIndices->hasDedicatedTransfer = false;
  }

  if (!foundCompute) {
    familyIndices->computeIndex = familyIndices->graphicsIndex;
    familyIndices->hasDedicatedCompute = false;
  }

  return foundGraphics && foundPresent;
}

/**
 * Returns the properties of all queue families of the given `device`, as well as writing the number of
 * families in the `device` to `queueFamilyCount`.
 *
 * The caller is responsible for freeing the returned allocated memory.
 */
static inline VkQueueFamilyProperties *getVkFamilyProperties(VkPhysicalDevice device, u32 *queueFamilyCount) {
  vkGetPhysicalDeviceQueueFamilyProperties(device, queueFamilyCount, NULL);

  VkQueueFamilyProperties *families = malloc(*queueFamilyCount * sizeof(VkQueueFamilyProperties));
  vkGetPhysicalDeviceQueueFamilyProperties(device, queueFamilyCount, families);

  return families;
}

bool findGpuQueueFamilyIndices(VkPhysicalDevice device, VkSurfaceKHR surface, GpuQueueFamilyIndices *familyIndices) {
  u32 queueFamilyCount = 0;
  VkQueueFamilyProperties *queueFamilyProperties = getVkFamilyProperties(device, &queueFamilyCount); 

  const bool deviceIsUsable = identifyQueueFamilies(familyIndices, queueFamilyProperties, queueFamilyCount, device, surface);

  free(queueFamilyProperties);
  return deviceIsUsable;
}

u32 deduplicateQueueFamilyIndices(const GpuQueueFamilyIndices *indices, u32 *deduplicatedIndices) {
  u32 candidates[IDEAL_QUEUE_FAMILY_COUNT] = {
    indices->graphicsIndex,
    indices->presentIndex,
    indices->transferIndex,
    indices->computeIndex,
  };

  u32 uniqueIndexCount = 0;
  for (u32 i = 0; i < IDEAL_QUEUE_FAMILY_COUNT; i++) {
    bool queueFamilyIndexIsAlreadyUsed = false;

    for (u32 j = 0; j < uniqueIndexCount; j++) {
      if (deduplicatedIndices[j] == candidates[i]) {
        queueFamilyIndexIsAlreadyUsed = true;
        break;
      }
    }

    if (!queueFamilyIndexIsAlreadyUsed) {
      deduplicatedIndices[uniqueIndexCount++] = candidates[i];
    }
  }

  return uniqueIndexCount;
}

#undef QUEUE_HAS_FLAG