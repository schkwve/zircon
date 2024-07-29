#include <config.h>
#include <irc/connect.h>
#include <stdlib.h>
#include <utils/signals.h>
#include <utils/zerr.h>
#include <zircon.h>

static int exit_code = 0;

void
die(void);

int
main(int argc, char** argv)
{

  UNUSED(argc);
  UNUSED(argv);
  UNUSED(exit_code);

  register_handlers();

  if (atexit(die) != 0) {
    zerr("Failed to register exit handler");
    return 1;
  }

  /* irc.libera.chat */
  const char* address = "94.125.182.252";
  const int port = 6667;

  zinfo("Connecting to %s:%d", address, port);

  load_config();

  /* everything must be loaded from here on */

  /* assume we want to connect to localhost @ 6667 */
  irc_connect_to(address, port);

  irc_disconnect();

  zinfo("Disconnected from %s:%d", address, port);
  zinfo("Done");

  return 0;
}

void
die(void)
{
  irc_disconnect();

  free_config();

  zsucc("Freed memory and disconnected from server");
}