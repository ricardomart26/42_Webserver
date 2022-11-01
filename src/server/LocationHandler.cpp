#include "LocationHandler.hpp"

LocationHandler::LocationHandler(const std::string &request, ServerBlock *sb)
{
	(void)request;
	_sb = sb;
	
	// _sb_root = sb_root;
	_location_vec = _sb->getLocation();
	// std::cout << _location_vec.size() << "!" << std::endl;
	// std::cout << sb->getLocation().size() << "!" << std::endl;
	// std::cout << _sb->getLocation().size() << "!" << std::endl;
	
	
	_location = NULL;
}

LocationHandler::~LocationHandler() 
{

}

void	LocationHandler::init(const std::string &path)
{
	size_t i = 0;

	_path = path;
	// Search in location prefix for the best match for request path

	// std::cout << "\nSearch for: " << _path << std::endl;

	for (; i < _location_vec.size(); i++)
	{
		std::cout << "Options are: " << _location_vec[i]->get_prefix() << std::endl;
		if (_location_vec[i]->get_prefix().compare(path) == 0)
		{
			_location = _location_vec[i];
			break ;
		}
	}

	if (i == _location_vec.size() - 1)
	{
		if (_location_vec[i]->get_prefix().compare("/") == 0)
		{
			// std::cout << "Default location" << std::endl;
			_location = _location_vec[i];
		}
	}

	if (_location == NULL)
	{
		// What happens if nginx doest find the location
		error_and_exit("Location error in LocationHandler::init(int, ServerBlock)");
	}

}

void	LocationHandler::get_location_root()
{
	std::string ret;
	std::string location_root = _location->dir<Root>("root")->getValue();
	// std::cout << "Root found is: " << _location->get_root() << std::endl;
	if (location_root.empty())
	{
		if (_sb_root.empty())
		{
			// Send error because it doesn't have a folder to look for files
			error_and_exit("LocationHandler::get_location_root root not found");
		} 
		_path = _sb_root + _path; 
	}
	else
		_path = location_root + _path;

}

std::string	LocationHandler::search_for_path_with_index(const std::vector<std::string> &index_vec)
{
	// std::cout << std::endl;
	for (size_t i = 0; i < index_vec.size(); i++)
	{
		// std::cout << "search for path with index: " << _path + index_vec[i] << std::endl;
		if (fileExists(_path + index_vec[i]))
			return (_path += index_vec[i]);
	}
	return "";
}

void	LocationHandler::search_for_files(const std::vector<std::string> &sb_index_vec, bool auto_index)
{

	std::string new_path;

	new_path = search_for_path_with_index(_location->get_index());
	if (new_path.empty())
	{
		new_path = search_for_path_with_index(sb_index_vec);
		if (new_path.empty())
		{
			if (auto_index == true)
			{
				// Do autoindex page
			}
			else
			{
				// Return 404 page not found
				// EXIT HERE
			}
		}
	}
	_path = new_path;
}


std::vector<Location*>	LocationHandler::get_location_vec() const
{
	return (_location_vec);
}

bool	LocationHandler::emptyLocation() const
{
	return (!_location_vec.size());
}

Location	*LocationHandler::get_location() const
{
	return (_location);
}

const std::string	&LocationHandler::get_path() const
{
	return (_path);
}
