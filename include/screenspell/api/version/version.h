#ifndef SCREENSPELl_API_VERSION_H
#define SCREENSPELL_API_VERSION_H

#include "screenspell/common.h"

/**
 * Screenspell version information, following SemVer conventions.
 */
typedef struct {
  u32 major;
  u32 minor;
  u32 patch;
} Version;

/**
 * Expands to a Version struct creation based on the provided macro arguments.
 */
#define SCREENSPELL_MAKE_VERSION(major, minor, patch) (Version){major, minor, patch};

/**
 * Transforms a Screenspell Version struct into a `u32` that Vulkan can read using `VK_MAKE_VERSION`.
 */
#define SCREENSPELl_VERSION_TO_VK_VERSION(version) VK_MAKE_VERSION(version.major, version.minor, version.patch)

#endif