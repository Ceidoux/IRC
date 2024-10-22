# include "../../incs/irc.h"

void	Server::privmsg( std::string line, Client & client )
{
	// if there is a # after PRIVMSG, it means it is a channel message
	if (line[8] && line[8] == '#')
	{
		std::string channel = line.substr(line.find("#"), line.find(" ", line.find("#")) - line.find("#"));
		std::string message = line.substr(line.find(":", line.find("#")) + 1);
		std::string RPL_PRIVMSG = ":" + client.getNick() + "!" + client.getUser() + "@localhost PRIVMSG " + channel + " :" + message + "\r\n";
		for (std::size_t i = 0; i < this->_channels.size(); i++)
		{
			if (this->_channels[i].getName() == channel)
			{
				for (std::size_t j = 0; j < this->_channels[i].getClients().size(); j++)
				{
					if (this->_channels[i].getClients()[j]->getFd() != client.getFd())
						write(this->_channels[i].getClients()[j]->getFd(), RPL_PRIVMSG.c_str(), RPL_PRIVMSG.length());
				}
			}
		}
	}
	// else
	// {
	// 	std::string recipient = line.substr(line.find(" ") + 1, line.find(" ", line.find(" ") + 1) - line.find(" ") - 1);
	// 	std::string message = line.substr(line.find(":", line.find(" ")) + 1);
	// 	std::string RPL_PRIVMSG = ":" + client.getNick() + "!" + client.getUser() + "@" + "localhost" + " PRIVMSG " + recipient + " :" + message + "\r\n";
	// 	for (int i = 0; i < this->_clients.size(); i++)
	// 	{
	// 		if (this->_clients[i].getNick() == recipient)
	// 		{
	// 			write(this->_clients[i].getFd(), RPL_PRIVMSG.c_str(), RPL_PRIVMSG.length());
	// 		}
	// 	}
	// }
}
