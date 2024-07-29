#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <system/uname.h>
#include <unistd.h>
#include <utils/str.h>
#include <utils/zerr.h>
#include <zircon.h>

char*
get_real_name(const char* gecos)
{
  char* real_name;
  const char* comma_pos;
  size_t length;

  /* Allocate memory for the real name */
  real_name = (char*)malloc(MAX_FIELD_LENGTH);
  if (real_name == NULL) {
    zfatal(-284, "Failed to allocate memory for real name\n: ");
  }

  /* Find the position of the first comma */
  comma_pos = strchr(gecos, ',');
  if (comma_pos != NULL) {
    /* Copy the substring before the first comma into real_name */
    length = comma_pos - gecos;
    if (length >= MAX_FIELD_LENGTH) {
      length = MAX_FIELD_LENGTH - 1;
    }
    strncpy(real_name, gecos, length);
    real_name[length] = '\0'; /* Null-terminate the string */
  } else {
    /* No comma found, copy the whole field */
    strncpy(real_name, gecos, MAX_FIELD_LENGTH - 1);
    real_name[MAX_FIELD_LENGTH - 1] = '\0'; /* Null-terminate the string */
  }

  return real_name;
}

int
system_get_username(char** username, char** fullname)
{
  /* this prevents gcc complaining about */
  /* these parameters being set but not used */
  UNUSED(username);
  UNUSED(fullname);

  struct passwd* pwd = getpwuid(getuid());

  if (pwd == NULL) {
    zerr(0, "getpwuid returned NULL!");
    return 1;
  }

  char* name = get_real_name(pwd->pw_gecos);
  if (name == NULL) {
    zerr(0, "Failed to get real name");
    return 1;
  }

  /* copy username and full name strings */
  *username = z_strdup(pwd->pw_name);
  *fullname = z_strdup(name);

  return 0;
}