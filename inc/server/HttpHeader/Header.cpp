#include "Header.hpp"

Header::Header() 
{

}

Header::~Header() 
{

}

void	Header::set_entity_header(string &file_ext, size_t len, c_string  &type)
{ 
	_entity_header += EntityHeader(file_ext, len, type).get_entity_header(); 
}

void	Header::set_response_header() 
{ 
	_response_header += ResponseHeader().get_response_header(); 
}

void	Header::set_general_header() 
{ 
	_general_header += GeneralHeader().get_general_header(); 
}

bool	Header::is_empty() const
{
	return (get_header().empty());
}

const std::string Header::get_header() const 
{
	return (_entity_header + _response_header + _general_header); 
}

void	Header::add_response_header(c_string header)
{
	_response_header += header;
}

void	Header::add_entity_header(c_string &header)
{
	_entity_header += header;
}

void	Header::add_general_header(c_string &header)
{
	_general_header += header;
}
