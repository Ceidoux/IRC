#include "../incs/Server.hpp"

/* OVERLOADED CONSTRUCTOR WITH SERVER'S PORT */

static int addPort( char * p )
{
	int port(0);

	while (*p)
	{
		if (!std::isdigit(*p))
			throw Server::WrongPortException((char *)"wrong port format");
		port = 10 * port + *p - 48;
		if (port > 65535)
			throw Server::WrongPortException((char *)"wrong port format");
		++p;
	}
	if (port < 1024)
		throw Server::WrongPortException((char *)"well known port");
	return port;
}

Server::Server( char * port, char * pass ) : _port(addPort(port)), _pass(pass), _nfds(0)
{
	std::cout << "\033[0;32mServer port: " << this->_port << "\033[0m" << std::endl;
	std::cout << "\033[0;32mServer password: " << this->_pass << "\033[0m" << std::endl;
}

/* DESTRUCTOR */

Server::~Server( void )
{
	for (int i = 0; i < this->_nfds; ++i)
		if (this->_fds[i].fd > 0)
			close(this->_fds[i].fd);
}

/* GETTERS */

int						Server::getnfds( void ) const { return this->_nfds; }

struct pollfd *			Server::getfd0addr( void ) const { return (struct pollfd *)&this->_fds[0]; }

std::vector <Channel>	Server::getChannels( void ) const { return this->_channels; }
