#ifndef SERVERBLOCK_HPP
#define SERVERBLOCK_HPP

#include <vector>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <map>
#include <sstream>

// #include "Config.hpp"
#include "InfoConfig.hpp"
#include "Directives.hpp"
#include "Location.hpp"
#include "utils.hpp"

#define DEFAULT_PATH "/home/ricardo/Desktop/42/42_projects/42_WebServer/web_files"

class ServerBlock
{
	public:

		ServerBlock(const std::string &cont);
		ServerBlock(const ServerBlock &cpy);
		~ServerBlock();

		template <typename T>
		T *dir(const std::string key)
		{
			return (dynamic_cast<T*>(_m[key]));
		}
		class ValueNotFound : public std::exception
		{
			const char *what() const throw()
			{
				return ("Value in config file is not valid");
			}
		};
		void							parseFile();
		bool							getAutoIndex() const;
		const std::vector<Location *>	&getLocation() const;

	private:

		std::string							_content;
		std::map<std::string, Directives*>	_m;
		char								_separator;
		char								_end;
		std::vector<Location *>				_locations;
		bool								_autoIndex;
};

#endif
