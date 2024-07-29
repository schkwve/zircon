#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <system/uname.h>
#include <utils/kvpairs.h>
#include <utils/str.h>
#include <utils/zerr.h>

struct zircon_config zircon_config;

int load_config()
{
  /* get username and full name */
  if (system_get_username(&zircon_config.username, &zircon_config.fullname) != 0) {
    zerr(0, "Failed to get username and full name");
    return -1;
  }

  /* make nickname and username identical by default */
  zircon_config.nickname = z_strdup(zircon_config.username);

  KeyValueArray kvArray;
  if (read_key_value_file("zircon.conf", &kvArray, &zircon_config) != 0) {
    zerr(1, "Couldn't read config file: ");
    return -1;
  }

  char* name = get_value(&kvArray, "name");
  char* username = get_value(&kvArray, "username");
  char* nickname = get_value(&kvArray, "nickname");

  if (validate_nickname(nickname) == 1) {
    zerr(0, "Invalid nickname!");
  } else if (validate_nickname(nickname) == -1) {
    zwarn("Nickname contains a dot which is not recommended");
  } else if (validate_nickname(nickname) == 0) {
    zsucc("Nickname is valid");
  }

  /* Free old values if they were dynamically allocated */
  free(zircon_config.fullname);
  free(zircon_config.username);
  free(zircon_config.nickname);

  /* Assign new values */
  zircon_config.fullname = name;
  zircon_config.username = username;
  zircon_config.nickname = nickname;

  zinfo("Full name: %s", zircon_config.fullname);
  zinfo("Username: %s", zircon_config.username);
  zinfo("Nickname: %s", zircon_config.nickname);

  return 0;
}

void free_config()
{
  zwarn("Free is empty because pointers are handled by the kvArray");
}

struct irc_server_info*
config_get_server_info(void)
{
  return &zircon_config.server;
}

char*
config_get_nickname()
{
  return zircon_config.nickname;
}

char*
config_get_username()
{
  return zircon_config.username;
}

char*
config_get_fullname()
{
  return zircon_config.fullname;
}

/* 1=invalid -1=dot 0=good */
int
validate_nickname(const char* nickname)
{
  if (nickname[0] == '\0' || nickname[0] == '$' || nickname[0] == ':' ||
      nickname[0] == '#' || nickname[0] == '&' || nickname[0] == '%' ||
      nickname[0] == '+' || nickname[0] == '@' || nickname[0] == '~') {
    return 1;
  }

  if (strstr(nickname, " ") != NULL || strstr(nickname, ",") != NULL ||
      strstr(nickname, "*") != NULL || strstr(nickname, "?") != NULL ||
      strstr(nickname, "!") != NULL || strstr(nickname, "@") != NULL) {
    return 1;
  }

  if (strstr(nickname, ".") != NULL) {
    return -1;
  }

  return 0;
}