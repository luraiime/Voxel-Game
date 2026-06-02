#ifndef SCREENSPELL_LOG_H
#define SCREENSPELL_LOG_H

/**
 * Formats `message` using vfprintf on it and the given additional variadic arguments. 
 * 
 * The formatted message is output to STDERR, after which is written a single newline character.
 */
void debugLog(const char *message, ...);

#endif