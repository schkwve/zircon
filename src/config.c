#include <stdlib.h>
#include <string.h>

#include <config.h>
#include <system/uname.h>

struct zircon_config zircon_config;

int load_config()
{
  /* TODO: Open a config file and try to read it. */

  /* get username and full name */
  if (system_get_username(&zircon_config.username, &zircon_config.fullname) !=
      0) {
    return -1;
  }

  /* make nickname and username identical by default */
  zircon_config.nickname = strdup(zircon_config.username);

  return 0;
}

void free_config()
{
  if (zircon_config.nickname) {
    free(zircon_config.nickname);
  }

  if (zircon_config.username) {
    free(zircon_config.username);
  }

  if (zircon_config.fullname) {
    free(zircon_config.fullname);
  }
}

struct irc_server_info *config_get_server_info(void)
{
  return &zircon_config.server;
}

char *config_get_nickname()
{
  return zircon_config.nickname;
}

char *config_get_username()
{
  return zircon_config.username;
}

char *config_get_fullname()
{
  return zircon_config.fullname;
}
