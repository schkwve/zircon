#ifndef _NETWORK_SERVER_INFO_H
#define _NETWORK_SERVER_INFO_H

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

#endif /* _NETWORK_SERVER_INFO_H */