#ifndef _UTILS_STR_H
#define _UTILS_STR_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <utils/zerr.h>

#define MAX_PATH_LENGHT 1024 /* for z_readlink */

char*
z_strdup(const char* src);
ssize_t
z_readlink(const char* path, char* buf, size_t bufsize);
void
z_strstrip(char* str, int chars_to_remove);

#endif /* _UTILS_STR_H */
