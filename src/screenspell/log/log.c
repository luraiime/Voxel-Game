#include "screenspell/log/log.h"

#include <stdarg.h>
#include <stdio.h>

void debugLog(const char *message, ...) {
  va_list args;
  va_start(args, message);

  vfprintf(stderr, message, args);

  va_end(args);
  fputc('\n', stderr);
}