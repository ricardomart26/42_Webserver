#include "LocationHandler.hpp"

LocationHandler::LocationHandler(ServerBlock *sb, std::string &path)
{
	_sb = sb;
	_locationVec = _sb->getLocation();
	_location = NULL;

	_path = &path;
}

LocationHandler::~LocationHandler() {}


/**
 * @brief Init will compare url endpoint (e.g. https://[domain name]:[port]/[url endpoint]), and compare with 
 * 
*/
void	LocationHandler::init()
{
	size_t i = 0;
	// std::cout << "Ve o path:::: " << *_path << std::endl;
	// Search in location prefix for the best match for request path
	for (; i < _locationVec.size(); i++)
	{
		// std::cout << "Options are: " << _locationVec[i]->getPrefix() << std::endl;
		if (!_locationVec[i]->getPrefix().compare(*_path) || !_locationVec[i]->getPrefix().compare("/"))
		{
			_location = _locationVec[i];
			// std::cout << "DEBUG:::LocationHandler::find this one()\n\n\tOption found: " << ((_location == NULL) ? "NULL" : _location->getPrefix()) << "\n\n";
			return ;
		}
	}

	throw 404;
	// What happens if nginx doest find the location
	// sendHttpError(404);

	// std::cout << "DEBUG::: LocationHandler::init()\n\n\tOption found: " << ((_location == NULL) ? "NULL" : _location->getPrefix()) << "\n\n";
	// std::cout << "DEBUG::: LocationHandler::init()\n\n\tPath is: " << *_path << "\n\n";
	// std::cout << "DEBUG::: i: " << i << _locationVec.size() - 1 << "\n\n";


}

void	LocationHandler::getLocationRoot()
{
	// std::cout << _location->dir<Root>("root")->getValue() << std::endl;
	if (_location->dir<Root>("root")->getValue().empty())
	{
		if (_sbRoot.empty())
		{
			// Send error because it doesn't have a folder to look for files
			error_and_exit("LocationHandler::getLocationRoot root not found");
		} 
		*_path = _sbRoot + *_path; 
	}
	else
		*_path = _location->dir<Root>("root")->getValue() + *_path;
	// std::cout << "DEBUG::: LocationHandler::getLocationRoot()\n\n\tPath is: " << *_path << "\n";
}

std::string	LocationHandler::searchForPathWithIndex(const std::vector<std::string> &indexVec)
{
	for (size_t i = 0; i < indexVec.size(); i++)
	{
		if (fileExists(*_path + indexVec[i]))
			return (*_path += indexVec[i]);
	}
	return ("");
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
	*_path = new_path;
}

bool	LocationHandler::emptyLocation() const
{
	return (!_locationVec.size());
}

std::string	&LocationHandler::getPath()
{
	return (*_path);
}
