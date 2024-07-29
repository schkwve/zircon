#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <system/uname.h>
#include <utils/str.h>
#include <zircon.h>
#include <utils/zerr.h>

#define MAX_USERNAME_LEN 32
#define MAX_FULLNAME_LEN 64

int system_get_username(char **username, char **fullname)
{
  /* this prevents gcc complaining about */
  /* these parameters being set but not used */
  UNUSED(username);
  UNUSED(fullname);

  int username_len = MAX_USERNAME_LEN;
  int fullname_len = MAX_FULLNAME_LEN;

  char *username_tmp = (char *)malloc(username_len);
  char *fullname_tmp = (char *)malloc(fullname_len);

  /* *username = GetUserNameA() */
  if (!GetUserNameA(username_tmp, &username_len)) {
    /* reallocate and try again if the buffer is too small */
    if (GetLastError() == ERROR_MORE_DATA) {
      username_tmp = realloc(username_len);
      if (!GetUserNameA(username_tmp, &username_len)) {
        free(username_tmp);
        free(fullname_tmp);

        zerror("GetUserNameA() failed with the following error code: %x\n", GetLastError());

        return 1;
      }
    } else {
      free(username_tmp);
      free(fullname_tmp);

      zerror("GetUserNameA() failed with the following error code: %x\n", GetLastError());
      return 1;
    }
  }

  if (!GetUserNameExA(NameDisplay, fullname_tmp, &fullname_len)) {
    /* reallocate and try again if the buffer is too small */
    if (GetLastError() == ERROR_MORE_DATA) {
      fullname_tmp = realloc(fullname_len);
      if (!GetUserNameExA(NameDisplay, fullname_tmp, &fullname_len)) {
        /* if we still error out, just use the default */
        zerror("GetUserNameExA() failed with the following error code: %x\n", GetLastError());
        zinfo("Using default real name...\n");
        fullname_tmp = realloc(strlen(FULLNAME_DEFAULT));
        strcpy(fullname_tmp, FULLNAME_DEFAULT);
      }
    } else {
      free(username_tmp);
      free(fullname_tmp);

      zerror("GetUserNameExA() failed with the following error code: %x\n", GetLastError());
      zinfo("Using default real name...\n");
      fullname_tmp = realloc(strlen(FULLNAME_DEFAULT));
      strcpy(fullname_tmp, FULLNAME_DEFAULT);
      return 1;
    }
  }

  *username = username_tmp;
  *fullname = fullname_tmp;

  return 0;
}