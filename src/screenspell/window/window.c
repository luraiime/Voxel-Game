#include "screenspell/window/window.h"

/**
 * Sets the GLFW window hints.  In particular:
 * 
 * - It tells GLFW not to create an OpenGL context, as we're using Vulkan
 * - It disables window resizing (for now).
 */
static inline void setGlfwWindowHints() {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

/**
 * Creates a new GLFW window, assuming GLFW is already initialized.
 * 
 * This function does not check whether `**glfwWindow` is `NULL` before dereferencing it.  It also does not
 * check whether GLFW is already initialized.
 * 
 * Returns whether the window creation was successful.
 * 
 * The caller is responsible for managing the allocated memory written to `glfwWindow`.
 */
static inline bool initGlfwWindow(u32 width, u32 height, const char *title, GLFWwindow **glfwWindow) {
  *glfwWindow = glfwCreateWindow((i32)width, (i32)height, title, NULL, NULL);
  return *glfwWindow != NULL;
}

bool initWindow(u32 width, u32 height, const char *title, Window *window) {
  if (!glfwInit()) {
    return false;
  }

  setGlfwWindowHints();

  const bool glfwWindowCreationWasSuccessful = initGlfwWindow(width, height, title, &window->glfwWindow);
  if (!glfwWindowCreationWasSuccessful) {
    glfwTerminate();
    return false;
  }

  window->title = title;
  window->width = width;
  window->height = height;

  return true;
}

void freeWindow(Window *window) {
  glfwDestroyWindow(window->glfwWindow);
  glfwTerminate();
}