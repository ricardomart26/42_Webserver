#include "Server.hpp"

Server::Server(const char *f) : Config(f) {}

Server::~Server() {}

/**
 * @brief Create and setup a set (conjunto) of sockets,
 * to bind them to differente addr and ports depending on the config file.
 */
void	Server::setupSockets()
{
	ServerBlock *sb = NULL;
	for (size_t i = 0; (sb = getServerBlock(i)) != NULL; i++)
	{
		ListenIndv *listenIndv = NULL;
		for (size_t j = 0; (listenIndv = sb->dir<Listen>("listen")->getListenIndv(j)) != NULL ; j++)
			_socket_set.push_back(new Socket(AF_INET, SOCK_STREAM, 0, *sb, listenIndv->getValue().second));
	}
	_socket_set[0]->socket_getRead_and_write_size();
}

/**
 * @brief returns true if is server socket that has something 
 * to be read
 */
bool	isNewConnection(int fd, int server_socket)
{
	return (fd == server_socket);
}


/**
 * @brief returns true if client socket that has something 
 * to be read
 */
bool	isReadyToRead(int revents)
{
	return (revents & POLLIN);
}


/**
 * @brief returns true if client socket that has something 
 * to write
 */
bool	isReadyToWrite(int revents)
{
	return (revents & POLLOUT);
}

std::vector<Client *>::iterator	Server::getClient(int event_fd)
{
	std::vector<Client *>::iterator it = _clients.begin();
	for (; it != _clients.end(); it++) 
	{
		if ((*it)->getClientSocket() == event_fd)
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
	socket->getPoll()->removeEvent((*client)->getClientSocket());
	close((*client)->getClientSocket());
	_clients.erase(client);
}

void	Server::handleEvent(Socket *socket, pollfd *event)
{
	if (isNewConnection(event->fd, socket->getSocket()))
		_clients.push_back(new Client(socket->socketAccept(), getServerBlockVec()));
	else
	{
		try {
			std::vector<Client *>::iterator	client = getClient(event->fd);
			if (isReadyToRead(event->revents))
			{
				if (!(*client)->createRequest())
					remove_client(client, socket);
			}
			else if (isReadyToWrite(event->revents) && (*client)->getRequest() != NULL)
				(*client)->createResponse();
		} catch (const std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
}

void	Server::run()
{
	for (size_t j = 0; Config::getServerBlock(j) != NULL; j++)
	{
		_socket_set[j]->getPoll()->waitForConnection();
		for (size_t i = 0; i < _socket_set[j]->getPoll()->nbrOfEvents(); i++)
			handleEvent(_socket_set[j], _socket_set[j]->getPoll()->getReturnedEvents(i));
	}
}
