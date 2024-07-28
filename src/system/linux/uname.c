#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <system/uname.h>
#include <zircon.h>

int system_get_username(char **username, char **fullname)
{
  /* this prevents gcc complaining about */
  /* these parameters being set but not used */
  UNUSED(username);
  UNUSED(fullname);

  size_t name_len;
  size_t gecos_len;

  struct passwd *pwd = getpwuid(getuid());

  if (pwd == NULL) {
    /* TODO: Proper error handling */
    return 1;
  }

  name_len = strlen(pwd->pw_name);
  gecos_len = strlen(pwd->pw_gecos);

  /* copy username and full name strings */
  *username = (char *)malloc(name_len);
  *fullname = (char *)malloc(gecos_len);
  memcpy(*username, pwd->pw_name, name_len);
  memcpy(*fullname, pwd->pw_gecos, gecos_len);

  return 0;
}