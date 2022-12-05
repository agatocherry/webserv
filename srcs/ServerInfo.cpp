#include "../includes/ServerInfo.hpp"

ServerInfo::ServerInfo(void)
{
}

ServerInfo::ServerInfo(std::string ip)
{
	this->setIp(ip);
}

void	ServerInfo::setIp(std::string line)
{
	if (line.find("localhost") > 0)
		this->_ip = "127.0.0.1";
	else
		this->_ip = &line[line.find(" ")];
}

std::string ServerInfo::getIp()
{
	return (this->_ip);
}

void	ServerInfo::setName(std::string line)
{
	this->_name = &line[line.find(" ")];
}

std::string ServerInfo::getName()
{
	return(this->_name);
}

void	ServerInfo::setClientSize(std::string line)
{
	this->_clientSize = atoi(&line[line.find(" ")]);
}

long int	ServerInfo::getClientSize()
{
	return (this->_clientSize);
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
	return (0);
}
