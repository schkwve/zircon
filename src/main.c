#include <network/connect.h>

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  const char *address = "0.0.0.0";
  const int port = 6667;

  /* assume we want to connect to localhost @ 6667 */
  connect_server(address, port);
  close_server_connection();

  return 0;
}