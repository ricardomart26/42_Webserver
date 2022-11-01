#include "GeneralHeader.hpp"

GeneralHeader::GeneralHeader()
{
	// Connection: Keep-Alive
	_connection = CONNECTION;
	_date = getTime();
	// Keep-Alive: timeout=xs max=y
	// _keep_alive = KEEP_ALIVE;
	// _keep_alive = 
	// Transfer-Encoding
}

GeneralHeader::~GeneralHeader() {}

std::string GeneralHeader::get_general_header() 
{ 
	return (_connection + _date + _keep_alive); 
}
