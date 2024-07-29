#include <config.h>
#include <execinfo.h>
#include <irc/connect.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utils/signals.h>
#define PATH_MAX 4096

#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils/str.h>
#include <utils/zerr.h>

#define MAX_FRAMES 10

void
print_stacktrace()
{
	void* frames[MAX_FRAMES];
	int frame_count;
	char** symbols;
	int i;

	frame_count = backtrace(frames, MAX_FRAMES);
	symbols = backtrace_symbols(frames, frame_count);

	if (symbols) {
		for (i = 1; i < frame_count; i++) { printf("  %s\n", symbols[i]); }
		free(symbols);
	}
}

void
sigint_handler()
{
	zerr("SIGINT caught: quitting!");
	zerr("Backtrace: ");
	print_stacktrace();
	exit(0);
}

void
sigsegv_handler()
{
	zerr("SIGSEGV caught: quitting!");
	zerr("Backtrace: ");
	print_stacktrace();
	exit(0);
}

void
sigabrt_handler()
{
	zerr("SIGABRT caught: quitting!");
	zerr("Backtrace: ");
	print_stacktrace();
	exit(0);
}

void
register_handlers()
{
	signal(SIGINT, sigint_handler);
	signal(SIGSEGV, sigsegv_handler);
	signal(SIGABRT, sigabrt_handler);
}