# include "../../incs/irc.h"

void		Server::topic(std::string line, Client & client)
{
	std::string channel = line.substr(line.find("#"), line.find(" ", line.find("#")) - line.find("#"));
	std::string topic = line.substr(line.find(":") + 1, line.size() - line.find(":") + 1); // a voir si place pour \0 ou non
	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i].getName() == channel)
		{
			if (this->_channels[i].getMode_t() == true)
			{
				std::cout << "channel is set to secret" << std::endl;
				size_t j = 0;
				while (j < this->_channels[i].getOperators().size())
				{
					if (this->_channels[i].getOperators()[j]->getNick() == client.getNick())
						break ;
					j++;
				}
				if (j == this->_channels[i].getOperators().size())
				{
					writeRPL(client.getFd(), ERR_CHANOPRIVSNEEDED(client.getNick(), channel));
					return ;
				}
			}
		}
	}
	for (std::size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i].getName() == channel)
		{
			for (std::size_t j = 0; j < this->_channels[i].getClients().size(); j++)
				writeRPL(this->_channels[i].getClients()[j]->getFd(), RPL_TOPIC(client.getNick(), this->_channels[i].getName(), topic));
			this->_channels[i].setTopic(topic);
			return ;
		}
	}
}