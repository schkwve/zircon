#include <config.h>
#include <irc/connect.h>
#include <utils/zerr.h>
#include <zircon.h>
#include <utils/kvpairs.h>

void die(void);

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  atexit(die);

  /* chat.freenode.net */
  const char *address = "207.148.28.126";
  const int port = 6667;

  zinfo("Connecting to %s:%d\n", address, port);

  load_config();

  KeyValueArray kvArray;
  char* filename = "zircon.conf";
  if (read_key_value_file(filename, &kvArray) != 0) {
    zerr("Failed to read key value file\n");
    return -1;
  }
  print_key_value_pairs(&kvArray);

  /* assume we want to connect to localhost @ 6667 */
  irc_connect_to(address, port);
  irc_disconnect();

  zinfo("Disconnected from %s:%d\n", address, port);
  zinfo("Done\n");

  return 0;
}

void die(void)
{
  irc_disconnect();

  free_config();
}