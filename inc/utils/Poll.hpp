#ifndef POLL_HPP
#define POLL_HPP

#include <poll.h>
#include <cstddef>
#include <iostream>

#include "utils.hpp"


/**
 * @brief Poll class is a struct pollfd management class, struct poll fd waits for
 * a set of file descriptors to become ready to perform I/O operations. 
 * struct of pollfd: 
 * 	int fd;			File descriptor
 * 	short events;	Events to watch 
 * 	short revents;	Events returned
 * 
 * The field fd contains a file descriptor for an open file. If the field is 
 * negative, the events and revents is ignored.
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
class Poll
{
	public:

		Poll(int server_socket, size_t size);
		~Poll();

		size_t			nbrOfEvents();
		struct pollfd	*getReturnedEvents(size_t pos);
		void			waitForConnection();
		void			reset_connection(size_t pos);
		void			add_event(int client_socket);
		void			removeEvent(int client_socket);


	public:

		void			set_event(size_t pos, int fd, short event);
		
		size_t			_size;
		size_t			_nbrOfEvents;
		struct pollfd	*_events_poll;
		struct pollfd	**_events_returned;
};

#endif
