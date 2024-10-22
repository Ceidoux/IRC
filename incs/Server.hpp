#ifndef SERVER_HPP
#define SERVER_HPP

# include "irc.h"

class Client;
class Channel;
class Server
{
public:
	Server( char * port, char * pass );
	virtual ~Server( void );

	void createServer( void );
	void readInputs( void );
	bool checkIfPasswordValid( std::string const & pwd ) const;

	struct pollfd * getfd0addr( void ) const;
	int getnfds( void ) const;

	void clientRegistration( std::string command, Client & myClient );

	class WrongPortException: public std::exception
	{
	private:
		const char * _message;	
	public:
		WrongPortException(char * msg) : _message(msg) {}
		virtual const char *what(void) const throw() { return _message; }
	};

	class CreateServerException: public std::exception
	{
	private:
		const char * _message;
	public:
		CreateServerException(char * msg) : _message(msg) {}
		virtual const char *what(void) const throw() { return _message; }
	};

	class NewClientException: public std::exception
	{
	private:
		const char * _message;
	public:
		NewClientException(char * msg) : _message(msg) {}
		virtual const char *what(void) const throw() { return _message; }
	};

public:
	std::vector <Channel>		getChannels( void ) const;
private:
	const int					_port;
	const std::string			_pass;
	int							_nfds;
	std::vector <struct pollfd>	_fds; 
	std::vector <Client>		_clients;
	std::vector <Channel>		_channels;

	void	acceptClient( void );
	void	readFromClient( int i );
	bool	checkNickCollision( std::string nickTested );
	void	command( std::string buff, Client & client );
	void	join( std::string line, Client & client );
	void	privmsg( std::string line, Client & client );
	void	ping( std::string line, Client & client );
	void	nick( std::string line, Client & client );
	void	quit( std::string line, Client & client );
	void	part( std::string line, Client & client );
	void	kick( std::string line, Client & client );
	void	topic( std::string line, Client & client );
	void	invite( std::string line, Client & client );
	void	mode( std::string line, Client & client );
};

#endif