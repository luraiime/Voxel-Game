#ifndef SCREENSPELL_INSTANCE_H
#define SCREENSPELL_INSTANCE_H

#include <vulkan/vulkan.h>

#include "screenspell/common.h"

#include "screenspell/api/game/game_info.h"

/**
 * A wrapper around a `vkInstance`.
 * 
 * The contained `vkInstance` stores information about the game (provided by `gameInfo` in `initScreenspellInstance`), 
 * as well as information about the engine itself (see `screenspell/engine.h`).
 */
typedef struct {
  VkInstance vkInstance;
} ScreenspellInstance;

/**
 * Initializes the given `instance` based on the provided `gameInfo`.
 * 
 * Returns whether the initialization was successful.
 */
bool initScreenspellInstance(GameInfo gameInfo, ScreenspellInstance *instance);

/**
 * Frees the `vkInstance` stored in `instance`.
 */
void freeScreenspellInstance(ScreenspellInstance *instance);

#endif