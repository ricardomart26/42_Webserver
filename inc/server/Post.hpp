#ifndef POST_HPP
#define POST_HPP

#include "Response.hpp"

class Post : public Response 
{
	public:

		Post(Request *_request, int fd, ServerBlock *sb, size_t err = 200);
		Post(const Post &cpy);
		Post	&operator=(const Post &rhs);
		~Post();

		void	sendToClient(const Request &request);

};

#endif
