#include "../incs/Server.hpp"

/* BINDING SERVER TO A SOCKET */

void	Server::createServer( void )
{
	struct sockaddr_in	server_addr;
	struct protoent		*proto;
	struct pollfd		server;
	int 				level = 1;

	proto = getprotobyname("tcp");
	if (!proto)
		throw Server::CreateServerException((char *)"getprotobyname() failed");
	server.fd = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (server.fd < 0)
		throw Server::CreateServerException((char *)"socket() failed");
	std::cout << "\033[0;32mSocket created\nServer fd: " << server.fd << "\033[0m" << std::endl;

	std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->_port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  
	setsockopt(server.fd, SOL_SOCKET, SO_REUSEADDR, &level, sizeof(level));
	if (fcntl(server.fd, F_SETFL, fcntl(server.fd, F_GETFL) | O_NONBLOCK) == -1) // set fd to non-blocking
		throw Server::CreateServerException((char *)"fcntl() failed");
	if (bind(server.fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		throw Server::CreateServerException((char *)"bind() failed");
	if (listen(server.fd, LISTEN_BACKLOG) == -1)
		throw Server::CreateServerException((char *)"listen() failed");
	server.events = POLL_IN;
	this->_fds.push_back(server);
	this->_nfds++;
	Client	myServer(server.fd, (char *)"127.0.0.1");
	this->_clients.push_back(myServer); // first client being server to keep both vectors (_clients & _fds) with same index
}

/* READING SOCKET INPUT */

void Server::readInputs( void )
{
	if (this->_fds[0].revents & POLLIN)
		this->acceptClient();
	for (int i = 1; i < this->_nfds; ++i)
		if (this->_fds[i].fd && (this->_fds[i].revents & POLLIN))
			this->readFromClient(i);
}

/* ACCEPTING NEW CLIENT */

void	Server::acceptClient( void )
{
	struct pollfd		client;
	struct sockaddr_in	client_addr;
	socklen_t			client_addr_size;

	client_addr_size = sizeof(client_addr);
	client.fd = accept(this->_fds[0].fd, (struct sockaddr*)&client_addr, &client_addr_size);
	if (client.fd == -1)
		throw Server::NewClientException((char *)"accept() failed");
	std::cout << "New client #" << client.fd << " from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;
	if (fcntl(client.fd, F_SETFL, fcntl(client.fd, F_GETFL) | O_NONBLOCK) == -1) // set fd to non-blocking
		throw Server::NewClientException((char *)"fnctl() failed");
	client.events = POLL_IN;
	this->_fds.push_back(client);
	this->_nfds++;

	Client	myClient(client.fd, inet_ntoa(client_addr.sin_addr));
	this->_clients.push_back(myClient);
}

/* DEALING CLIENT MESSAGE */

void Server::readFromClient( int i )
{
	ssize_t		ret;
	char		buffer[BUFFER_SIZE + 1];
	std::string	command;

	std::memset(buffer, 0, sizeof(buffer));
	ret = read(this->_fds[i].fd, buffer, BUFFER_SIZE);
	if (ret <= 0)
	{
		std::cout << "Client #" << this->_fds[i].fd << " has left the server" << std::endl;
		this->_clients[i].eraseAttributes();
		close(this->_fds[i].fd);
		this->_fds[i].fd = 0;
		/* A TESTER:
		this->_clients.erase(this->_clients.begin() + i);
		this->_fds.erase(this->_fds.begin() + i);
		*/
	}
	else
	{
		buffer[ret] = '\0';
		std::cout << "\033[0;104mCLIENT #" << this->_fds[i].fd << " > SERVER\033[0;34m " << buffer << "\033[0m";
		this->_clients[i].setBuffer(this->_clients[i].getBuffer() + buffer);
		while (this->_clients[i].getBuffer().find("\r\n") != std::string::npos)
		{
			command = this->_clients[i].getBuffer().substr(0, this->_clients[i].getBuffer().find("\r\n"));
				this->_clients[i].setBuffer(this->_clients[i].getBuffer().substr(this->_clients[i].getBuffer().find("\r\n") + 2));
			if (this->_clients[i].getIsRegistered() == true)
				this->command(command, this->_clients[i]);
			else
				clientRegistration(command, this->_clients[i]);
		}
	}
}

/* REGISTER NEW CLIENT */

bool Server::checkNickCollision( std::string nickTested )
{
	unsigned long	i(0);

	for (i = 0; i < this->_clients.size(); ++i)
		if (this->_clients[i].getNick() == nickTested)
			return true;
	return false;
}

void Server::clientRegistration( std::string command, Client & myClient )
{
	if (this->_pass == "")
		myClient.setIsPasswordValid(true);
	/* first command must be CAP or PASS otherwise ERR_PASSWDMISMATCH */
	if (command.compare(0, 4, "CAP ") && command.compare(0, 5, "PASS ") && myClient.getIsPasswordValid() == false)
	{
		std::cout << "\033[0;31mNo password given\033[0m" << std::endl;
		writeRPL(myClient.getFd(), ERR_PASSWDMISMATCH(myClient.getNick()));
	}
	else if (!command.compare(0, 5, "PASS ") && this->checkIfPasswordValid(command.substr(5)))
		myClient.setIsPasswordValid(true);
	else if (!command.compare(0, 5, "NICK "))
	{
		if (!myClient.validNick(command.substr(5)))
			writeRPL(myClient.getFd(), ERR_ERRONEUSNICKNAME(command.substr(5)));
		else if (checkNickCollision(command.substr(5)))
			writeRPL(myClient.getFd(), ERR_NICKCOLLISION(command.substr(5)));
		else
			myClient.setNick(command.substr(5));
	}
	else if (!command.compare(0, 5, "USER "))
		myClient.setUser(command.substr(5, command.find(" ", 5) - 5));
	
	/* PASS, NICK and USER can be sent in several packages. Check if the 3 of them have been sent to register */
	if (myClient.getIsPasswordValid() && myClient.getNick() != "" && myClient.getUser() != "")
	{
		writeRPL(myClient.getFd(), RPL_WELCOME(myClient.getNick()));
		writeRPL(myClient.getFd(), RPL_YOURHOST(myClient.getNick()));
		writeRPL(myClient.getFd(), RPL_CREATED(myClient.getNick()));
		writeRPL(myClient.getFd(), RPL_MYINFO(myClient.getNick()));
		myClient.setIsRegistered(true);
	}	
}

/* PASSWORD CHECK */

bool Server::checkIfPasswordValid( std::string const & pwd ) const
{
	if (pwd.compare(this->_pass) == 0)
	{
		std::cout << "\033[0;32mPassword is correct\033[0m" << std::endl;
		return (true);
	}
	std::cout << "\033[0;31mPassword is incorrect\033[0m" << std::endl;
	return (false);
}
