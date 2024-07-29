#ifndef _UTILS_STR_H
#define _UTILS_STR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <utils/zerr.h>

#define MAX_PATH_LENGHT 1024 /* for z_readlink */

char *z_strdup(const char *src);
ssize_t z_readlink(const char *path, char *buf, size_t bufsize);

#endif /* _UTILS_STR_H */
