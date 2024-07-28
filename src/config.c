#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <config.h>
#include <system/uname.h>
#include <utils/str.h>
#include <utils/zerr.h>
#include <utils/kvpairs.h>

struct zircon_config zircon_config;

int load_config()
{
  /* get username and full name */
  if (system_get_username(&zircon_config.username, &zircon_config.fullname) !=
      0) {
    zerr("Failed to get username and full name");
    return -1;
  }

  /* make nickname and username identical by default */
  zircon_config.nickname = z_strdup(zircon_config.username);

  KeyValueArray kvArray;

  if (read_key_value_file("zircon.conf", &kvArray, &zircon_config) != 0) {
    zerr("Coulnt read config file: ");
    return -1;
  }

  
  
  
  char* name = get_value(&kvArray, "name");
  char *username = get_value(&kvArray, "username");
  char *nickname =get_value(&kvArray, "nickname");

  if (validate_nickname(nickname) == 1) {
    zerr("Invalid nickname!");
  } else if (validate_nickname(nickname) == -1) {
    zwarn("Nickname contains a a dot which is not recommended");
  } else if (validate_nickname(nickname) == 0) {
    zsucc("Nickname is valid");
  }

  zinfo("Full name: %s", name);
  zinfo("Username: %s", username);
  zinfo("Nickname: %s", nickname);

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

/* 1=invalid -1=dot 0=good */
int validate_nickname(const char *nickname) {
   if (nickname[0] == '\0' || nickname[0] == '$' || nickname[0] == ':' || nickname[0] == '#' || nickname[0] == '&'
    || nickname[0] == '%' || nickname[0] == '+' || nickname[0] == '@' || nickname[0] == '~') {
      return 1;
    } else {
      if (strstr(nickname, " ") != NULL || strstr(nickname, ",") != NULL || strstr(nickname, "*") != NULL ||
        strstr(nickname, "?") != NULL || strstr(nickname, "!") != NULL || strstr(nickname, "@") != NULL) {
      return 1;
      } else {
        if (strstr(nickname, ".") != NULL) {
          return -1;
        } else {
          return 0;
        }
      }
    }
    
   return 0;
}