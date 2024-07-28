#ifndef _SYSTEM_UNAME_H
#define _SYSTEM_UNAME_H

#define MAX_FIELD_LENGTH 256

int system_get_username(char **username, char **fullname);
char* get_real_name(const char* gecos);

#endif /* _SYSTEM_UNAME_H */