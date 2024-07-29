
#include <irc/connect.h>
#include <irc/negotiation.h>
#include <network/connect.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <utils/str.h>
#include <utils/zerr.h>

void
irc_connect_to(const char* server_address, uint16_t server_port)
{

  connect_server(server_address, server_port);

  struct irc_capabilities* caps = malloc(sizeof(struct irc_capabilities));

  ls_capabilities(caps);
  print_capabilities(caps);

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
    zerr("The buffer cant be empty");
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
    zerr("Read size cant be 0!");
    return -1;
  }

  /* Alloc memory for the buffer so that it *hopefully* doesnt segfault */
  *buffer = (char*)malloc(size);
  if (*buffer == NULL) {
    zfatal(-281, "Could not allocate buffer to recv from the server:");
    return -1;
  }

  bzero(*buffer, size);
  char* pbuf = z_strdup(*buffer);
  z_strstrip(pbuf, 2);
  zircmsg("Recived message '%s' from the server.", pbuf);

  return recv_data_from_server(buffer, size);
}