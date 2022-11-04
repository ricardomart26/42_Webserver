#include "Client.hpp"

Client::Client(int fd, const std::vector<ServerBlock *> sb) 
	: _clientSocket(fd), _keep_alive(false), _response(NULL), _finished(false), _sb(sb)
{
	_request = NULL;
}

Client::~Client() {}

Response	*Client::initResponse(int clientFd)
{
	std::string method = _request->getMethod();
	if (!method.compare("POST"))
		return (new Post(_request, clientFd));
	else if (!method.compare("GET")) 
		return (new Get(_request, clientFd));
	else if (!method.compare("DELETE")) 
		return (new Delete(_request, clientFd));
	else
		throw MethodNotFound(405);
}

bool	Client::createRequest()
{
	try 
	{
		if (_request != NULL)
		{
			delete	_request;
			_request = NULL;
		}
		_request = new Request(_clientSocket, _sb); 
	}
	catch (const std::exception &e) 
	{
		std::cout << e.what() << std::endl;
		return (false);
	} 
	return (true);
}

bool	Client::createResponse()
{
	try 
	{
		if (_response == NULL)
			_response = initResponse(_clientSocket);
		_response->sendToClient(*_request);
	}
	catch (size_t err) 
	{ 
		_response = new Get(_request, _clientSocket, err);
	}
	return (isFinished());
}

int	Client::getClientSocket() const
{
	return (_clientSocket);
}

Request	&Client::getRequest() const
{
	return (*_request);
}

Request	*Client::getRequest) const
{
	return (_request);
}

bool	Client::isFinished()
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

// bool	Client::sendHttpError(unsigned short code)
// {
// 	std::string reason_phrase = "KO";

// 	if (code == 404)
// 		reason_phrase = "Not Found";

// 	FileWrapper file(Response::_WRITE_SIZE);
// 	file.open("error.html");
// 	file.read();
// 	file.closeFile();

// 	std::string body = file.getContent() + "\r\n";

// 	std::string	status_line = _request->getHttpVersion() + " " + std::string(ft_itoa(code)) + " KO\r\n";
// 	std::string	header = "Content-Type: text/html\r\nContent-Length: " + std::string(ft_itoa(body.size())) + "\r\n";
// 	header += getTime() + "\r\n\r\n";

// 	std::string	response = status_line + header + body;
// 	send(_clientSocket, response.c_str(), response.size(), 0);

// 	return (true);
// }
