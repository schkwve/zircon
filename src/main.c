#include <config.h>
#include <irc/connect.h>
#include <utils/zerr.h>

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  /* chat.freenode.net */
  const char *address = "207.148.28.126";
  const int port = 6667;

  zinfo("Connecting to %s:%d\n", address, port);

  load_config();

  

  /* assume we want to connect to localhost @ 6667 */
  irc_connect_to(address, port);
  irc_disconnect();

  zinfo("Disconnected from %s:%d\n", address, port);
  zinfo("Done\n");

  return 0;
}