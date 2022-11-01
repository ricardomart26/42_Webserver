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

		class Request_empty : public std::exception
		{
			const char *what() const throw() { return ("Request Empty"); }
		};

		class ServerBlockNotFound : public std::exception
		{
			const char *what() const throw() { return ("Server Block Not Found"); }
		};

		Request(int client_fd, const std::vector<ServerBlock *> sb);
		~Request();

		
		void		HTTPRequestToMap(const std::string &msg);
		std::pair<std::string, std::string>	splitHeaderAttribute(c_string &s, char sep);
		std::string	&get_map_value(c_string value);
		std::map<std::string, std::string>	&get_map();


		c_string	&get_path() const;
		map_type	&get_info();
		c_string	&get_http_version() const;
		c_string	&get_method() const; 
		c_string	&get_host();
		c_string	&get_connection_type(); 
		c_string	&get_body() const;
		c_string	&get_filename() const;
		c_string	&get_query_string() const;
		c_string	&get_referer();
		c_string	&get_content_type();
		c_string	&get_sec_fetch_dest();
		c_string	&get_location_header();

		friend std::ostream &operator<<(std::ostream &out, Request &req);
		static unsigned int	_READ_SIZE;

	private:

		string		&remove_query();
		ServerBlock	*selectServerBlock(const std::string &host);

		
		map_type					_map;
		std::string					_path;
		std::string					_body;
		std::string					_query_string;
		FileWrapper						_file;
		LocationHandler				*_location_handler;
		std::vector<std::string>	_request_line;
		std::vector<ServerBlock*>	_sb;

		
};

#endif
