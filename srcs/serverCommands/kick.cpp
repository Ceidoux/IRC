# include "../../incs/irc.h"

void	Server::kick( std::string line, Client & client )
{
	std::string channel = line.substr(line.find("#"), line.find(" ", line.find("#")) - line.find("#"));
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

	std::string kickedNick = line.substr(line.find(" ", line.find("#")) + 1, line.find(" ", line.find(" ", line.find("#")) + 1) - line.find(" ", line.find("#")) - 1);
	std::cout << "kickedNick: " << kickedNick << std::endl;
	
	j = 0;
	while (j < this->_channels[i].getClients().size())
	{
		std::cout << "Comparing it with: " << this->_channels[i].getClients()[j]->getNick() << std::endl;
		if (this->_channels[i].getClients()[j]->getNick() == kickedNick)
			break;
		j++;
	}
	if (j == this->_channels[i].getClients().size())
	{
		writeRPL(client.getFd(), ERR_USERNOTINCHANNEL(client.getNick(), kickedNick, channel));
		return;
	}

	std::string kickMessage = line.substr(line.find(":", line.find(" ", line.find(" ", line.find("#")) + 1)) + 1);
	if (kickMessage == "")
		kickMessage = "Probably has done something wrong";
	if (kickedNick == "" || channel == "")
	{
		writeRPL(client.getFd(), ERR_NEEDMOREPARAMS(client.getNick(), "KICK"));
		return;
	}
	
	std::string RPL_KICK = ":" + client.getNick() + "!" + client.getUser() + "@localhost KICK " + channel + " " + kickedNick + " :" + kickMessage + "\r\n";
	for (std::size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i].getName() == channel)
		{
			for (std::size_t j = 0; j < this->_channels[i].getClients().size(); j++)
			{
				int w = 0;
				while (w < static_cast<int>(this->_channels[i].getOperators().size()))
				{
					if (this->_channels[i].getOperators()[w]->getNick() == client.getNick())
						break;
					w++;
				}
				if (w == static_cast<int>(this->_channels[i].getOperators().size()))
				{
					writeRPL(client.getFd(), ERR_CHANOPRIVSNEEDED(client.getNick(), channel));
					return;
				}
			}
			// if (std::find(this->_channels[i].operators.begin(), this->_channels[i].operators.end(), client.getNick()) == this->_channels[i].operators.end())
			// {
			// 	writeRPL(client.getFd(), ERR_CHANOPRIVSNEEDED(client.getNick(), channel));
			// 	return;
			// }
			for (std::size_t j = 0; j < this->_channels[i].getClients().size(); j++)
			{
				if (this->_channels[i].getClients()[j]->getNick() == kickedNick)
				{
					for (std::size_t k = 0; k < this->_channels[i].getClients().size(); k++)
						writeRPL(this->_channels[i].getClients()[k]->getFd(), RPL_KICK);
					this->_channels[i].removeClient(this->_channels[i].getClients()[j]);
					if (this->_channels[i].getNumberOfClients() == 0)
					{
						this->_channels.erase(this->_channels.begin() + i);
						std::cout << this->_channels[i].getName() << " was removed (no client left)" << std::endl;
					}
					break;
				}
			}
		}
	}
}
