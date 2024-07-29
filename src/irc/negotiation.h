#ifndef _IRC_NEGOTIATION_H
#define _IRC_NEGOTIATION_H

#define BUFFER_SIZE 1024
/* 10 most common capabilities for an IRC server */
struct irc_capabilities
{
	int multiPrefix;
	int sasl;
	int accountNotify;
	int awayNotify;
	int extendedJoin;
	int chghost;
	int userhostInNames;
	int inviteNotify;
	int labeledResponse;
	int messageTags;
};

void
ls_capabilities();
void
print_capabilities(const struct irc_capabilities* caps);

#endif /* _IRC_NEGOTIATION_H */