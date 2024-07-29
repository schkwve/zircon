#ifndef _IRC_COMMANDS_H
#define _IRC_COMMANDS_H

#include <stddef.h>

/** NICK **/

void
irc_nick(const char* nickname);

/** USER **/
void
irc_user(const char* username, const char* fullname);

/** CAP **/

enum
{
  IRC_VER302 = 302,
};

void
irc_capls(int version);
void
irc_capreq(const char* capabilities);
void
irc_capend(void);
void
irc_join_channel(const char* channel);
int
irc_recv(char** buffer, size_t size);

#endif /* _IRC_COMMANDS_H */