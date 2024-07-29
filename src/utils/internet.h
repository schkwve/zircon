#ifndef _UTILS_INTERNET_H
#define _UTILS_INTERNET_H

#include <stddef.h>

#define MAX_IP_LENGTH 16

int resolve_hostname(const char *hostname, char *ip_buffer, size_t buffer_size);

#endif /* _UTILS_INTERNET_H */