#include "Config.hpp"

// PARSING DONT WORK IF THERE IS NOT A NEW LINE IN THE END OF THE FILE....

/** @brief Receives a configuration file, see if file exists, 
 * and parse the file to pass information to the server */
Config::Config(const char *filename)
: _file(200), _checker()
{
	_file.open(filename);
	_file.read();
	_content = _file.get_content();
}

ServerBlock	*Config::getServerBlock(size_t i)
{
	if (i >= _server_block.size())
		return (NULL);
	return (_server_block[i]);
}

std::vector<ServerBlock*>	&Config::getServerBlockVec()
{
	return (_server_block);
}


void	Config::removeEmptyNewLines()
{
	erase_while_is(_content, '\n');
	int index = _content.length();
	while (index > 0)
	{
		int exist = 0;
		while (index > 0 && _content[index] != '\n')
			index--;
		while (index > 0 && _content[--index] != '\n')
		{
			if (!isspace(_content[index]))
				exist++;
		}
		if (!exist)
			_content.erase(index, 1);
	}
}

void	Config::fileValidator()
{

	if (invalidEndOfLine())
		throw ConfigCheckEndLine();
	if (invalidBrackets())
		throw ConfigCheckOpenings();
}

void	Config::parse_server()
{
	size_t i = 0;
	std::string to_find = ;

	while (i < _content.length())
	{
		int pos = _content.find("server", i);
		if (pos == -1)
			break ;
		
		i = pos + 6;
		
		while (!isalpha(_content[i]))
			i++;

		pos = i;
		size_t counter = 1;
		while (counter && _content[i]) 
		{
			if (_content[i] == '{')
				counter++;
			else if (_content[i] == '}')
				counter--;
			i++;
		}
		_server_block.push_back(new ServerBlock(_content.substr(pos, i - pos - 1)));
		_server_block[_server_block.size() - 1]->parseFile();
	}
}

int Config::invalidEndOfLine()
{
	int index = _content.length() - 1;
	while (index > -1)
	{
		if (_content[index] == '\n')
		{
			while (index > 0 && isspace(_content[index])) 
				index--;

			if (_content[index] == ';')
			{
				if (!isDirectives(index - 1))
					return (1);
			}
			else if (_content[index] == '{')
			{
				if (!isContext(index - 1))
					return (1);
				index--;
			}
			continue ;
		}
		index--;
	}
	return (0);
}

bool	Config::invalidBrackets()
{
	int open = 0;
	int close = 0;
	int index = 0;

	while (_content[index])
	{
		if (_content[index] == '{')
			open++;
		else if (_content[index] == '}')
		{
			if (open <= close)
				return (true);
			close++;
		}
		index++;
	}
	if (open != close)
		return (true);
	return (false);
}

bool	Config::isContext(int index)
{
	while (index > 0 && _content[index] != ';')
		index--;

	while (_content[index] && !isalpha(_content[index]))
		index++;

	int save_index = index;

	while (_content[save_index] &&  !isspace(_content[save_index]))
		save_index++;

	std::string sub = _content.substr(index, save_index - index);

	if (_confInfo.is_context(sub))
		return (1);

	if (!sub.compare("GET") || !sub.compare("POST") || !sub.compare("DELETE"))
		return (is_context(index - 1));

	return (0);
}

bool	Config::isDirectives(int index)
{
	while (index - 1 > 0 && (_content[index - 1] != ';' && 
	_content[index - 1] != '{' && _content[index - 1] != '}'))
		index--;

	if (index - 1 == 0)
		return (false);

	while (_content[index] && (!isprint(_content[index]) || isspace(_content[index])))
		index++;

	int save_index = index;
	while (isalpha(_content[index]) || _content[index] == '_') 
		index++;

	if (_confInfo.is_directive(_content.substr(save_index, index - save_index)))
		return (true);

	return (false);
}



Config::~Config() 
{
	for (size_t i = 0; i < _server_block.size(); i++)
		delete _server_block[i];
}
