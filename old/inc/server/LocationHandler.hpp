#ifndef LOCATIONHANDLER_HPP
#define LOCATIONHANDLER_HPP

#include "Location.hpp"
#include "ServerBlock.hpp"
#include "utils.hpp"


class LocationHandler {

	public:
		
		LocationHandler(const std::string &request, ServerBlock	*sb);
		~LocationHandler();

		void		init(const std::string &path);
		void		getLocationRoot();
		std::string	searchForPathWithIndex(const std::vector<std::string> &index_vec);
		void		searchForFiles(const std::vector<std::string> &sb_index_vec, bool auto_index);
		std::vector<Location*>	getLocationVec() const;
		bool		emptyLocation() const;

		Location			*getLocation() const;
		const std::string	&getPath() const;


	private:

		ServerBlock				*_sb;
		Location				*_location;
		std::string				_path;
		std::string				_sbRoot;
		std::vector<Location *>	_locationVec;
};



#endif

