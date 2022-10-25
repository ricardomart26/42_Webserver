#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "ServerBlock.hpp"
#include "FileWrapper.hpp"

#include <string>
#include <cstdlib>

class MyFile;
class ServerBlock;

class Config
{
	public:
		Config(const char *filename);
		~Config();

		void	fileValidator();
		void	removeEmptyNewLines();
		void	parse_server();
		bool	invalidEndOfLine();
		bool	invalidBrackets();
		bool	isContext(int index);
		bool	isDirectives(int index);

		ServerBlock	*getServerBlock(size_t i);
		std::vector<ServerBlock*>	&getServerBlockVec();

		class ConfigCheckEndLine : public std::exception
		{
			const char *what() const throw() { return ("Check end line failed"); }
		};

		class ConfigCheckOpenings : public std::exception
		{
			const char *what() const throw() { return ("Check openings failed"); }
		};

	private:

		std::string					_content;
		MyFile						_file;
		std::vector<ServerBlock *>	_server_block;
};

#endif
