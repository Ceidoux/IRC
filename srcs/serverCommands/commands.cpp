# include "../../incs/irc.h"

void	Server::command( std::string buff, Client & client )
{
	#define		NUMBER_OF_CMD 10
	
	std::string	cmd[NUMBER_OF_CMD] = {"JOIN ", "PING ", "PRIVMSG ", "NICK ", "QUIT ", "PART ", "KICK ", "TOPIC ", "INVITE ", "MODE "};	
	void		(Server::*fct[NUMBER_OF_CMD])(std::string, Client &client) = { &Server::join, &Server::ping, &Server::privmsg, &Server::nick, &Server::quit, &Server::part, &Server::kick, &Server::topic, &Server::invite, &Server::mode };
	int			idx;

	for (idx = 0; idx < NUMBER_OF_CMD; ++idx)
		if (!buff.compare(0, cmd[idx].length(), cmd[idx]))
			break;
	if (idx != NUMBER_OF_CMD )
		(this->*(fct[idx]))(buff, client);
}
