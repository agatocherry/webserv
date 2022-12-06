#include "../includes/ServerInfo.hpp"

ServerInfo::ServerInfo(void)
{
	this->_allow[0] = 0;
	this->_allow[1] = 0;
	this->_allow[2] = 0;
	this->_allow[3] = 0;
}

void	ServerInfo::setIp(std::string line)
{
	if (line.find("localhost") != std::string::npos)
		this->_ip = "127.0.0.1";
	else
		if (line.find(" ") != std::string::npos)
			this->_ip = &line[line.find(" ")];
}

std::string ServerInfo::getIp()
{
	return (this->_ip);
}

void	ServerInfo::setName(std::string line)
{
	if (line.find(" ") != std::string::npos)
		this->_name = &line[line.find(" ")];
}

std::string ServerInfo::getName()
{
	return(this->_name);
}

void	ServerInfo::setClientSize(std::string line)
{
	if (line.find(" ") != std::string::npos)
		this->_clientSize = atoi(&line[line.find(" ")]);
}

long int	ServerInfo::getClientSize()
{
	return (this->_clientSize);
}

void	ServerInfo::setAutoIndex(int autoIndex)
{
	this->_autoIndex = autoIndex;
}

int	ServerInfo::getAutoIndex()
{
	return(this->_autoIndex);
}

void	ServerInfo::setAllow(std::string line)
// GET POST DELETE : 0 si interdit, 1 si autorise
{
	if (line.find("GET") != std::string::npos)
			this->_allow[0] = 1;
	if (line.find("POST") != std::string::npos)
			this->_allow[1] = 1;
	if (line.find("DELETE") != std::string::npos)
			this->_allow[2] = 1;
}

int	ServerInfo::getAllow(std::string allow)
// GET POST DELETE : 0 si interdit, 1 si autorise, return -1 if not found
{
	if (allow == "GET")
			return (this->_allow[0]);
	if (allow == "POST")
			return (this->_allow[1]);
	if (allow == "DELETE")
			return (this->_allow[2]);
	return (-1);
}

int	main(void)
{
	ServerInfo si;
	
	si.setIp("	listen www.localhost");
	std::cout << "Ip : " << si.getIp() << std::endl;
	si.setName("	server_name YoupiBanane");
	std::cout << "Name : " << si.getName() << std::endl;
	si.setClientSize("	client_body_buffer_size 100");
	std::cout << "Client size : " << si.getClientSize() << std::endl;
	si.setAutoIndex(0);
	std::cout << "Auto index : " << si.getAutoIndex() << std::endl;
	si.setAllow("	allow_methods GET");
	std::cout << "Allow : " << si.getAllow("GET") << ", " << si.getAllow("POST") << ", " << si.getAllow("DELETE") << std::endl;
	return (0);
}
