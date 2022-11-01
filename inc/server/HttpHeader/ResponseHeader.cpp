#include "ResponseHeader.hpp"

ResponseHeader::ResponseHeader()
{
	// Access-Control-Allow-Origin: *
	// Etag
	// Server: Webserver
	_server = "Server: WebServer\r\n";
	// X-Frame-Options: DENY
}

ResponseHeader::~ResponseHeader() {}

std::string ResponseHeader::get_response_header() 
{ 
	return (_server); 
}

