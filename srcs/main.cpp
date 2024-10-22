#include "../incs/irc.h"

bool g_sigReceived = false;

static void	sigHandler( int sig )
{
	(void) sig;
	g_sigReceived = true;
}

static void	sigInitialize( void )
{
	struct sigaction	sig_int;	/* ctrl-c */
	struct sigaction	sig_quit;	/* ctrl-\ */
	struct sigaction	sig_tstp;	/* ctrl-z */

	std::memset(&sig_quit, 0, sizeof(sig_quit));
	sig_quit.sa_handler = sigHandler;
	sig_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sig_quit, NULL);
	
	std::memset(&sig_int, 0, sizeof(sig_int));
	sig_int.sa_handler = sigHandler;
	sig_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	
	std::memset(&sig_tstp, 0, sizeof(sig_tstp));
	sig_tstp.sa_handler = sigHandler;
	sig_tstp.sa_flags = SA_RESTART;
	sigaction(SIGTSTP, &sig_tstp, NULL);
	
}

int main ( int ac, char *av[] )
{

	if (ac != 3)
	{
		std::cout << "Usage: " << av[0] << " <port> <password>" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	sigInitialize();

	try
	{
		Server	myServer(av[1], av[2]);
		myServer.createServer();
		while (true)
		{
			if (poll(myServer.getfd0addr(), myServer.getnfds(), -1) == -1)
			{
				if (!g_sigReceived)
					std:: cerr << "\033[0;31mError: poll() failed\033[0m" << std::endl;
				break;
			}
			myServer.readInputs();
		}
	}
	catch (std::exception &e)
	{
		std:: cerr << "\033[0;31mError: " << e.what() << "\033[0m" << std::endl;
	}
	return 0;
}