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

  load_config();

  zinfo("Testing please work! %d %s\n", 5, "hello");
  zwarn("Testing please work! %d %s\n", 5, "hello");
  zerr("Testing please work! %d %s\n", 5, "hello");
  zfatal(1, "Testing please work! %d %s\n", 5, "hello");

  /* assume we want to connect to localhost @ 6667 */
  irc_connect_to(address, port);
  irc_disconnect();

  return 0;
}