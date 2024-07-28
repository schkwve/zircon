#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <config.h>
#include <irc/commands.h>
#include <irc/connect.h>
#include <network/connect.h>
#include <utils/zerr.h>

/* *** *** *** ** *** *** */
/*  IMPLEMENTATION NOTES  */
/* *** *** *** ** *** *** */
/* */

void irc_connect_to(const char *server_address, uint16_t server_port)
{
  /* connect to the server via TCP */
  connect_server(server_address, server_port);

  /* what capabilities do you have, kind server? */
  irc_capls(IRC_VER302);
  /*irc_recv(&response_buffer, 512);*/

  /* identify ourselves */
  irc_nick(config_get_nickname());
  irc_user(config_get_username(), config_get_fullname());

  /* jk i don't care anyway, fuck you */
  irc_capend();

  /* TODO: check if we have a PING we can PONG to */
}

void irc_disconnect()
{
  close_server_connection();
}

int irc_send(const char *buffer)
{
  size_t size = strlen(buffer);
  if (size < 1) {
    zerr("The buffer cant be empty");
    return -1;
  }

  return send_data_to_server(buffer);
}

int irc_recv(char **buffer, size_t size)
{
  if (size < 1) {
    zerr("The read size cant be 0!");
    return -1;
  }

  bzero(*buffer, sizeof(buffer));
  return recv_data_from_server(buffer, size);
}