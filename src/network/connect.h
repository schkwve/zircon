#ifndef _NETWORK_CONNECT_H
#define _NETWORK_CONNECT_H

#include <stdbool.h>
#include <stdint.h>

struct irc_server_info
{
  char *address;
  uint16_t port;

  int sockfd;
  int connfd;
  bool is_connected;
};

void connect_server(const char *server_address, uint16_t server_port);
void close_server_connection(void);

#endif /* _NETWORK_CONNECT_H */