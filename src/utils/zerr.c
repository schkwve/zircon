#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils/zerr.h>
#include <zircon.h>

void
zinfo(const char* fmt, ...)
{
	va_list args;

	printf("%s%s[INFO]:%s ", ZERR_COLOR_BLUE, ZERR_STYLE_BOLD, ZERR_COLOR_RESET);

	/* Init the va list */
	va_start(args, fmt);

	/* Use vprintf to print the valist */
	vprintf(fmt, args);
	printf("\n");

	/* Cleanup */
	va_end(args);
}

void
zwarn(const char* fmt, ...)
{
	va_list args;

	printf(
		"%s%s[WARN]:%s ", ZERR_COLOR_YELLOW, ZERR_STYLE_BOLD, ZERR_COLOR_RESET);

	/* Init the va list */
	va_start(args, fmt);

	/* Use vprintf to print the valist */
	vprintf(fmt, args);
	printf("\n");

	/* Cleanup */
	va_end(args);
}

void
zerr(const char* fmt, ...)
{
	va_list args;

	printf("%s%s[ERR]:%s ", ZERR_COLOR_RED, ZERR_STYLE_BOLD, ZERR_COLOR_RESET);

	/* Init the va list */
	va_start(args, fmt);

	/* Use vprintf to print the valist */
	vprintf(fmt, args);
	perror(NULL);
	printf("\n");

	/* Cleanup */
	va_end(args);
}

void
zfatal(int err_code, const char* fmt, ...)
{
	va_list args;

	printf("%s%s[FATAL@CODE %d]: ", ZERR_COLOR_RED, ZERR_STYLE_BOLD, err_code);

	/* Init the va list */
	va_start(args, fmt);

	/* Use vprintf to print the valist */
	vprintf(fmt, args);
	perror(NULL);
	printf("%s", ZERR_COLOR_RESET);
	printf("\n");

	/* Cleanup */
	va_end(args);

	exit(1);
}

void
zsucc(const char* fmt, ...)
{
	va_list args;

	printf(
		"%s%s[SUCCESS]:%s ", ZERR_COLOR_GREEN, ZERR_STYLE_BOLD, ZERR_COLOR_RESET);

	/* Init the va list */
	va_start(args, fmt);

	/* Use vprintf to print the valist */
	vprintf(fmt, args);
	printf("\n");

	/* Cleanup */
	va_end(args);
}

void
zircmsg(const char* fmt, ...)
{
	va_list args;

	printf(
		"%s%s[IRC]:%s ", ZERR_COLOR_MAGENTA, ZERR_STYLE_BOLD, ZERR_COLOR_RESET);

	/* Init the va list */
	va_start(args, fmt);

	/* Use vprintf to print the valist */
	vprintf(fmt, args);
	printf("\n");

	/* Cleanup */
	va_end(args);
}

void
zircwarn(const char* fmt, ...)
{
	va_list args;

	printf(
		"%s%s[IRC-WARN]:%s ", ZERR_COLOR_CYAN, ZERR_STYLE_BOLD, ZERR_COLOR_RESET);

	/* Init the va list */
	va_start(args, fmt);

	/* Use vprintf to print the valist */
	vprintf(fmt, args);
	printf("\n");

	/* Cleanup */
	va_end(args);
}