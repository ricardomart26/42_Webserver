#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include "Request.hpp"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <vector>
#include <fstream>

#include "utils.hpp"
#include "Header.hpp"
#include "MyQueue.hpp"
#include "FileWrapper.hpp"
#include "Request.hpp"

class Response {

	public:

		typedef std::string string;

		Response(Request *_request, int clientFd, size_t status_code);
		virtual	~Response();
		void	ConvertHttpRequestToMap(const std::string &msg);
		std::pair<std::string, std::string>	splitHeaderAttribute(const std::string &s, char sep);

		virtual void	sendToClient(const Request &request) = 0;
		bool			finished();

		static unsigned int _WRITE_SIZE;

	protected:

		int	handlePhp(Request *request);
		
		std::map<std::string, std::string>	_map;
		std::string							_body;
		string	_path;
		int		_clientSocket;
		string	_contentLength;
		string	_contentType;
		string	_statusLine;
		Header	_rh;
		MyQueue _queue;
		FileWrapper	_file;
		string	_reason_phrase;
		unsigned short _status_code;
};

#endif