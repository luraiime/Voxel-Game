#include "screenspell/gpu/gpu_info.h"

#include "screenspell/log/log.h"

#include <stdlib.h>

/**
 * Finds the list of all Vulkan-capable GPUs and writes them to `physicalGpus`.  Writes the number of GPUs
 * into `gpuCount`.
 * 
 * Returns whether a Vulkan-capable GPU was found.
 */
static bool findVkCapableGpus(VkInstance instance, VkPhysicalDevice **physicalGpus, u32 *gpuCount) {
  vkEnumeratePhysicalDevices(instance, gpuCount, NULL);

  if (*gpuCount == 0) {
    return false;
  }

  *physicalGpus = malloc(*gpuCount * sizeof(VkPhysicalDevice));
  vkEnumeratePhysicalDevices(instance, gpuCount, *physicalGpus);

  return true;
}

/**
 * Finds the first usable GPU in the list of `physicalGpus`, that is, the first GPU to have both a graphics and present queue. 
 * If found, the found GPU's info is written to `gpuInfo`.
 * 
 * Returns whether a usable GPU was found or not.
 */
static bool findUsableGpuInfo(VkPhysicalDevice *physicalGpus, u32 gpuCount, VkSurfaceKHR surface, GpuInfo *gpuInfo) {
  for (u32 currentPhysicalGpuIndex = 0; currentPhysicalGpuIndex < gpuCount; currentPhysicalGpuIndex++) {
    GpuQueueFamilyIndices queueFamilyIndices = {0};
    VkPhysicalDevice physicalGpu = physicalGpus[currentPhysicalGpuIndex];

    const bool gpuIsUsable = findGpuQueueFamilyIndices(physicalGpu, surface, &queueFamilyIndices);
    if (gpuIsUsable) {
      gpuInfo->physicalGpu = physicalGpu;
      gpuInfo->queueFamilyIndices = queueFamilyIndices;
      return true;
    }
  }

  return false;
}

bool initGpuInfo(const ScreenspellInstance *instance, VkSurfaceKHR surface, GpuInfo *gpuInfo) {
  u32 gpuCount = 0;
  VkPhysicalDevice *physicalGpus;
  const bool vkCapableGpuIsAvailable = findVkCapableGpus(instance->vkInstance, &physicalGpus, &gpuCount);

  if (!vkCapableGpuIsAvailable) {
    debugLog("Screenspell: no Vulkan-capable GPU was found!");
    return false;
  }

  const bool foundUsableGpu = findUsableGpuInfo(physicalGpus, gpuCount, surface, gpuInfo);
  free(physicalGpus);

  if (!foundUsableGpu) {
    debugLog("Screenspell: no suitable GPU found!");
    return false;
  }

  return true;
}