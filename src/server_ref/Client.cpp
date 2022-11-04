#include "Client.hpp"

Client::Client(int fd, ServerBlock *sb)
	: _clientSocket(fd), _keep_alive(false), _request(NULL), _response(NULL), _finished(false), _sb(sb) {}

Client::~Client() {}

Response	*Client::initResponse(int clientFd)
{
	if (_response != NULL)
		return (_response);
	std::string method = _request->getMethod();
	if (!method.compare("POST"))
		return (new Post(_request, clientFd, _sb));
	else if (!method.compare("GET")) 
		return (new Get(_request, clientFd, _sb));
	else if (!method.compare("DELETE")) 
		return (new Delete(_request, clientFd, _sb));
	else
		throw 405;
}

bool	Client::createRequest()
{
	try
	{
		// Se for um novo pedido
		if (_request != NULL)
			delete	_request;
		_request = new Request(_clientSocket, _sb); 
	}
	catch (const std::exception &e) 
	{
		std::cout << e.what() << std::endl;
		return (false);
	} 
	return (true);
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

bool	Client::createResponse()
{
	try 
	{
		_response = initResponse(_clientSocket);
		_response->sendToClient(*_request);
	}
	catch (size_t err) 
	{
		_response = new Get(_request, _clientSocket, _sb, err);
	}
	return (isFinished());
}

int	Client::getClientSocket() const
{
	return (_clientSocket);
}

Request	*Client::getRequest() const
{
	return (_request);
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

// 295 ou 261

