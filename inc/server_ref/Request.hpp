#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <map>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <exception>

#include "utils.hpp"
#include "FileWrapper.hpp"
#include "ServerBlock.hpp"
#include "LocationHandler.hpp"
#include "Directives.hpp"

class Request
{
	public:

		typedef std::string string;
		typedef const string c_string;
		typedef std::map<string, string> map_type;
		typedef const map_type c_map_type;

		class EmptyRequest : public std::exception
		{
			const char *what() const throw() { return ("Request Empty"); }
		};

		class ServerBlockNotFound : public std::exception
		{
			const char *what() const throw() { return ("Server Block Not Found"); }
		};

		Request(int client_fd, ServerBlock * sb);
		~Request();

		
		void		ConvertHttpRequestToMap(const std::string &msg);
		std::pair<std::string, std::string>	splitHeaderAttribute(c_string &s, char sep);
		std::string	&getMapValue(c_string value);
		std::map<std::string, std::string>	&getMap();


		c_string	&getPath() const;
		map_type	&getInfo();
		c_string	&getHttpVersion() const;
		c_string	&getMethod() const; 
		c_string	&getHost();
		c_string	&getConnectionType(); 
		c_string	&getBody() const;
		c_string	&getFilename() const;
		c_string	&getQueryString() const;
		c_string	&getReferer();
		c_string	&getContentType();
		c_string	&getSecFetchDest();
		c_string	&getLocationHeader();

		friend std::ostream &operator<<(std::ostream &out, Request &req);
		static unsigned int	_READ_SIZE;

	private:

		string		&removeQuery();
		
		map_type					_map;
		std::string					_path;
		std::string					_body;
		std::string					_queryString;
		FileWrapper					_file;
		std::vector<std::string>	_requestLine;
		ServerBlock					*_sb;

		
};

#endif
