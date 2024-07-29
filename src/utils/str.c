#include <utils/str.h>

#include <string.h>
#include <stdlib.h>

char *z_strdup(const char *src)
{
	size_t len = strlen(src);
	char *ret = malloc(len + sizeof(char));
	memcpy(ret, src, len);
	return ret;
}

ssize_t z_readlink(const char *path, char *buf, size_t bufsize) {
    int fd;
    ssize_t len;

    /* Open Symlink */
    fd = open(path, O_RDONLY | 00400000);
    if (fd == -1) {
        zerr("couldnt open %s for readlink: ", path);
        return -1;
    }

    /* Read the target */
    len = read(fd, buf, bufsize - 1);
    if (len == -1) {
        zerr("couldnt read %s for readlink: ", path);
        close(fd);
        return -1;
    }

    /* Null terminate the result */
    buf[len] = '\0';

    /* cleanup */
    close(fd);
    return len;
}

void z_strstrip(char *str, int num_chars) {
    int len = strlen(str);

    if (len >= num_chars) {
        str[len - num_chars] = '\0';
    } else {
        str[0] = '\0'; 
    }
}