#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <cstddef>
#include <iostream>
#include <unistd.h>
// #include <string.h>

#include "Request.hpp"
#include "ServerBlock.hpp"
#include "utils.hpp"
#include "Get.hpp"
#include "Post.hpp"
#include "Delete.hpp"


#define ERROR_PAGE "/Users/rimartin/Desktop/42_WebServer/web_files/error.html"

class Client
{
	public:

		Client(int fd, const std::vector<ServerBlock *> sb);
		// Client(size_t buffer_size);
		Client(const Client &cp);
		Client &operator=(const Client &rhs);
		~Client();

		bool	create_response();
		bool	create_request();
		Request	&get_request() const;
		int		get_client_socket() const;
		Request	*get_request_addr() const;



	private:

		bool		send_http_error(unsigned short code);
		bool		is_finished();
		Response	*init_response(int clientFd);
		
		int				_client_socket;
		static size_t	_read_size;
		bool			_keep_alive;
		Request			*_request;
		Response		*_response;
		bool			_finished;
		const std::vector<ServerBlock *>	_sb;		
};

#endif
