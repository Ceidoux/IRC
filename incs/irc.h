#ifndef IRC_H
#define IRC_H

# include <iostream>
# include <exception>
# include <cstdio>			// perror
# include <sys/socket.h>	// socket, bind, listen, inet_ntoa
# include <sys/types.h>		// bind, listen
# include <cstring>			// memset
# include <netinet/in.h>	// sockaddr_in, inet_ntoa
# include <arpa/inet.h>		// inet_ntoa
# include <sys/select.h>	// select
# include <unistd.h>		// close
# include <cstring>			// strlen, memset
# include <string>			// getline
# include <cstdlib>			// EXIT_SUCCESS, EXIT_FAILURE
# include <fstream>			// std::fstream
# include <string.h>		// strcmp
# include <cctype>			// isdigit
# include <vector>
# include <algorithm>		// max
# include <netdb.h>			// getprotobyname
# include <fcntl.h>			// fcntl
# include <poll.h>			// poll
# include <signal.h>		// poll, sigaction

# include "rpl.h"
# include "err.h"
# include "Server.hpp"
# include "Client.hpp"
# include "Channel.hpp"

# define LISTEN_BACKLOG 50
# define BUFFER_SIZE	8192

/* Prototypes */
class Server;
class Client;

void	writeRPL( int fd, std::string RPL );

#endif