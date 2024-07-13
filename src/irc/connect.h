#ifndef _IRC_CONNECT_H
#define _IRC_CONNECT_H

#include <stdint.h>

void irc_connect_to(const char *server_address, uint16_t server_port);
void irc_disconnect();

#endif /* _IRC_CONNECT_H */