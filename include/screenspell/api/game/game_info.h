#ifndef SCREENSPELL_API_GAME_INFO_H
#define SCREENSPELL_API_GAME_INFO_H

#include "screenspell/common.h"

#include "screenspell/api/version/version.h"

/**
 * The necessary game information for Screenspell, so that it can create a Vulkan instance.
 */
typedef struct {
  const char *name;
  Version version;
} GameInfo;

#endif