#ifndef ENTITYHEADER_HPP
#define ENTITYHEADER_HPP

#include <cstring>
#include <string>
#include "utils.hpp"


class EntityHeader {

	public:

		typedef std::string string;
		typedef const string c_string;


		EntityHeader(string &file_ext, size_t len, c_string &type);
		~EntityHeader();

		string get_entity_header();

	private:

		string	_content_len;
		string	_content_type;

};

#endif
