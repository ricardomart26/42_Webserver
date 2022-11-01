#ifndef POST_HPP
#define POST_HPP

#include "Response.hpp"

class Post : public Response 
{
	public:

		Post(Request *_request, int fd);
		Post(const Post &cpy);
		Post	&operator=(const Post &rhs);
		~Post();

		void	send_to_client(const Request &request);

};

#endif
