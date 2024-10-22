# include "../../incs/irc.h"

void	Server::quit( std::string line, Client & client )
{
	std::string RPL_QUIT = ":" + client.getNick() + "!" + client.getUser() + "@" + "localhost" + " QUIT :" + line.substr(line.find(":") + 1) + "\r\n";
	std::cout << "RPL_QUIT: " << RPL_QUIT << std::endl;
	for (std::size_t i = 0; i < this->_channels.size(); i++)
	{
		for (std::size_t j = 0; j < this->_channels[i].getClients().size(); j++)
		{
			if (this->_channels[i].getClients()[j]->getNick() == client.getNick())
			{
				for (std::size_t k = 0; k < this->_channels[i].getClients().size(); k++)
				{
					if (this->_channels[i].getClients()[k]->getNick() != client.getNick())
						write(this->_channels[i].getClients()[k]->getFd(), RPL_QUIT.c_str(), RPL_QUIT.length());
				}
				this->_channels[i].removeClient(&client);
				break;
			}
		}
	}
	for (std::size_t i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i].getNick() == client.getNick())
		{
			write(this->_clients[i].getFd(), RPL_QUIT.c_str(), RPL_QUIT.length());
			// close(this->_clients[i].getFd());
			break;
		}
	}
}
