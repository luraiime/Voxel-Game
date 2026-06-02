#ifndef SCREENSPELL_GPU_H
#define SCREENSPELL_GPU_H

#include <vulkan/vulkan.h>

#include "screenspell/gpu/queue/gpu_queue.h"
#include "screenspell/gpu/gpu_info.h"

/**
 * A live GPU struct.
 * 
 * It contains a `VkDevice` and a `GpuQueueGroup` with all necessary queues.
 */
typedef struct {
  VkDevice vkDevice;

  GpuQueueGroup queues;
} Gpu;

/**
 * Initializes a new live GPU based on the given `gpuInfo`.
 */
bool initGpu(const GpuInfo *gpuInfo, Gpu *gpu);

/**
 * Frees the `vkDevice` stored in the `gpu`. 
 */
void freeGpu(Gpu *gpu);

#endif