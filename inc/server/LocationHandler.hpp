#ifndef LOCATIONHANDLER_HPP
#define LOCATIONHANDLER_HPP

#include "Location.hpp"
#include "ServerBlock.hpp"
#include "utils.hpp"


class LocationHandler {

	public:
		
		LocationHandler(ServerBlock	*sb, std::string &path);
		~LocationHandler();

		void					findLocationBlock();
		std::string				findRoot();
		std::string				searchForPathWithIndex(const std::vector<std::string> &index_vec);
		bool					emptyLocation() const;
		void					checkIfDir();

		std::vector<Location*>	getLocationVec() const;
		Location				*getLocation() const;
		std::string				&getPath();

	private:

		ServerBlock				*_sb;
		Location				*_location;
		std::string				_path;
		std::string				_sbRoot;
		std::vector<Location *>	_locationVec;
};



#endif

