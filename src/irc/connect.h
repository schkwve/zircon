#ifndef _IRC_CONNECT_H
#define _IRC_CONNECT_H

#include <stddef.h>
#include <stdint.h>

void
irc_connect_to(const char* server_address, uint16_t server_port);
void
irc_disconnect();

int
irc_send(char* buffer);
int
irc_recv(char** buffer, size_t size);

#endif /* _IRC_CONNECT_H */