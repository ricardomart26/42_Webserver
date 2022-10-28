#include "Location.hpp"

size_t	until_alpha(const std::string &str, size_t i)
{
	while (str[i] && !isalpha(str[i]))
		i++;
	return (i);
}

Location::Location(const std::string &block, std::map<std::string, Directives*> m) : _m(m)
{
	std::cout << "Location block: " << block << std::endl;
	_prefix = trim(block.substr(0, block.find('{')), SPACES);
	std::cout << "Prefix is: " << _prefix << std::endl;
	_content = block.substr(block.find('{') + 1);
	for (size_t i = 0; _content[i]; i = until_alpha(_content, i))
	{
		std::string sliced = slice_str(_content, SPACES, i);
		if (sliced.empty())
			break ;

		std::string end = SPACES;

		if (sliced == "limit_except")
			end = "}";
		_m[sliced]->action(slice_str(_content, end, ++i), LOCATION);
	}
}

Location::~Location()
{

}


Location::Location(const Location &cpy)
{
	_prefix = cpy._prefix;
	_m = cpy._m;
	_index = cpy._index;
	_content = cpy._content;
}

const Location &Location::operator=(const Location &rhs)
{
	if (this == &rhs)
	{
		std::cout << "Prefix is: " << _prefix << std::endl;
		this->_prefix = rhs._prefix;

		std::map<std::string, Directives*>::const_iterator it = rhs._m.begin();
		for (; it != rhs._m.end(); it++)
			this->_m[it->first] = it->second;

		std::vector<std::string>::const_iterator it_loc = rhs._index.begin();
		for (; it_loc != rhs._index.end(); it_loc++)
			this->_index.push_back(*it_loc);
	}
	return (*this);
}


const std::string &Location::get_prefix() const
{
	return (_prefix);
}

const std::vector<std::string>	&Location::get_index() const
{
	return (_index);
}

