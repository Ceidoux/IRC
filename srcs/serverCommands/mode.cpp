# include "../../incs/irc.h"

int	setmode(std::vector<Channel> &channels, std::string &channel, std::string mode, bool &status, std::string &arguments, std::string &initial_arguments)
{
	std::size_t i = 0;
	while (i < channels.size())
	{
		if (channels[i].getName() == channel)
			break;
		i++;
	}
	if (i == channels.size())
	{
		std::cout << "Channel does not exist" << std::endl;
		return 1;
	}
	if (mode == "i")
	{
		channels[i].setMode_i(status);
	}
	else if (mode == "t")
	{
		channels[i].setMode_t(status);
	}
	else if (mode == "k")
	{
		int previous_status = channels[i].getMode_k();
		channels[i].setMode_k(status);
		if (status == false)
		{
			channels[i].setKey("");
			return 0;
		}
		else
		{

			if (arguments == "")
			{
				if (previous_status == 0)
					channels[i].setMode_k(false);
				writeRPL(channels[i].getClients()[0]->getFd(), ERR_INVALIDKEY(channels[i].getClients()[0]->getNick(), channel));
				return 1;
			}
			std::string key = arguments.substr(0, arguments.find(" "));
			channels[i].setKey(key);
			initial_arguments += key;
			if (arguments.find(" ") != std::string::npos)
				initial_arguments += " ";
			arguments = arguments.substr(arguments.find(" ") + 1);
			std::cout << "key: " << key << std::endl;
			if (channels[i].getMode_k())
				std::cout << "k is set" << std::endl;
		}
	}
	else if (mode == "o")
	{
		if (status == true)
		{
			std::string operatorNick = arguments.substr(0, arguments.find(" "));
			std::size_t j = 0;
			while (j < channels[i].getClients().size())
			{
				if (channels[i].getClients()[j]->getNick() == operatorNick)
					break;
				j++;
			}
			if (j == channels[i].getClients().size())
			{
				std::cout << "User is not in the channel" << std::endl;
				return 1;
			}
			for (std::size_t k = 0; k < channels[i].getOperators().size(); k++)
			{
				if (channels[i].getOperators()[k]->getNick() == operatorNick)
				{
					std::cout << "User is already an operator" << std::endl;
					return 1;
				}
			}
			channels[i].addOperator(channels[i].getClients()[j]);
			arguments = arguments.substr(arguments.find(" ") + 1);
			std::cout << "operatorNick: " << operatorNick << std::endl;
		}
		else
		{
			std::string operatorNick = arguments.substr(0, arguments.find(" "));
			std::size_t j = 0;
			while (j < channels[i].getClients().size())
			{
				if (channels[i].getClients()[j]->getNick() == operatorNick)
					break;
				j++;
			}
			if (j == channels[i].getClients().size())
			{
				std::cout << "User is not in the channel" << std::endl;
				return 1;
			}
			int w = 0;
			while (w < static_cast<int>(channels[i].getOperators().size()))
			{
				if (channels[i].getOperators()[w]->getNick() == operatorNick)
					break;
				w++;
			}
			if (w == static_cast<int>(channels[i].getOperators().size()))
			{
				std::cout << "User is not an operator" << std::endl;
				return 1;
			}
			channels[i].removeOperator(channels[i].getClients()[j]);
			arguments = arguments.substr(arguments.find(" ") + 1);
			std::cout << "operatorNick: " << operatorNick << std::endl;
		}
	}
	else if (mode == "l")
	{
		channels[i].setMode_l(status);
		if (status == false)
		{
			channels[i].setUserLimit("");
			return 0;
		}
		else
		{
			std::string userLimit = arguments.substr(0, arguments.find(" "));
			channels[i].setUserLimit(userLimit);
			initial_arguments += userLimit;
			if (arguments.find(" ") != std::string::npos)
				initial_arguments += " ";
			arguments = arguments.substr(arguments.find(" ") + 1);
			std::cout << "userLimit: " << userLimit << std::endl;
		}
	}
	return 0;
}

bool 	have_set_modes(Channel channel)
{
	
	if (channel.getMode_i() || channel.getMode_t() || channel.getMode_k() || channel.getMode_l())
		return true;
	return false;
}

// bool	have_unset_modes(Channel channel)
// {
// 	if (!channel.getMode_i() && !channel.getMode_t() && !channel.getMode_k() && !channel.getMode_l())
// 		return true;
// 	return false;
// }

bool mode_with_argument(Channel channel)
{
	if (channel.getMode_k() || channel.getMode_l())
		return true;
	return false;
}

std::string	modestring_maker(Channel channel)
{
	std::string modestring;
	if (have_set_modes(channel))
	{
		modestring = "+";
		if (channel.getMode_i())
			modestring += "i";
		if (channel.getMode_t())
			modestring += "t";
		if (channel.getMode_k())
			modestring += "k";
		if (channel.getMode_l())
			modestring += "l";
		if (mode_with_argument(channel))
		{
			modestring += " ";
			if (channel.getMode_k())
				modestring += channel.getKey();
			if (channel.getMode_l())
				modestring += " " + channel.getUserLimit();
		}
	}
	else
		modestring = "";
	return modestring;
}

std::string only_good_chars(std::string &modes)
{
	std::string good_chars = "tkoil+-";
	std::string new_modes = "";
	for (std::size_t i = 0; i < modes.length(); i++)
	{
		if (good_chars.find(modes[i]) != std::string::npos && new_modes.find(modes[i]) == std::string::npos)
			new_modes += modes[i];
	}
	return new_modes;
}


void	Server::mode( std::string line, Client & client )
{
	int flag = 0;
	if (line.find("#") == std::string::npos)
	{
		std::string client_nick = line.substr(line.find(" ") + 1, line.find(" ", line.find(" ") + 1) - line.find(" ") - 1);
		std::string modes = line.substr(line.find(" ", line.find(" ") + 1) + 1);
		std::cout << "Here is the client: " << client_nick << std::endl;
		std::cout << "Here is the modes: " << modes << std::endl;
		return;
	}
	std::string channel = line.substr(line.find("#"), line.find(" ", line.find("#")) - line.find("#"));
	if (line.size() == channel.size() + std::string("MODE ").size()) 
	{
		for (std::size_t i = 0; i < this->_channels.size(); i++)
		{
			if (this->_channels[i].getName() == channel)
			{
				std::string modestring = modestring_maker(this->_channels[i]);
				writeRPL(client.getFd(), RPL_CHANNELMODEIS(client.getNick(), channel, modestring));
				std::cout << "modestring: " << modestring << std::endl;
				return;
			}
		}
	}
	std::string modes = line.substr(line.find(" ", line.find("#") + 1) + 1, line.find(" ", line.find(" ", line.find("#") + 1) + 1) - line.find(" ", line.find("#") + 1) - 1);
	modes = only_good_chars(modes);
	std::string arguments = line.substr(line.find(" ", line.find(" ", line.find("#") + 1) + 1) + 1);
	if (arguments == line)
		arguments = "";
	// if (arguments.substr(0, 4) == "MODE")
	// {

	// }
	std::cout << "channel: " << channel << std::endl;
	std::cout << "modes: " << modes << std::endl;
	std::cout << "arguments: " << arguments << std::endl;
	std::string initial_arguments;
	bool status;
	if (modes[0] == '+')
		status = true;
	else if (modes[0] == '-')
		status = false;
	else
	{
		std::cout << "Invalid mode" << std::endl;
		return;
	}
	for (std::size_t i = 0; i < modes.length(); i++)
	{
		if (modes[i] == '+')
			status = true;
		else if (modes[i] == '-')
			status = false;
		else
		{
			flag = setmode(this->_channels, channel, std::string(1, modes[i]), status, arguments, initial_arguments);
			if (flag == 1)
			{
				writeRPL(client.getFd(), ERR_INVALIDMODEPARAM(client.getNick(), channel, "+" + std::string(1, modes[i]), arguments));
				return;
			}
		}
	}
	std::cout << "Initial arguments: " << initial_arguments << std::endl;
	std::string modeMessage = ":" + client.getNick() + "!" + client.getUser() + "@localhost MODE " + channel + " " + modes + " " + initial_arguments + "\r\n";
	for (std::size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i].getName() == channel)
		{
			for (std::size_t j = 0; j < this->_channels[i].getClients().size(); j++)
			{
				if (this->_channels[i].getMode_k())
					std::cout << "Again, k is set" << std::endl;
				else
					std::cout << "k is not set" << std::endl;
				std::cout << "Mode message: " << modeMessage << std::endl;
				writeRPL(this->_channels[i].getClients()[j]->getFd(), modeMessage);
			}
			break;
		}
	}
}