#include <iostream>
#include "Config.hpp"

int main(int ac, char **av)
{

	if (ac != 2)
	{
		std::cerr << "ERROR: Bad Arguments" << std::endl;
		return (1);
	}

	// Server *server = NULL;
	try {
		Config conf(av[1]);
		// server = new Server(av[1]);

		// server->setup_sockets();

		// std::cout << "\nServer Starting...\n";

		// while (1)
		// 	server->run();

		// delete server;

	} 
	catch (const std::exception &e) 
	{
		std::cout << e.what() << std::endl;
		// delete server;
	}

	return (0);
}
