#include <pwd.h>
#include <string.h>
#include <unistd.h>

#include <system/uname.h>
#include <zircon.h>

int system_get_username(char **username, char **fullname)
{
  /* this prevents gcc complaining about */
  /* these parameters being set but not used */
  UNUSED(username);
  UNUSED(fullname);

  struct passwd *pwd = getpwuid(getuid());

  if (pwd == NULL) {
    /* TODO: Proper error handling */
    return 1;
  }

  /* copy username and full name strings */
  *username = strdup(pwd->pw_name);
  *fullname = strdup(pwd->pw_gecos);

  return 0;
}