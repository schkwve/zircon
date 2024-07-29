#include <irc/commands.h>
#include <irc/connect.h>
#include <irc/negotiation.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils/zerr.h>

void
ls_capabilities(struct irc_capabilities* caps)
{
	char* buffer = NULL;
	size_t buffer_size = BUFFER_SIZE;
	int ret;

	irc_capls(302);

	ret = irc_recv(&buffer, buffer_size);
	if (ret <= 0) {
		zerr("Error receiving capabilities list: ");
		free(buffer);
		return;
	}
	printf("Buffer: %s\n", buffer);

	char* cap_start = strstr(buffer, "CAP * LS :");
	if (cap_start) {
		cap_start += strlen("CAP * LS :");
		char* cap_end = strstr(cap_start, "\r\n");
		if (cap_end) {
			*cap_end = '\0';
			char* cap = strtok(cap_start, " ");
			while (cap) {
				if (strcmp(cap, "multi-prefix") == 0) {
					caps->multiPrefix = 1;
				} else if (strcmp(cap, "sasl") == 0) {
					caps->sasl = 1;
				} else if (strcmp(cap, "account-notify") == 0) {
					caps->accountNotify = 1;
				} else if (strcmp(cap, "away-notify") == 0) {
					caps->awayNotify = 1;
				} else if (strcmp(cap, "extended-join") == 0) {
					caps->extendedJoin = 1;
				} else if (strcmp(cap, "chghost") == 0) {
					caps->chghost = 1;
				} else if (strcmp(cap, "userhost-in-names") == 0) {
					caps->userhostInNames = 1;
				} else if (strcmp(cap, "invite-notify") == 0) {
					caps->inviteNotify = 1;
				} else if (strcmp(cap, "message-tags") == 0) {
					caps->messageTags = 1;
				} else if (strcmp(cap, "labeled-response") == 0) {
					caps->labeledResponse = 1;
				}
				cap = strtok(NULL, " ");
			}
		}
	}
	free(buffer);

	char* cap_req =
		"multi-prefix sasl account-notify away-notify extended-join chghost "
		"userhost-in-names invite-notify message-tags labeled-response";

	char *req_buffer = malloc(BUFFER_SIZE);

	irc_capreq(cap_req);
	irc_capreq(cap_req);
	irc_recv(&req_buffer, buffer_size);
	zinfo("Buffer: %s", req_buffer);
	free(req_buffer);

	irc_capend();
}

void
print_capabilities(const struct irc_capabilities* caps)
{
	zinfo("IRC Capabilities:");
	zinfo("  Multi Prefix: %s",
				caps->multiPrefix ? "Supported" : "Not Supported");
	zinfo("  SASL: %s", caps->sasl ? "Supported" : "Not Supported");
	zinfo("  Account Notify: %s",
				caps->accountNotify ? "Supported" : "Not Supported");
	zinfo("  Away Notify: %s", caps->awayNotify ? "Supported" : "Not Supported");
	zinfo("  Extended Join: %s",
				caps->extendedJoin ? "Supported" : "Not Supported");
	zinfo("  Chghost: %s", caps->chghost ? "Supported" : "Not Supported");
	zinfo("  Userhost In Names: %s",
				caps->userhostInNames ? "Supported" : "Not Supported");
	zinfo("  Invite Notify: %s",
				caps->inviteNotify ? "Supported" : "Not Supported");
	zinfo("  Labeled Response: %s",
				caps->labeledResponse ? "Supported" : "Not Supported");
}