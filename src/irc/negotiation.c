#include <irc/commands.h>
#include <irc/connect.h>
#include <irc/negotiation.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils/zerr.h>

void
ls_capabilities()
{

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