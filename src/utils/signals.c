#include <utils/signals.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <config.h>
#include <irc/connect.h>
#define PATH_MAX 4096

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>
#include <string.h>
#include <utils/zerr.h>
#include <utils/str.h>


#define MAX_FRAMES 10

void print_stacktrace() {
    void *frames[MAX_FRAMES];
    int frame_count;
    char **symbols;
    int i;

    frame_count = backtrace(frames, MAX_FRAMES);
    symbols = backtrace_symbols(frames, frame_count);

    if (symbols) {
        for (i = 1; i < frame_count; i++) {
            printf("\t%s\n", symbols[i]);
        }
        free(symbols);
    }
} 

void common_exit() {
    irc_disconnect();
    zsucc("Freed memory and disconnected from server");
}



void sigint_handler() {
    zerr("SIGINT caught: quitting!");
    common_exit();
    zerr("Backtrace: ");
    print_stacktrace();
    exit(0);
}

void sigsegv_handler() {
    zerr("SIGSEV caught: quitting!");
    common_exit();
    zerr("Backtrace: ");
    print_stacktrace();
    exit(0);
}

void register_handlers() {
    signal(SIGINT, sigint_handler);
    signal(SIGSEGV, sigsegv_handler);
}