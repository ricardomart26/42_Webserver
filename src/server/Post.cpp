#include "Post.hpp"

Post::Post(Request *request, int clientFd,  ServerBlock *_sb, size_t err)
	:	Response(request, clientFd, err, _sb) {}

Post::~Post() {}

void	Post::sendToClient(const Request &request)
{
	if (_queue.is_empty())
	{
		if (_status_code == 200)
			_reason_phrase = "OK";
		if (_status_code == 404 || _status_code == 405)
			_reason_phrase = "KO";

		_statusLine = request.getHttpVersion() + " " +
		ft_itoa(_status_code) + " " + 
		_reason_phrase + "\r\n";

		_queue.add_data(_statusLine);
		if (!_rh.is_empty())
			_queue.add_data(_rh.get_header() + "\r\n");
		_queue.add_data(_file.getContent() + "\r\n");
	}

	string response = _queue.get_data();
	send(_clientSocket, response.c_str(), response.size(), 0);
	#if DEBUG == 1
		std::ofstream file("logs/Response/post.txt", std::ios::app);
		file << response << std::endl;
	#endif
}
