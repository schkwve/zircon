#ifndef _NETWORK_CONNECT_H
#define _NETWORK_CONNECT_H

#include <stddef.h>
#include <stdint.h>

void connect_server(const char *server_address, uint16_t server_port);
void close_server_connection(void);

int send_data_to_server(const char *buffer);
int recv_data_from_server(char **buffer, size_t size);

#endif /* _NETWORK_CONNECT_H */