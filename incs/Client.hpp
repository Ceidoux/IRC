#ifndef CLIENT_HPP
#define CLIENT_HPP

# include "irc.h"

class Server;

class Client
{
public:
	Client( void );
	Client( int fd, char * ip );
	Client( Client const & src );
	Client & operator=( Client const & src );
	bool 	 operator==( Client const & rhs ) const;
	virtual ~Client( void );

	int getFd( void ) const;
	std::string getNick( void ) const;
	std::string getUser( void ) const;
	std::string getBuffer( void ) const;
	bool getIsRegistered( void ) const;
	bool getIsPasswordValid( void ) const;

	void setNick( std::string nick );
	void setUser( std::string user );
	void setBuffer( std::string buffer );
	void setIsRegistered( bool isRegistered );
	void setIsPasswordValid( bool isPasswordValid );

	bool validNick( std::string nick );

	void eraseAttributes( void );

private:
	int			_fd;
	std::string	_ip;
	std::string	_nick;
	std::string	_user;
	std::string	_buffer;
	bool		_isRegistered;
	bool		_isPasswordValid;
};

#endif