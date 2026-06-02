#ifndef SCREENSPELL_WINDOW_SURFACE_H
#define SCREENSPELL_WINDOW_SURFACE_H

#include <vulkan/vulkan.h>

#include "screenspell/common.h"
#include "screenspell/window/window.h"
#include "screenspell/instance/instance.h"

/**
 * A wrapper around a `VkSurfaceKHR`.
 * 
 * Represents the Vulkan surface associated with a `Window`, used to interface
 * between the Vulkan instance and the platform's windowing system.
 */
typedef struct {
  VkSurfaceKHR vkSurface;
} ScreenspellSurface;

/**
 * Creates a Vulkan surface for the given `window` and writes it to `surface`.
 *
 * Returns whether the surface creation was successful.
 */
bool initSurface(const Window *window, const ScreenspellInstance *instance, ScreenspellSurface *surface);

/**
 * Frees the given `surface`.
 */
void freeSurface(const ScreenspellInstance *instance, ScreenspellSurface *surface);

#endif