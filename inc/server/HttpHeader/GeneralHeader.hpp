#ifndef GENERALHEADER_HPP
#define GENERALHEADER_HPP

#include <cstring>
#include <string>
#include "utils.hpp"

const std::string CONNECTION = "Connection: keep-alive\r\n";
const std::string KEEP_ALIVE = "Keep-Alive: timeout=10 max=4\r\n";

class GeneralHeader 
{
	typedef std::string string;

	public:

		GeneralHeader();
		~GeneralHeader();

		string get_general_header();

	private:

		string	_connection;
		string	_date;
		string	_keep_alive;
};

#endif
