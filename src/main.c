#include <config.h>
#include <irc/connect.h>
#include <utils/zerr.h>
#include <zircon.h>
#include <utils/kvpairs.h>
#include <utils/str.h>      
#include <irc/negotiation.h>

void die(void);

int main(int argc, char **argv)
{
  

  UNUSED(argc);
  UNUSED(argv);

  atexit(die);

  /* chat.freenode.net */
  const char *address = "94.125.182.252";
  const int port = 6667;

  zinfo("Connecting to %s:%d", address, port);

  load_config();

  /* everything must be loaded from here on */

  struct irc_capabilities *caps = malloc(sizeof(struct irc_capabilities));

  req_capabilities(caps);
  print_capabilities(caps);

  free(caps);
  /* assume we want to connect to localhost @ 6667 */
  irc_connect_to(address, port);
  irc_disconnect();

  zinfo("Disconnected from %s:%d", address, port);
  zinfo("Done");

  return 0;
}

void die(void)
{
  irc_disconnect();
  free_config();

  zinfo("Exited");
}