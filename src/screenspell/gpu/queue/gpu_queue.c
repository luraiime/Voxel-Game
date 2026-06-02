#include "screenspell/gpu/queue/gpu_queue.h"

static inline void setGpuQueues(VkDevice device, GpuQueueFamilyIndices queueFamilyIndices, GpuQueueGroup *queueGroup) {
  vkGetDeviceQueue(device, queueFamilyIndices.graphicsIndex, 0, &queueGroup->graphics.queue);
  queueGroup->graphics.familyIndex = queueFamilyIndices.graphicsIndex;

  vkGetDeviceQueue(device, queueFamilyIndices.presentIndex, 0, &queueGroup->present.queue);
  queueGroup->present.familyIndex = queueFamilyIndices.presentIndex;

  vkGetDeviceQueue(device, queueFamilyIndices.transferIndex, 0, &queueGroup->transfer.queue);
  queueGroup->transfer.familyIndex = queueFamilyIndices.transferIndex;

  vkGetDeviceQueue(device, queueFamilyIndices.computeIndex, 0, &queueGroup->compute.queue);
  queueGroup->compute.familyIndex = queueFamilyIndices.computeIndex;
}

GpuQueueGroup makeGpuQueueGroup(VkDevice device, GpuQueueFamilyIndices queueFamilyIndices) {
  GpuQueueGroup queueGroup = {0};
  setGpuQueues(device, queueFamilyIndices, &queueGroup);

  return queueGroup;
}