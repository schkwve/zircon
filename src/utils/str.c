#include <string.h>
#include <stdlib.h>

char *z_strdup(const char *src)
{
	size_t len = strlen(src);
	char *ret = malloc(len * sizeof(char));
	memcpy(ret, src, len);
	return ret;
}