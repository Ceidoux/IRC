# include "../../incs/irc.h"

void	Server::invite( std::string line, Client & client )
{
	if (line.find("#") == std::string::npos)
	{
		//channel name starts after secound space found
		std::string channel = line.substr(line.find(" ", line.find(" ") + 1) + 1, line.find(" ", line.find(" ", line.find(" ") + 1) + 1) - line.find(" ", line.find(" ") + 1) - 1);
		writeRPL(client.getFd(), ERR_NOSUCHCHANNEL(client.getNick(), channel));
		return;
	}
	std::string channel = line.substr(line.find("#"), line.find(" ", line.find("#")) - line.find("#"));
	std::cout << "channel: " << channel << std::endl;
	std::size_t i = 0;

	while (i < this->_channels.size())
	{
		if (this->_channels[i].getName() == channel)
			break;
		i++;
	}
	if (i == this->_channels.size())
	{
		writeRPL(client.getFd(), ERR_NOSUCHCHANNEL(client.getNick(), channel));
		return;
	}
	
	std::size_t j = 0;
	while (j < this->_channels[i].getClients().size())
	{
		if (this->_channels[i].getClients()[j]->getNick() == client.getNick())
			break;
		j++;
	}
	if (j == this->_channels[i].getClients().size())
	{
		writeRPL(client.getFd(), ERR_NOTONCHANNEL(client.getNick(), channel));
		return;
	}
	std::string invitedNick = line.substr(line.find(" ") + 1, line.find(" ", line.find(" ") + 1) - line.find(" ") - 1);
	std::cout << "invitedNick: " << invitedNick << std::endl;
	// si dejadans le channel le dire
	for (std::size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i].getName() == channel)
		{
			for (std::size_t j = 0; j < this->_channels[i].getClients().size(); j++)
			{
				if (this->_channels[i].getClients()[j]->getNick() == invitedNick)
				{
					writeRPL(client.getFd(), ERR_USERONCHANNEL(channel, invitedNick));
					return;
				}
			}
		}
	}
	j = 0;
	while (j < this->_clients.size())
	{
		if (this->_clients[j].getNick() == invitedNick)
			break;
		j++;
	}
	if (j == this->_clients.size())
	{
		// writeRPL(client.getFd(), ERR_NOSUCHNICK(client.getNick(), invitedNick));
		std::cout << "ERR_NOSUCHNICK" << std::endl;
		return;
	}
    std::string RPL_INVITING = ":" + client.getNick() + "!" + client.getUser() + "@localhost 341 " + client.getNick() + " " + invitedNick + " " + channel + "\r\n";
	// std::string RPL_INVITING = ":" + client.getNick() + "!" + client.getUser() + "@localhost 341 " + client.getNick() + " " + channel+ " " + invitedNick + "\r\n";
	std::cout << "RPL_INVITING: " << RPL_INVITING << std::endl;
	writeRPL(client.getFd(), RPL_INVITING);

	// Send the INVITE message to the invited person
	std::string INVITE_MSG = ":" + client.getNick() + "!" + client.getUser() + "@localhost INVITE " + invitedNick + " " + channel + "\r\n";
	std::cout << "INVITE_MSG: " << INVITE_MSG << std::endl;
	writeRPL(this->_clients[j].getFd(), INVITE_MSG);
	for (std::size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i].getName() == channel)
		{
			this->_channels[i].addInvitedClient(&this->_clients[j]);
			break;
		}
	}
}