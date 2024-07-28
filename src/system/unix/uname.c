#include <pwd.h>
#include <string.h>
#include <unistd.h>

#include <system/uname.h>
#include <utils/str.h>
#include <zircon.h>
#include <utils/zerr.h>

int system_get_username(char **username, char **fullname)
{
  /* this prevents gcc complaining about */
  /* these parameters being set but not used */
  UNUSED(username);
  UNUSED(fullname);

  struct passwd *pwd = getpwuid(getuid());

  if (pwd == NULL) {
    zerr("getpwuid returned NULL!\n");
    return 1;
  }

  /* copy username and full name strings */
  *username = z_strdup(pwd->pw_name);
  *fullname = z_strdup(pwd->pw_gecos);

  return 0;
}