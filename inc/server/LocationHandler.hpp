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
		void		get_location_root();
		std::string	search_for_path_with_index(const std::vector<std::string> &index_vec);
		void		search_for_files(const std::vector<std::string> &sb_index_vec, bool auto_index);
		std::vector<Location*>	get_location_vec() const;
		bool		emptyLocation() const;

		Location			*get_location() const;
		const std::string	&get_path() const;


	private:

		ServerBlock				*_sb;
		Location				*_location;
		std::string				_path;
		std::string				_sb_root;
		std::vector<Location *>	_location_vec;
};



#endif

