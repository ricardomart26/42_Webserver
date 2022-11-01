#ifndef GET_HPP
#define GET_HPP

#include "Response.hpp"

class Get : public Response 
{
	public:

		Get(Request *_request, int fd);
		Get(const Get &cpy);
		Get	&operator=(const Get &rhs);
		~Get();

		void	send_to_client(const Request &request);
	
};

#endif
