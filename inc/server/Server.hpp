#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <netdb.h>

#include "Socket.hpp"
#include "Config.hpp"
#include "Client.hpp"
#include "Poll.hpp"
#include "Directives.hpp"

#ifndef DEBUG
	#define DEBUG 0
#endif

class Server : protected Config
{
	public:

		Server();
		Server(const char *filename);
		~Server();

		void	setup_sockets();
		void	run();
		size_t	nbr_of_servers() const;
		ServerBlock	*TestegetServerBlock(size_t i);

	private:
		
		void							remove_client(std::vector<Client *>::iterator client, Socket *socket);
		std::vector<Client *>::iterator	get_client(int event_fd);
		void							handle_event(Socket *socket, pollfd *event);

		std::vector<Client *>	_clients;
		// bool					_keep_alive;
		std::vector<Socket *>	_socket_set;
};

#endif
