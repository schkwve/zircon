#ifndef _UTILS_STR_H
#define _UTILS_STR_H

#include <stddef.h>
#include <sys/types.h>

#define MAX_PATH_LENGHT 1024 /* for z_readlink */

char*
z_strdup(const char* src);

ssize_t
z_readlink(const char* path, char* buf, size_t bufsize);

void
z_strstrip(char* str, int num_chars);

#endif /* _UTILS_STR_H */
