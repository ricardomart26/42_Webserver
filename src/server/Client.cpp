#include "Client.hpp"

Client::Client(int fd, const std::vector<ServerBlock *> sb) 
	: _client_socket(fd), _keep_alive(false), _response(NULL), _finished(false), _sb(sb) 
{
	_request = NULL;
}

Client::~Client() {}

Response	*Client::init_response(int clientFd)
{
	std::string method = _request->get_method();
	if (!method.compare("POST"))
		return (new Post(_request, clientFd));
	else if (!method.compare("GET")) 
		return (new Get(_request, clientFd));
	else if (!method.compare("DELETE")) 
		return (new Delete(_request, clientFd));
	return (NULL);
}

bool	Client::create_request() 
{
	try 
	{
		if (_request != NULL)
		{
			delete	_request;
			_request = NULL;
		}
		_request = new Request(_client_socket, _sb); 
	}
	catch (const std::exception &e) 
	{
		std::cout << e.what() << std::endl;
		return (false);
	} 
	catch (const char *err) 
	{
		std::cout << err << std::endl;
		return (false);
	} 
	return (true);
}

bool	Client::create_response()
{
	try 
	{
		if (_response == NULL)
		{
			_response = init_response(_client_socket);
			if (_response == NULL)
				send_http_error(405); // 405 is method not allowed

		}
		_response->send_to_client(*_request);
	}
	catch (const char *err) 
	{ 
		// std::cerr << "Client::send_response: " << err << std::endl; 
		return (send_http_error(404));
	}

	return (is_finished());
}

int	Client::get_client_socket() const 
{ 
	return (_client_socket);
}

Request	&Client::get_request() const
{ 
	return (*_request); 
}

Request	*Client::get_request_addr() const
{ 
	return (_request); 
}


bool	Client::is_finished()
{
	if (_response->finished())
	{
		if (_response != NULL)
			delete _response;
		if (_request != NULL)
			delete _request;
		_response = NULL;
		_request = NULL;
		return (true);
	}
	return (false); 
}

bool	Client::send_http_error(unsigned short code)
{
	std::string reason_phrase = "KO";

	if (code == 404)
		reason_phrase = "Not Found";

	FileWrapper file(Response::_WRITE_SIZE);
	file.open("error.html");
	file.read();
	file.closeFile();


	std::string body = file.get_content() + "\r\n";

	std::string	status_line = _request->get_http_version() + " " + std::string(ft_itoa(code)) + " KO\r\n";
	std::string	header = "Content-Type: text/html\r\nContent-Length: " + std::string(ft_itoa(body.size())) + "\r\n";
	header += getTime() + "\r\n\r\n";
	std::string	response = status_line + header + body;
	// std::cout << response << std::endl;

	send(_client_socket, response.c_str(), response.size(), 0);

	return (true);
}
