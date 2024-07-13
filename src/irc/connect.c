#include <network/connect.h>
#include <stdint.h>

/* *** *** *** ** *** *** */
/*  IMPLEMENTATION NOTES  */
/* *** *** *** ** *** *** */
/* */

void irc_connect_to(const char *server_address, uint16_t server_port)
{
  /* connect to the server via TCP */
  connect_server(server_address, server_port);

  /* identify ourselves */
  /* NICK <nickname> */
  /* irc_nick(config_get_nickname()); */
  /* USER <username> 0 * <realname> */
  /* irc_user(config_get_username(), config_get_realname()); */
}

void irc_disconnect()
{
  close_server_connection();
}