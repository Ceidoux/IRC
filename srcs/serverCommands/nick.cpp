# include "../../incs/irc.h"

void	Server::nick( std::string line, Client & client )
{
	std::string newNick = line.substr(line.find("NICK") + 5);
	
	if (newNick == "")
		writeRPL(client.getFd(), "No nickname given\r\n");
	else if (!client.validNick(newNick))
		writeRPL(client.getFd(), ERR_ERRONEUSNICKNAME(newNick));
	else if (checkNickCollision(newNick))
		writeRPL(client.getFd(), ERR_NICKCOLLISION(newNick));
	else
	{
		std::string RPL_NICK = ":" + client.getNick() + "!" + client.getUser() + "@" + "localhost" + " NICK :" + newNick + "\r\n";
		writeRPL(client.getFd(), RPL_NICK);
		for (std::size_t i = 0; i < this->_channels.size(); i++)
		{
			for (std::size_t j = 0; j < this->_channels[i].getClients().size(); j++)
			{
				if (this->_channels[i].getClients()[j]->getNick() == client.getNick())
				{
					for (std::size_t k = 0; k < this->_channels[i].getClients().size(); k++)
					{
						if (this->_channels[i].getClients()[k]->getNick() != client.getNick())
							writeRPL(this->_channels[i].getClients()[k]->getFd(), RPL_NICK);
					}
				}
			}
		}
		client.setNick(newNick);
	}
	std::cout << "Client state: nickname=" << client.getNick() << std::endl;
}
