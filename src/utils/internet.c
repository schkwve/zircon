#include <utils/internet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <utils/zerr.h>

#define MAX_IP_LENGTH 16  /* IPv4 addr xxx.xxx.xxx.xxx + null terminator */

int resolve_hostname(const char *hostname, char *ip_buffer, size_t buffer_size) {
    struct hostent *he;
    struct in_addr **addr_list;
    char *ip;
    
    if (buffer_size < MAX_IP_LENGTH) {
        zerr(0, "Buffer size is too small to store IP address");
        return -1;
    }

    he = gethostbyname(hostname);
    if (he == NULL) {
        zerr(0, "Failed to resolve hostname");
        return -1;
    }

    addr_list = (struct in_addr **)he->h_addr_list;

    if (addr_list[0] == NULL) {
        zerr(0, "Failed to resolve hostname to IP address!");
        return -1;
    }

    ip = inet_ntoa(*addr_list[0]);
    if (ip == NULL) {
        zerr(0, "Failed to convert IP address to string!");
        return -1;
    }

    strncpy(ip_buffer, ip, buffer_size - 1);

    ip_buffer[buffer_size - 1] = '\0';

    return 0;  
}
