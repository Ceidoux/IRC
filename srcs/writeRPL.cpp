# include "../incs/irc.h"

void	writeRPL( int fd, std::string RPL )
{
	write(fd, RPL.c_str(), RPL.length());
	std::cout << "\033[0;104mSERVER > CLIENT #" << fd << "\033[0;34m " << RPL.c_str() << "\033[0m";
}
