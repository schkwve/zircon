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
    UNUSED(argv);

    char *address = malloc(MAX_IP_LENGTH * sizeof(char));
    if (address == NULL) {
        zfatal(-286, "Failed to allocate memory");
        return 1;
    }

    int port = 0;
    char *ip = malloc(64 * sizeof(char));
    char *channel = malloc(64 * sizeof(char));

    if (ip == NULL || channel == NULL) {
        zfatal(-286, "Failed to allocate memory");
        return 1;
    }

    char input_buffer[64];

    printf("Domain to connect to (default: irc.libera.chat): ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
        input_buffer[strcspn(input_buffer, "\n")] = '\0'; 
        if (strlen(input_buffer) > 0) {
            strncpy(ip, input_buffer, 63);
            ip[63] = '\0';
        } else {
            strncpy(ip, "irc.libera.chat", 64);
        }
    }

    printf("Port to connect to (default: 6667): ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
        input_buffer[strcspn(input_buffer, "\n")] = '\0'; 
        if (strlen(input_buffer) > 0) {
            port = atoi(input_buffer);
        } else {
            port = 6667;
        }
    }

    printf("Channel to join (default: #aurixos): ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
        input_buffer[strcspn(input_buffer, "\n")] = '\0'; 
        if (strlen(input_buffer) > 0) {
            strncpy(channel, input_buffer, 63);
            channel[63] = '\0';
        } else {
            strncpy(channel, "#aurixos", 64);
        }
    }

    register_handlers();

    if (atexit(die) != 0) {
        zerr(0, "Failed to register exit handler");
        return 1;
    }

    if (resolve_hostname(ip, address, MAX_IP_LENGTH) != 0) {
        zerr(0, "Failed to resolve hostname");
        return 1;
    }

    zinfo("Connecting to %s:%d", address, port);

    load_config();

    irc_connect_to(address, port, channel);

    while (1) {
        char* buffer = (char*)malloc(1024);
        if (buffer == NULL) {
            zerr(0, "Failed to allocate memory");
            break;
        }
        if (fgets(buffer, 1024, stdin) != NULL) { /* Avoid buffer overflow */
            if (strstr(buffer, "exit") != NULL) {
                free(buffer);
                break;
            }
        }
        free(buffer);
    }

    irc_disconnect();

    zinfo("Disconnected from %s:%d", address, port);
    zinfo("Done");

    free(address);
    free(ip);
    free(channel);

    return 0;
}


void die(void) {
    irc_send("QUIT :Client is shutting down\r\n");
    zsucc("Sent QUIT command to server");
    irc_disconnect();
    free_config();
    zsucc("Freed memory and disconnected from server");
}
