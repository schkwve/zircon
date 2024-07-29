#ifndef _UTILS_ZERR_H
#define _UTILS_ZERR_H

/* ASCII escape codes for color and sytle */
#define ZERR_COLOR_RED "\x1b[31m"
#define ZERR_COLOR_GREEN "\x1b[32m"
#define ZERR_COLOR_YELLOW "\x1b[33m"
#define ZERR_COLOR_BLUE "\x1b[34m"
#define ZERR_COLOR_MAGENTA "\x1b[35m"
#define ZERR_COLOR_CYAN "\x1b[36m"
#define ZERR_COLOR_RESET "\x1b[0m"
#define ZERR_STYLE_BOLD "\x1b[1m"

void
zinfo(const char* fmt, ...);
void
zwarn(const char* fmt, ...);
void
zerr(int perrno, const char* fmt, ...);
void
zfatal(int err_code, const char* fmt, ...);
void
zsucc(const char* fmt, ...);
void
zircmsg(const char* fmt, ...);
void
zircwarn(const char* fmt, ...);

#endif /* _UTILS_ZERR_H */