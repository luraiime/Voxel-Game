#include "screenspell/instance/instance.h"

#include "screenspell/api/game/game_info.h"

#include "screenspell/common.h"
#include "screenspell/engine.h"

#include "screenspell/log/log.h"

#include <stdio.h>

#include <GLFW/glfw3.h>

/**
 * Returns all required extensions for GLFW as constant strings and writes the number of those extensions to `extensionCount`.
 */
static inline const char **getGlfwExtensions(u32 *extensionCount) {
  const char **glfwExtensions = glfwGetRequiredInstanceExtensions(extensionCount);
  return glfwExtensions;
}

/**
 * Creates the Vulkan application info with the game's name and the engine's name.
 */
static inline VkApplicationInfo makeVkApplicationInfo(GameInfo gameInfo) {
  VkApplicationInfo appInfo = {0};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = gameInfo.name;
  appInfo.applicationVersion = SCREENSPELL_VERSION_TO_VK_VERSION(gameInfo.version);
  appInfo.pEngineName = SCREENSPELL_ENGINE_NAME;
  appInfo.engineVersion = SCREENSPELL_ENGINE_VERSION_FOR_VK;
  appInfo.apiVersion = VK_API_VERSION_1_3;

  return appInfo;
}

/**
 * Creates a `VkInstanceCreateInfo` necessary for Vulkan instance creation, based on the given `appInfo`.
 * 
 */
static inline VkInstanceCreateInfo makeVkCreateInfo(const VkApplicationInfo *appInfo) {
  u32 glfwExtensionCount;
  const char **glfwExtensions = getGlfwExtensions(&glfwExtensionCount);

  VkInstanceCreateInfo createInfo = {0};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = appInfo;
  createInfo.enabledExtensionCount = glfwExtensionCount;
  createInfo.ppEnabledExtensionNames = glfwExtensions;
  createInfo.enabledLayerCount = 0;

  return createInfo;
}

/**
 * Creates a VkInstance based on the provided `gameInfo` and writes it to `instance`.
 * 
 * Returns a `VkResult` based on how the instance creation went.
 */
static inline VkResult initVkInstance(GameInfo gameInfo, VkInstance *instance) {
  const VkApplicationInfo appInfo = makeVkApplicationInfo(gameInfo);
  const VkInstanceCreateInfo createInfo = makeVkCreateInfo(&appInfo);

  return vkCreateInstance(&createInfo, NULL, instance);
}

bool initRenderInstance(GameInfo gameInfo, ScreenspellInstance *instance) {
  const VkResult createInstanceResult = initVkInstance(gameInfo, &instance->vkInstance);

  if (createInstanceResult != VK_SUCCESS) {
    debugLog("Screenspell: failed to create Vulkan instance (VkResult %d)", createInstanceResult);
    return false;
  }

  return true;
}

void freeRenderInstance(ScreenspellInstance *instance) {
  vkDestroyInstance(instance->vkInstance, NULL);
}