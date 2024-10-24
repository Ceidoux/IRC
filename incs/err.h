#ifndef ERR_H
#define ERR_H


# define ERR_NOSUCHNICK(nick) 								nick + " :No such nick/channel\r\n"
# define ERR_NOSUCHCHANNEL(nick, channel)			        ":localhost 403 " + nick + " " + channel + " :No such channel\r\n"
# define ERR_NONICKNAMEGIVEN								" :No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(nick)					        ":localhost 432 * " + nick + " :Erroneous Nickname\r\n"
# define ERR_NICKCOLLISION(nick)							":localhost 436 " + nick + " :Nickname collision\r\n"
# define ERR_NICKNAMEINUSE(nick)							nick + " :Nickname is already in use\r\n"
# define ERR_USERNOTINCHANNEL(nick, kick, channel)	        ":localhost 441 " + nick + " " + kick + " " + channel + " :They aren't on that channel\r\n"
# define ERR_NOTONCHANNEL(nick, channel)			        ":localhost 442 " + nick + " " + channel + " :You're not on that channel\r\n"
# define ERR_NEEDMOREPARAMS(nick, command)			        ":localhost 461 " + nick + " " + command + " :Not enough parameters\r\n"
# define ERR_PASSWDMISMATCH(nick)					        ":localhost 464 " + nick + " :Password Incorrect\r\n"
# define ERR_CHANNELISFULL(nick, channel)			        ":localhost 471 " + nick + " " + channel + " :Cannot join channel (+l)\r\n"
# define ERR_INVITEONLYCHAN(nick, channel)			        ":localhost 473 " + nick + " " + channel + " :Cannot join channel (+i)\r\n"
# define ERR_BADCHANNELKEY(nick, channel)			        ":localhost 475 " + nick + " " + channel + " :Cannot join channel (+k)\r\n"
# define ERR_CHANOPRIVSNEEDED(nick, channel)		        ":localhost 482 " + nick + " " + channel + " :You're not channel operator\r\n"
# define ERR_INVALIDKEY(nick, channel)				        ":localhost 525 " + nick + " " + channel + " :Key is not well-formed\r\n"
# define ERR_INVALIDMODEPARAM(nick, target, mode, param)    ":localhost 696 " + nick + " " + target + " " + mode + " " + param + " :Invalid MODE parameter\r\n"
# define ERR_USERONCHANNEL(nick, channel)			        ":localhost 443 " + nick + " " + channel + " :is already on channel\r\n"

#endif
