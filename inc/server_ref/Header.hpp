#ifndef HEADER_HPP
#define HEADER_HPP

#include <cstring>
#include <string>
#include "utils.hpp"

#include "EntityHeader.hpp"
#include "ResponseHeader.hpp"
#include "GeneralHeader.hpp"

class Header {

	public:

		typedef std::string string;
		typedef const string c_string;

		Header();
		~Header();

		c_string	get_header() const;
		bool		is_empty() const;

		void		set_entity_header(string &file_ext, size_t len, c_string &type);
		void		set_response_header();
		void		set_general_header();

		void		add_response_header(c_string header);
		void		add_entity_header(c_string &header);
		void		add_general_header(c_string &header);


	private:

		string	_entity_header;
		string	_response_header;
		string	_general_header;

};

#endif
