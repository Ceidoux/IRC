# include "../../incs/irc.h"

void	Server::ping( std::string line, Client & client )
{
    size_t pos = line.find(" ");
    if (pos != std::string::npos) 
	{
        std::string param = line.substr(pos + 1);
        std::string rpl = "PONG " + param + "\r\n";
		writeRPL(client.getFd(), rpl);
    } 
	else 
        std::cerr << "Invalid PING format" << std::endl;
}
