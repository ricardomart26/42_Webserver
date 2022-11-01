#include "Get.hpp"

Get::Get(Request *request, int clientFd) 
	:	Response(request, clientFd) {}

Get::~Get() {}

void	Get::send_to_client(const Request &request)
{
	if (_queue.is_empty())
	{
		if (_status_code == 200)
			_reason_phrase = "OK";

		_status_line = request.get_http_version() + " " + ft_itoa(_status_code) + " " + _reason_phrase + "\r\n";

		_queue.add_data(_status_line);
		_queue.add_data(_rh.get_header() + "\r\n");
		_queue.add_data(_file.get_content() + "\r\n");
	}
	string response = _queue.get_data();
	send(_client_socket, response.c_str(), response.size(), 0);
	#if DEBUG == 1
		std::ofstream file("logs/Response/get.txt", std::ios::app);
		file << response << std::endl;
	#endif
}
