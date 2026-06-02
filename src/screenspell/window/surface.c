#include "screenspell/window/surface.h"

bool initSurface(const Window *window, const ScreenspellInstance *instance, ScreenspellSurface *surface) {
  return glfwCreateWindowSurface(instance->vkInstance, window->glfwWindow, NULL, &surface->vkSurface) == VK_SUCCESS;
}

void freeSurface(const ScreenspellInstance *instance, ScreenspellSurface *surface) {
  vkDestroySurfaceKHR(instance->vkInstance, surface->vkSurface, NULL);
}