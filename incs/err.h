#ifndef ERR_H
#define ERR_H

# define ERR_NOSUCHCHANNEL(nick, channel)					nick + " " + channel + " :No such channel\r\n"
# define ERR_NONICKNAMEGIVEN								" :No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(nick)							nick + " :Erroneous Nickname\r\n"
# define ERR_NICKCOLLISION(nick)							nick + " :Nickname collision\r\n"
# define ERR_NICKNAMEINUSE(nick)							nick + " :Nickname is already in use\r\n"
# define ERR_USERNOTINCHANNEL(nick, kick, channel)			nick + " " + kick + " " + channel + " :They aren't on that channel\r\n"
# define ERR_NOTONCHANNEL(nick, channel)					nick + " " + channel + " :You're not on that channel\r\n"
# define ERR_NEEDMOREPARAMS(nick, command)					nick + " " + command + " :Not enough parameters\r\n"
# define ERR_PASSWDMISMATCH(nick)							nick + " :Password Incorrect\r\n"
# define ERR_CHANNELISFULL(nick, channel)					nick + " " + channel + " :Cannot join channel (+l)\r\n"
# define ERR_INVITEONLYCHAN(nick, channel)					nick + " " + channel + " :Cannot join channel (+i)\r\n"
# define ERR_BADCHANNELKEY(nick, channel)					nick + " " + channel + " :Cannot join channel (+k)\r\n"
# define ERR_CHANOPRIVSNEEDED(nick, channel)				nick + " " + channel + " :You're not channel operator\r\n"
# define ERR_INVALIDKEY(nick, channel)						nick + " " + channel + " :Key is not well-formed\r\n"
# define ERR_INVALIDMODEPARAM(nick, target, mode, param)    nick + " " + target + " " + mode + " " + param + " :Invalid MODE parameter\r\n"

#endif
