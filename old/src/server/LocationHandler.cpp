#include "LocationHandler.hpp"

LocationHandler::LocationHandler(const std::string &request, ServerBlock *sb)
{
	(void)request;
	_sb = sb;
	_locationVec = _sb->getLocation();
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
	for (; i < _locationVec.size(); i++)
	{
		// std::cout << "Options are: " << _locationVec[i]->getPrefix() << std::endl;
		std::cout << "Options are: " << path << std::endl;

		if (_locationVec[i]->getPrefix().compare(path) == 0)
		{
			_location = _locationVec[i];
			break ;
		}
	}

	if (i == _locationVec.size() - 1)
	{
		if (_locationVec[i]->getPrefix().compare("/") == 0)
			_location = _locationVec[i];
		
	}

	if (_location == NULL)
	{
		// What happens if nginx doest find the location
		// sendHttpError(404);
		error_and_exit("Location error in LocationHandler::init(int, ServerBlock)");
	}

}

void	LocationHandler::getLocationRoot()
{
	std::string ret;
	std::string location_root = _location->dir<Root>("root")->getValue();
	// std::cout << "Root found is: " << _location->getRoot() << std::endl;
	// std::cout << "Path is: " << _path << std::endl;
	// std::cout << "location root is: " << location_root << std::endl;

	if (location_root.empty())
	{
		if (_sbRoot.empty())
		{
			// Send error because it doesn't have a folder to look for files
			error_and_exit("LocationHandler::getLocationRoot root not found");
		} 
		_path = _sbRoot + _path; 
	}
	else
		_path = location_root + _path;

}

std::string	LocationHandler::searchForPathWithIndex(const std::vector<std::string> &indexVec)
{
	// std::cout << std::endl;
	for (size_t i = 0; i < indexVec.size(); i++)
	{
		// std::cout << "search for path with index: " << _path + indexVec[i] << std::endl;
		if (fileExists(_path + indexVec[i]))
			return (_path += indexVec[i]);
	}
	return "";
}

void	LocationHandler::searchForFiles(const std::vector<std::string> &sb_indexVec, bool auto_index)
{

	std::string new_path;

	new_path = searchForPathWithIndex(_location->getIndex());
	if (new_path.empty())
	{
		new_path = searchForPathWithIndex(sb_indexVec);
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


// std::vector<Location*>	LocationHandler::get_locationVec() const
// {
// 	return (_locationVec);
// }

bool	LocationHandler::emptyLocation() const
{
	return (!_locationVec.size());
}

// Location	*LocationHandler::get_location() const
// {
// 	return (_location);
// }

const std::string	&LocationHandler::getPath() const
{
	return (_path);
}
