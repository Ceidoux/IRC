#include "Client.hpp"

/* CONSTRUCTORS */

Client::Client( void ) : _fd(0), _nick(""), _user(""), _isRegistered(false), _isPasswordValid(false) { }

Client::Client( int fd, char * ip ) : _fd(fd), _ip(ip), _nick(""), _user(""), _isRegistered(false), _isPasswordValid(false) { }

Client::Client( Client const & src ) : _fd(src._fd), _nick(src._nick), _user(src._user), _isRegistered(src._isRegistered), _isPasswordValid(src._isPasswordValid) { }

/* ASSIGNMENT OPERATOR OVERLAOD */

Client & Client::operator=( Client const & src )
{
	this->_fd = src._fd;
	this->_nick = src._nick;
	this->_user = src._user;
	this->_isRegistered = src._isRegistered;
	return *this;
}

/* COMPARISON OPERATOR OVERLOAD */

bool Client::operator==( Client const & rhs ) const
{
	return this->_fd == rhs._fd;
}

/* DESTRUCTOR */

Client::~Client( void ) { }

/* WELCOME NEW CLIENT */

bool Client::validNick( std::string nick )
{
	char	forbiddenCharacter[6] = {' ', ',', '*', '?', '!', '@'};
	char	forbiddenFirstCharacter[4] = {'$', ':', '#', '&'};

	for (int i = 0; i < 6; ++i)
		if (std::find(nick.begin(), nick.end(), forbiddenCharacter[i]) != nick.end())
			return false;
	for (int i = 0; i < 4; ++i)
		if (nick[0] == forbiddenFirstCharacter[i])
			return false;
	if (std::find(nick.begin(), nick.end(), '.') != nick.end())
		return false;
	return true;
}

/* ERASE ATTRIBUTES */

void Client::eraseAttributes( void )
{
	this->_fd = 0;
	this->_ip = "";
	this->_nick = "";
	this->_user = "";
	this->_buffer = "";
	this->_isRegistered = false;
	this->_isPasswordValid = false;
}

/* GETTERS & SETTERS */

int Client::getFd( void ) const { return this->_fd; }

std::string Client::getNick( void ) const { return this->_nick; }

std::string Client::getUser( void ) const {	return this->_user; }

std::string Client::getBuffer( void ) const { return this->_buffer; }

bool Client::getIsRegistered( void ) const { return this->_isRegistered; }

bool Client::getIsPasswordValid( void ) const { return this->_isPasswordValid; }

void Client::setNick( std::string nick ) { this->_nick = nick; }

void Client::setUser( std::string user ) { this->_user = user; }

void Client::setBuffer( std::string buffer ) { this->_buffer = buffer; }

void Client::setIsRegistered( bool isRegistered ) { this->_isRegistered = isRegistered; }

void Client::setIsPasswordValid( bool isPasswordValid ) { this->_isPasswordValid = isPasswordValid; }
