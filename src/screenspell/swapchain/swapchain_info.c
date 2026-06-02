#include "screenspell/swapchain/swapchain_info.h"

static inline void initSwapchainInfoSurfaceCapabilities(VkPhysicalDevice physicalGpu, VkSurfaceKHR vkSurface, SwapchainInfo *swapchainInfo) {
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalGpu, vkSurface, &swapchainInfo->surfaceCapabilities);
}

static bool initSwapchainInfoSurfaceFormatCount()

bool initSwapchainInfo(const GpuInfo *gpuInfo, const ScreenspellSurface *surface, SwapchainInfo *swapchainInfo) {
  initSwapchainInfoSurfaceCapabilities(gpuInfo->physicalGpu, surface->vkSurface, swapchainInfo);

  vkGetPhysicalDeviceSurfaceFormatsKHR(gpuInfo->physicalGpu, surface->vkSurface, &swapchainInfo->formatCount, NULL);
  swapchainInfo->formats = malloc(sizeof(VkSurfaceFormatKHR) * swapchainInfo->formatCount);
  vkGetPhysicalDeviceSurfaceFormatsKHR(gpuInfo->physicalGpu, surface->vkSurface, &swapchainInfo->formatCount, swapchainInfo->formats);

  vkGetPhysicalDeviceSurfacePresentModesKHR(gpuInfo->physicalGpu, surface->vkSurface, &swapchainInfo->presentModeCount, NULL);
  swapchainInfo->presentModes = malloc(sizeof(VkSurfaceFormatKHR) * swapchainInfo->presentModeCount);
  vkGetPhysicalDeviceSurfacePresentModesKHR(gpuInfo->physicalGpu, surface->vkSurface, &swapchainInfo->presentModeCount, swapchainInfo->presentModes);
}

void freeSwapchainInfo(SwapchainInfo *swapchainInfo) {

}