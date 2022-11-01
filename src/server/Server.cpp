#include "Server.hpp"

Server::Server(const char *f) : Config(f) {}

Server::~Server() {}

/**
 * @brief Create and setup a set (conjunto) of sockets,
 * to bind them to differente addr and ports depending on the config file.
 */
void	Server::setup_sockets()
{
	file_checker();
	parse_server();

	ServerBlock *sb = NULL;
	for (size_t i = 0; (sb = getServerBlock(i)) != NULL; i++)
	{
		ListenIndv *listenIndv = NULL;
		for (size_t j = 0; (listenIndv = sb->dir<Listen>("listen")->getListenIndv(j)) != NULL ; j++)
		{
			_socket_set.push_back(new Socket(AF_INET, SOCK_STREAM, 0, *sb));
			_socket_set[_socket_set.size() - 1]->socket_bind(listenIndv->getValue().second);
			_socket_set[_socket_set.size() - 1]->socket_listen(MAX_CONN);
		}
	}
	_socket_set[0]->socket_get_read_and_write_size();
}

bool	is_new_connection(int fd, int server_socket)
{
	return (fd == server_socket); 
}

bool	is_ready_to_read(int revents)
{
	return (revents & POLLIN);
}

bool	is_ready_to_write(int revents)
{
	return (revents & POLLOUT);
}

std::vector<Client *>::iterator	Server::get_client(int event_fd)
{
	std::vector<Client *>::iterator it = _clients.begin();
	for (; it != _clients.end(); it++) 
	{
		if ((*it)->get_client_socket() == event_fd)
			break ;
	}
	return (it);
}

void	Server::remove_client(std::vector<Client *>::iterator client, Socket *socket)
{
	/**
	 * Entra nesta condição quando o request é vazio (acho que é para "fechar" o cliente).
	 * Mas tenho que ter cuidado se o tamanho do request é maior que o que vai ser possivel
	 * para ler (_READ_SIZE), assim vai eliminar o cliente, em vez de ler o resto do pedido!
	 */
	std::cout << "Client Removed\n";
	socket->get_poll()->remove_event((*client)->get_client_socket());
	close((*client)->get_client_socket());
	_clients.erase(client);
}

void	Server::handle_event(Socket *socket, pollfd *event)
{
	if (is_new_connection(event->fd, socket->get_socket()))
		_clients.push_back(new Client(socket->socket_accept(), getServerBlockVec()));
	else
	{
		try {
			std::vector<Client *>::iterator	client = get_client(event->fd);
			if (is_ready_to_read(event->revents))
			{
				if (!(*client)->create_request())
					remove_client(client, socket);
			}
			else if (is_ready_to_write(event->revents) && (*client)->get_request_addr() != NULL)
				(*client)->create_response();
		} catch (const std::exception &e) {
			
		}
	}
}

void	Server::run()
{
	for (size_t j = 0; getServerBlock(j) != NULL; j++)
	{
		_socket_set[j]->get_poll()->wait_for_connection();
		for (size_t i = 0; i < _socket_set[j]->get_poll()->nbr_of_events(); i++)
			handle_event(_socket_set[j], _socket_set[j]->get_poll()->get_returned_events(i));
	}
}

ServerBlock	*Server::TestegetServerBlock(size_t i)
{
	return (Config::getServerBlock(i));
}
