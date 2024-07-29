#include <config.h>
#include <irc/connect.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <zircon.h>
#include <utils/zerr.h>
#include <utils/signals.h>
#include <utils/internet.h>
#include <stdlib.h>

void die(void);

int main(int argc, char** argv) {

    UNUSED(argc);

    char *address = malloc(16 * sizeof(char));
    int port = 0000;
    char *ip = malloc(64 * sizeof(char));
    char *channel = malloc(64 * sizeof(char));

    if (address == NULL) {
        zfatal(-286, "Failed to allocate memory");
        return 1;
    }
    
    if (argv[1] == NULL) {
        char *scanf_buffer = malloc(64 * sizeof(char));
        if (scanf_buffer == NULL) {
            zfatal(-286, "Failed to allocate memory");
            return 1;
        }
        zinfo("Adress (default: irc.libera.chat): ");
        scanf("%63s", scanf_buffer);
        if (scanf_buffer[0] == '\0') {
            strncpy(ip, "irc.libera.chat", 16);
        } else {
            strncpy(ip, scanf_buffer, 16);
        }
        free(scanf_buffer);
    }

    if (argv[2] == NULL) {
        zinfo("Port (default: 6667): ");
        scanf("%d", &port);
    } else {
        port = atoi(argv[2]);
    }

    if (argv[3] == NULL) {
        char *buffer = malloc(64 * sizeof(char));
        zinfo("Channel (default: #aurixos): ");
        scanf("%63s", buffer);
        if (buffer[0] == '\0') {
            strncpy(buffer, "#aurixos", 64);
        }
        strncpy(channel, buffer, 64);
        free(buffer);
    }

    register_handlers();

    if (atexit(die) != 0) {
        zerr(0, "Failed to register exit handler");
        return 1;
    }

    resolve_hostname(ip, address, MAX_IP_LENGTH);

    zinfo("Connecting to %s:%d", address, port);

    load_config();

    /* Everything must be loaded from here on */

    /* Assume we want to connect to localhost @ 6667 */
    irc_connect_to(address, port, channel);

    while (1) {
        char* buffer = (char*)malloc(1024);
        if (buffer == NULL) {
            zerr(0, "Failed to allocate memory");
            break;
        }
        scanf("%1023s", buffer); /* Avoid buffer overflow */
        if (strstr(buffer, "exit") != NULL) {
            free(buffer);
            break;
        }
        free(buffer);
    }

    irc_disconnect();

    zinfo("Disconnected from %s:%d", address, port);
    zinfo("Done");

    return 0;
}

void die(void) {
    irc_disconnect();
    free_config();
    zsucc("Freed memory and disconnected from server");
}
