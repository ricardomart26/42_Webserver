#ifndef DELETE_HPP
#define DELETE_HPP

#include "Response.hpp"

class Delete : public Response 
{
	public:

		Delete(Request *_request, int fd, ServerBlock *sb, size_t err = 200);
		Delete(const Delete &cpy);
		Delete	&operator=(const Delete &rhs);
		~Delete();

		void	sendToClient(const Request &request);

};

#endif
