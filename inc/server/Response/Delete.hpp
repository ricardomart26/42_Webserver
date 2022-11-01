#ifndef DELETE_HPP
#define DELETE_HPP

#include "Response.hpp"

class Delete : public Response 
{
	public:

		Delete(Request *_request, int fd);
		Delete(const Delete &cpy);
		Delete	&operator=(const Delete &rhs);
		~Delete();

		void	send_to_client(const Request &request);

};

#endif
