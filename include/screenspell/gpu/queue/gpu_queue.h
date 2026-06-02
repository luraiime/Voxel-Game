#ifndef SCREENSPELL_GPU_QUEUE_H
#define SCREENSPELL_GPU_QUEUE_H

#include <vulkan/vulkan.h>

#include "screenspell/common.h"

#include "screenspell/gpu/queue/gpu_queue_indices.h"

/**
 * A live GPU queue.
 * 
 * The `familyIndex` remains stored as some Vulkan calls may need it even after the queue is created.
 */
typedef struct {
  VkQueue queue;
  u32 familyIndex;
} GpuQueue;

/**
 * Stores all four GPU queues that may be used by Screenspell.
 */
typedef struct {
  GpuQueue graphics;
  GpuQueue present;

  /**
   * NOTE: This queue can be the same as `graphics` if no dedicated transfer queue exists.
   */
  GpuQueue transfer;

  /**
   * NOTE: This queue can be the same as `graphics` if no dedicated transfer queue exists.
   */
  GpuQueue compute;
} GpuQueueGroup;

GpuQueueGroup makeGpuQueueGroup(const VkDevice device, const GpuQueueFamilyIndices familyIndices);

#endif