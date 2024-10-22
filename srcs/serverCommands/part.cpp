# include "../../incs/irc.h"

void	Server::part( std::string line, Client & client )
{
    std::string channel = line.substr(line.find("#"), line.find(" ", line.find("#")) - line.find("#"));
    std::string partMessage = line.substr(line.find(":", line.find("#")) + 1);
    std::string RPL_PART = ":" + client.getNick() + "!" + client.getUser() + "@localhost PART " + channel + "\r\n";
	for (std::size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i].getName() == channel)
		{
			for (std::size_t j = 0; j < this->_channels[i].getClients().size(); j++)
			{
				if (this->_channels[i].getClients()[j]->getNick() == client.getNick())
				{
					for (std::size_t k = 0; k < this->_channels[i].getClients().size(); k++)
						writeRPL(this->_channels[i].getClients()[k]->getFd(), RPL_PART);
					this->_channels[i].removeClient(&client);
					break;
				}
			}
		}
	}
}
