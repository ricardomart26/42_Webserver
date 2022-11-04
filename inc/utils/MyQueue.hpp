#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP

#include <iostream>

/**
 * @def Saves strings in a queue with limited size 
 * that everytime we used a string, that string is deleted
 * 
 * @example If the size is 3, and we pass a string 10 char's,
 * it will save the string 3 by 3
 * 
 * string is: abcdefghij
 * size: 3
 *   -----		  -----        -----        ----- 
 *  | abc |  ->  | def |  ->  | ghi |  ->  | j   |
 * 	 -----        -----        -----        -----
 */
class MyQueue
{
	public:

		MyQueue(size_t max_size);

		MyQueue(const MyQueue &cp);
		MyQueue &operator=(const MyQueue &rhs);
		~MyQueue();

		/**
		 * @def Add string to queue, if string is bigger than 'max_size', 
		 * it will create a new node, and add the rest to the next node
		 */
		void		add_data(std::string data);

		/**
		 * @def Returns the first string in the linked list and goes to the 
		 * next node and delete the previous node
		 */
		std::string	get_data();

		/**
		 * @definition: If nothing saved in queue returns true
		 */
		bool		is_empty();

	private:

		typedef struct s_linkedQueue
		{
			std::string				_data;
			bool					_isFull;
			struct s_linkedQueue	*_next;
		} t_linkedQueue;
		
		t_linkedQueue	*_head;
		t_linkedQueue	*_tail;

		size_t			_max_size;
		size_t			_size;
		bool			_empty;

};

#endif
