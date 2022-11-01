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

		Socket(int domain, int type, int protocol, const ServerBlock &sb);
		~Socket();

<<<<<<< HEAD
		void		socket_bind(size_t port);
		void		socket_listen(int con);
		int			socket_accept();
=======
		void		socket_config(int opt = 1);
		void		socket_bind(size_t port, const std::string &server_name);
		void		socket_listen(int con);
		int			socket_accept();
		// void		set_server_block(ServerBlock &sb);
>>>>>>> 1c694832cd7dacfca0d60e01751aee90f0e8c3ec

		void		socket_get_read_and_write_size();
		int			get_socket();
		Poll		*get_poll();
		ServerBlock	get_server_block();

<<<<<<< HEAD
	
=======

>>>>>>> 1c694832cd7dacfca0d60e01751aee90f0e8c3ec
	protected:

		int					_read_size;
		struct sockaddr_in	_sock_addr;
		int					_server_socket;
		int					_address_family;
		int					_port;
		Poll				*_poll;
		ServerBlock			_sb;
};

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> 1c694832cd7dacfca0d60e01751aee90f0e8c3ec
