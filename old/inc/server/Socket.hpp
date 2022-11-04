#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <netdb.h>

#include "utils.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Poll.hpp"

extern const int RECV_BUFFER;
extern const int SEND_BUFFER;
#define MAX_CONN 255

class Socket
{
	public:

		Socket(int domain, int type, int protocol, const ServerBlock &sb, size_t port);
		~Socket();

		void		socket_bind(size_t port);
		void		socket_listen(int con);
		int			socketAccept();

		void		socket_getRead_and_write_size();
		int			getSocket();
		Poll		*getPoll();
		ServerBlock	getServerBlock();

	
	protected:

		int					_read_size;
		struct sockaddr_in	_sock_addr;
		int					_server_socket;
		int					_address_family;
		int					_port;
		Poll				*_poll;
		ServerBlock			_sb;
};

#endif
