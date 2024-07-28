#include <config.h>
#include <irc/connect.h>
#include <utils/zerr.h>
#include <zircon.h>
#include <utils/kvpairs.h>
#include <utils/str.h>

void die(void);

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  atexit(die);

  /* chat.freenode.net */
  const char *address = "207.148.28.126";
  const int port = 6667;

  zinfo("Connecting to %s:%d", address, port);

  load_config();

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