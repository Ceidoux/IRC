#ifndef RPL_H
#define RPL_H

# define RPL_WELCOME(nick)						":localhost 001 " + nick + " :Welcome to the ft_irc Network, " + nick + "\r\n"
# define RPL_YOURHOST(nick)						":localhost 002 " + nick + " :Your host is ft_irc, running version 1.0\r\n"
# define RPL_CREATED(nick)						":localhost 003 " + nick + " :This server was created 2024-08-01\r\n"
# define RPL_MYINFO(nick)						":localhost 004 " + nick + " localhost 1.0 <user_modes> <chan_modes>\r\n"
# define RPL_ISUPPORT(nick)						":localhost 005 " + nick + " PREFIX=(ov)@+ CHANTYPES=#& :are supported by this server\r\n"
# define RPL_JOIN(nick, user, channel)			":" + nick + "!" + user + "@" + "localhost" + " JOIN :" + channel + "\r\n"
# define RPL_TOPIC(nick, channel, topic)		":" + std::string("localhost") + " 332 " + nick + " " + channel + " :" + topic + "\r\n"
# define RPL_QUIT(nick, user, msg)				":" + nick + "!" + user + "@" + "localhost" + " QUIT :" + msg + "\r\n"
# define RPL_NAMREPLY(nick, channel, allnicks)	":localhost 353 " + nick + " = " + channel + " :" + allnicks + "\r\n"
# define RPL_ENDOFNAMES(nick, channel)			":localhost 366 " + nick + " " + channel + " :End of /NAMES list.\r\n"
# define RPL_CHANNELMODEIS(nick, channel, mode)	":localhost 324 " + nick + " " + channel + " " + mode + "\r\n"

#endif