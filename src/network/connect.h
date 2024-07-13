#ifndef _NETWORK_CONNECT_H
#define _NETWORK_CONNECT_H

#include <stdint.h>

void connect_server(const char *server_address, uint16_t server_port);
void close_server_connection(void);

#endif /* _NETWORK_CONNECT_H */