#ifndef _CONFIG_H
#define _CONFIG_H

#include <network/server_info.h>

struct zircon_config
{
  struct irc_server_info server;

  char *nickname;
  char *username;
  char *fullname;
};

int load_config();

struct irc_server_info *config_get_server_info(void);

char *config_get_nickname();
char *config_get_username();
char *config_get_fullname();

#endif /* _CONFIG_H */