#ifndef _IRC_COMMANDS_H
#define _IRC_COMMANDS_H

/** NICK **/

void irc_nick(const char *nickname);

/** USER **/
void irc_user(const char *username, const char *fullname);

/** CAP **/

enum
{
  IRC_VER302 = 302,
};

void irc_capls(int version);
void irc_capreq(const char *capabilities);
void irc_capend(void);

#endif /* _IRC_COMMANDS_H */