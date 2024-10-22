# include "../../incs/irc.h"

static	std::vector <Channel> createChannelList( std::string line )
{
	std::vector <Channel> channelList;
	std::string channels = line.substr(line.find("#"));
	std::string one_channel;

	for (std::size_t i = 0; i < channels.length(); i++)
	{
		while (channels[i] && channels[i] != ' ' && channels[i] != ',')
			one_channel += channels[i++];
		Channel addChannel(one_channel);
		channelList.push_back(addChannel);
		if (channels[i] != ',')
			break;
	}
	return channelList;
}

std::string	prefixIfOperator( Client & client, Channel & channel )
{
	for (std::size_t i = 0; i < channel.getOperators().size(); i++)
	{
		if (channel.getOperators()[i]->getNick() == client.getNick())
		{
			return ("@");
		}
	}
	return ("");
}

std::string	allNicks( Channel & channel )
{
	std::string	allNIcks("");

	for (std::size_t i = 0; i < channel.getClients().size(); i++)
		allNIcks += prefixIfOperator(*channel.getClients()[i], channel) +  channel.getClients()[i]->getNick() + " ";
	return (allNIcks);
}


void	Server::join( std::string line, Client & client )
{
	std::vector <Channel> channelList = createChannelList(line);

	
	for (std::size_t i = 0; i < channelList.size(); i++)
	{	
		bool channelExists = false;
		for (std::size_t j = 0; j < this->_channels.size(); j++)
		{
			if (this->getChannels()[j].getName() == channelList[i].getName())
			{
				std::cout << "Channel already exists" << std::endl;
				channelExists = true;
				if (this->getChannels()[j].getMode_i())
				{
					for (std::size_t i = 0; i < this->getChannels()[j].getInvitedClients().size(); i++)
					{
						if (this->getChannels()[j].getInvitedClients()[i]->getNick() == client.getNick())
						{
							break;
						}
					}
					if (i == this->getChannels()[j].getInvitedClients().size())
					{
						writeRPL(client.getFd(), ERR_INVITEONLYCHAN(client.getNick(), channelList[i].getName()));
						return;
					}
				}
				if (this->getChannels()[j].getMode_k() && this->getChannels()[j].getKey() != line.substr(line.find(" ", line.find("#")) + 1))
				{
					writeRPL(client.getFd(), ERR_BADCHANNELKEY(client.getNick(), channelList[i].getName()));
					std::cout << "key is " << this->getChannels()[j].getKey() << " and the key given is " << line.substr(line.find(" ", line.find("#")) + 1) << std::endl;
					return;
				}
				if (this->getChannels()[j].getMode_l() && static_cast<int>(this->getChannels()[j].getClients().size()) >= atoi(this->getChannels()[j].getUserLimit().c_str()))
				{
					writeRPL(client.getFd(), ERR_CHANNELISFULL(client.getNick(), channelList[i].getName()));
					return;
				}
				this->_channels[j].addClient(&client);	
				break;
			}
		}
		if (!channelExists)
		{
			Channel newChannel(channelList[i].getName());
			this->_channels.push_back(newChannel);
			this->_channels[this->_channels.size() - 1].addClient(&client);
			this->_channels[this->_channels.size() - 1].addOperator(&client);
		}
		
		std::cout << "Client " << client.getUser() << " joined channel " << channelList[i].getName() << std::endl;
		for (std::size_t j = 0; j < this->_channels.size();j++)
		{
			if (this->_channels[j].getName() == channelList[i].getName())
			{
				for (std::size_t k = 0; k < this->_channels[j].getClients().size(); k++)
				{
					writeRPL(this->_channels[j].getClients()[k]->getFd(), RPL_JOIN(client.getNick(), client.getUser(), channelList[i].getName()));
					if (!channelExists)
						this->_channels[j].setTopic("No topic is set");
					writeRPL(this->_channels[j].getClients()[k]->getFd(), RPL_TOPIC(client.getNick(), channelList[i].getName(), this->_channels[j].getTopic())); // message de reponse au client indiquant le topic du channel.
				}
			}
		}

		for (std::size_t m = 0; m < this->_channels.size(); m++)
		{
			if (this->_channels[m].getName() == channelList[i].getName())
			{
				for (std::size_t n = 0; n < this->_channels[m].getClients().size(); n++)
				{
					writeRPL(this->_channels[m].getClients()[n]->getFd(), RPL_NAMREPLY(client.getNick(), this->_channels[m].getName(), allNicks(this->_channels[m])));
					writeRPL(this->_channels[m].getClients()[n]->getFd(), RPL_ENDOFNAMES(client.getNick(), channelList[i].getName()));
				}
			}
		}
	}
}
