#include <irc/commands.h>
#include <irc/connect.h>
#include <stdio.h>
#include <string.h>
#include <utils/zerr.h>
#include <zircon.h>

#define MESSAGE_MAXLEN 512

/* NICK command */
void
irc_nick(const char* nickname)
{
	if (strlen(nickname) < 1) {
		zerr("Nickname cannot be empty");
		return;
	}

	char buffer[MESSAGE_MAXLEN];
	sprintf(buffer, "NICK %s\r\n", nickname);

	irc_send(buffer);
}

/* USER command */
void
irc_user(const char* username, const char* fullname)
{
	char buffer[MESSAGE_MAXLEN];

	/* TODO: check username and full name for invalid characters */
	/* but for now we can assume everything is valid */

	/* TODO: check for USERLEN when RPL_ISUPPORT is sent */
	sprintf(buffer, "USER %s 0 * :%s\r\n", username, fullname);

	irc_send(buffer);
}

/* CAP LS command */
void
irc_capls(int version)
{
	char buffer[MESSAGE_MAXLEN];
	sprintf(buffer, "CAP LS %.3u\r\n", version);

	irc_send(buffer);
}

/* CAP REQ command */
void
irc_capreq(const char* capabilities)
{
	char buffer[MESSAGE_MAXLEN];
	sprintf(buffer, "CAP REQ :%s\r\n", capabilities);
	irc_send(buffer);
}

/* CAP END */
void
irc_capend(void)
{
	irc_send("CAP END\r\n");
}

void 
irc_join_channel(const char *channel_name) {
	if (strlen(channel_name) < 2) {
		zerr("%s must be atlesat 2 characters", channel_name);
		return;
	}

	if (channel_name[0] != '#' || channel_name[0] != '&') {
		zerr("%s is not a channel name", channel_name);
	}

	char *command = NULL;
	sprintf(command, "JOIN %s\r\n", channel_name);
	irc_send(command);
}