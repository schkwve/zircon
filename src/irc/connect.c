
#include <config.h>
#include <irc/commands.h>
#include <irc/connect.h>
#include <irc/negotiation.h>
#include <network/connect.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <utils/str.h>
#include <utils/zerr.h>

void
irc_connect_to(const char* server_address, uint16_t server_port, const char* channel)
{
  char* buffer = malloc(1024);

  connect_server(server_address, server_port);
  irc_nick(config_get_nickname());
  irc_user(config_get_username(), config_get_fullname());
  irc_recv(&buffer, 1024);
  printf("%s\n", buffer);
  irc_recv(&buffer, 1024);
  printf("%s\n", buffer);
  irc_recv(&buffer, 1024);
  printf("%s\n", buffer);
  irc_recv(&buffer, 1024);
  printf("%s\n", buffer);
  irc_recv(&buffer, 1024);
  printf("%s\n", buffer);
  irc_recv(&buffer, 1024);
  printf("%s\n", buffer);
  irc_join_channel(channel);

  /* TODO: check if we have a PING we can PONG to */
}

void
irc_disconnect()
{
  close_server_connection();
}

int
irc_send(char* buffer)
{
  size_t size = strlen(buffer);
  if (size < 1) {
    zerr(0, "The buffer cant be empty");
    return -1;
  }

  char* pbuf = malloc(256); /* TODO: Fix this shit */
  strcpy(pbuf, buffer);
  z_strstrip(pbuf, 2);
  zircmsg("Send message '%s' to the server.", pbuf);

  return send_data_to_server(buffer);
}

int
irc_recv(char** buffer, size_t size)
{
  if (size < 1) {
    zerr(0, "Read size cant be 0!");
    return -1;
  }

  /* Alloc memory for the buffer so that it *hopefully* doesnt segfault */
  *buffer = (char*)malloc(size);
  if (*buffer == NULL) {
    zfatal(-281, "Could not allocate buffer to recv from the server:");
    return -1;
  }

  bzero(*buffer, size);

  return recv_data_from_server(buffer, size);
}
