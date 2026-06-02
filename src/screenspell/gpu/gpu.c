#include "screenspell/gpu/gpu.h"

#include <stdio.h>
#include <stdlib.h>

#include "screenspell/gpu/queue/gpu_queue_indices.h"

/**
 * Expands to `1.0f`, as we always request only one queue per queue family, hence we don't have competing queues and don't need to manage their priorities.
 */
#define DEFAULT_QUEUE_PRIORITY_VALUE 1.0f

/**
 * Creates an individual `VkDeviceQueueCreateInfo` based on the given `queueFamilyIndex` and `priority`.
 * 
 * NOTE: `priority` never changes as we never have competing GPU queues.  See `DEFAULT_QUEUE_PRIORITY_VALUE`.
 */
static inline VkDeviceQueueCreateInfo makeQueueCreateInfo(u32 queueFamilyIndex, f32 *priority) {
  VkDeviceQueueCreateInfo info = {0};
  info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  info.queueFamilyIndex = queueFamilyIndex;
  info.queueCount = 1;
  info.pQueuePriorities = priority;

  return info;
}

/**
 * Populates `queueCreateInfos` with all the necessary `VkDeviceQueueCreateInfo`s based on the available GPU and its available queue families.
 * 
 * Returns how many queue creation infos were made.
 */
static u32 buildQueueCreateInfos(const GpuQueueFamilyIndices *indices, f32 *priority, VkDeviceQueueCreateInfo *queueCreateInfos) {
  u32 deduplicatedIndices[IDEAL_QUEUE_FAMILY_COUNT] = {0};
  const u32 uniqueIndexCount = deduplicateQueueFamilyIndices(indices, deduplicatedIndices);

  for (u32 currentUniqueIndex = 0; currentUniqueIndex < uniqueIndexCount; currentUniqueIndex++) {
    VkDeviceQueueCreateInfo info = makeQueueCreateInfo(deduplicatedIndices[currentUniqueIndex], priority);
    queueCreateInfos[currentUniqueIndex] = info;
  }

  return uniqueIndexCount;
}

/**
 * Left as a static function for future expansion once necessary.
 */
static inline VkPhysicalDeviceFeatures getDeviceFeatures() {
  return (VkPhysicalDeviceFeatures){0};
}

/**
 * Provides the VkDeviceCreateInfo for device creation based on the given arguments.
 */
static inline VkDeviceCreateInfo makeDeviceCreateInfo(VkDeviceQueueCreateInfo *queueCreateInfos, u32 queueCount, VkPhysicalDeviceFeatures *deviceFeatures) {
  VkDeviceCreateInfo createInfo = {0};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  createInfo.pQueueCreateInfos = queueCreateInfos;
  createInfo.queueCreateInfoCount = queueCount;
  createInfo.pEnabledFeatures = deviceFeatures;
  createInfo.enabledExtensionCount = 0;
  createInfo.enabledLayerCount = 0;

  return createInfo;
}

/**
 * Creates the `VkDevice` that will be stored in the `Gpu`.
 * 
 * Returns a `VkResult` based on how the device creation went.
 */
static inline VkResult makeVkDevice(const GpuInfo *gpuInfo, VkDevice *device) {
  float priority = DEFAULT_QUEUE_PRIORITY_VALUE;

  VkDeviceQueueCreateInfo queueCreateInfos[IDEAL_QUEUE_FAMILY_COUNT];
  u32 queueCount = buildQueueCreateInfos(&gpuInfo->queueFamilyIndices, &priority, queueCreateInfos);

  VkPhysicalDeviceFeatures deviceFeatures = getDeviceFeatures();
  VkDeviceCreateInfo createInfo = makeDeviceCreateInfo(queueCreateInfos, queueCount, &deviceFeatures);

  return vkCreateDevice(gpuInfo->physicalGpu, &createInfo, NULL, device);
}

bool initGpu(const GpuInfo *gpuInfo, Gpu *gpu) {
  VkResult deviceCreationResult = makeVkDevice(gpuInfo, &gpu->vkDevice);

  if (deviceCreationResult != VK_SUCCESS) {
    debugLog("Screenspell: failed to create VkDevice (VkResult %d)", deviceCreationResult);
    return false;
  }
  
  GpuQueueGroup queueGroup = makeGpuQueueGroup(gpu->vkDevice, gpuInfo->queueFamilyIndices);
  gpu->queues = queueGroup;

  return true;
}

void freeGpu(Gpu *gpu) { vkDestroyDevice(gpu->vkDevice, NULL); }

#undef DEFAULT_QUEUE_PRIORITY_VALUE