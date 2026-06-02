#ifndef SCREENSPELL_WINDOW_H
#define SCREENSPELL_WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "screenspell/common.h"

/**
 * A wrapper around a `GLFWwindow`, along with additional information such as the window's width and height.
 */
typedef struct {
  GLFWwindow *glfwWindow;

  const char *title;
  u32 width;
  u32 height;
} Window;

/**
 * Initializes GLFW and creates a new `Window` based on the provided arguments, writing it to `window`.
 * 
 * Returns whether the `GLFWwindow` creation was successful.
 */
bool initWindow(u32 width, u32 height, const char *title, Window *window);

/**
 * Frees the given `window` and terminates GLFW.
 */
void freeWindow(Window *window);

#endif