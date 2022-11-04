#include "MyQueue.hpp"

MyQueue::MyQueue(size_t maxSize) : _head(NULL), _tail(NULL), _max_size(maxSize), _empty(true) {}

MyQueue::~MyQueue() {}

bool	MyQueue::is_empty() { return (_empty); }

std::string	MyQueue::get_data()
{
	if (_empty)
	{
		// std::cout << "Is empty\n";
		_head = NULL;
		return "";
	}

	if (_head->_next == NULL)
	{
		_empty = true;
	}
	

	std::string elem(std::string(_head->_data));

	t_linkedQueue *temp = _head;
	_head = _head->_next;
	delete temp;

	return (elem);
}

void	MyQueue::add_data(std::string newData)
{
	if (newData.size() == 0)
		return ;
	if (_head == NULL)
	{
		_head = new t_linkedQueue;
		_head->_data = newData.substr(0, _max_size);
		// std::cout << "\nHead Data added: " << _head->_data << "\n";
		_tail = _head;
		_empty = false;
		if (_head->_data.size() == _max_size)
		{
			if (newData.size() > _max_size)
				add_data(newData.substr(_max_size));
		}
		return ;
	}

	if (!_tail->_isFull) // Se o ultimo node ainda não estiver cheio
	{
		size_t remaining = _max_size - _tail->_data.size();
		_tail->_data += newData.substr(0, remaining);
		// std::cout << "\nTail Data added: " << _tail->_data << "\n";
		if (_tail->_data.size() == _max_size)
			_tail->_isFull = true;

		_tail->_next = NULL;
		if (newData.size() > remaining)
			add_data(newData.substr(remaining));
	}
	else 
	{
		_tail->_next = new t_linkedQueue;
		_tail = _tail->_next;
		_tail->_isFull = false;
		add_data(newData);
	}
}
