#ifndef SCREENSPELL_SWAPCHAIN_INFO_H
#define SCREENSPELL_SWAPCHAIN_INFO_H

#include <vulkan/vulkan.h>

#include "screenspell/common.h"

#include "screenspell/gpu/gpu_info.h"
#include "screenspell/window/surface.h"

/**
 * Carries all the information necessary about the swapchain support.
 * 
 * This is useful for determining an optimal swapchain configuration based on the device.
 */
typedef struct {
  VkSurfaceCapabilitiesKHR surfaceCapabilities;

  VkSurfaceFormatKHR *surfaceFormats;
  u32 surfaceFormatCount;

  VkPresentModeKHR *presentModes;
  u32 presentModeCount;
} SwapchainInfo;

/**
 * Initializes the SwapchainInfo based on the given `gpuInfo`'s `vkDevice` and the `surface`'s `vkSurface`.
 */
bool initSwapchainInfo(const GpuInfo *gpuInfo, const ScreenspellSurface *surface, SwapchainInfo *swapchainInfo);

/**
 * Frees the given `swapchainInfo`.
 */
void freeSwapchainInfo(SwapchainInfo *swapchainInfo);

#endif