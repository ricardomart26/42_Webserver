#ifndef RESPONSEHEADER_HPP
#define RESPONSEHEADER_HPP

#include <cstring>
#include <string>
#include "utils.hpp"

const std::string NO_SNIFF = "X-Content-Type-Options: nosniff\r\n";

class ResponseHeader 
{
	typedef std::string string;

	public:

		ResponseHeader();
		~ResponseHeader();

		string	getResponse_header();

	private:

		string	_server;

};

#endif
