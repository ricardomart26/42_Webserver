#include <iostream>
#include <sys/stat.h>


bool	fileExists(const std::string &path)
{
	struct stat	buffer;
	return (stat(path.c_str(), &buffer) == 0);
}


int main(void)
{
	std::string filename = "maino.cpp";
	if (fileExists(filename))
		std::cout << "Existe\n";
	else
		std::cout << "Não existe\n";
	return (0);
}
