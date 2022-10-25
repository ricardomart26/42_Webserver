#ifndef INFOCONFIG_HPP
#define INFOCONFIG_HPP

#include <string>
#include <vector>

class InfoConfig
{
	public:
		InfoConfig();
		~InfoConfig();

		bool	is_directive(const std::string &cmp) const;
		bool	is_context(const std::string &cmp) const;

		static std::vector<std::string> _directives;
		static std::vector<std::string> _contexts;
	// private:


};

#endif
