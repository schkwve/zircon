#include <config.h>
#include <irc/connect.h>

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  const char *address = "0.0.0.0";
  const int port = 6667;

  load_config();

  /* assume we want to connect to localhost @ 6667 */
  irc_connect_to(address, port);
  irc_disconnect();

  return 0;
}