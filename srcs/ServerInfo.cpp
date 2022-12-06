#include "../includes/ServerInfo.hpp"

ServerInfo::ServerInfo()
{
	this->_allow[0] = 0;
	this->_allow[1] = 0;
	this->_allow[2] = 0;
	this->_allow[3] = 0;
	this->_loc = NULL;
}

void	ServerInfo::setIp(std::string line)
{
	if (line.find("localhost") != std::string::npos)
		this->_ip = "127.0.0.1";
	else
		if (line.find(" ") != std::string::npos)
			this->_ip = &line[line.find(" ")];
}

void	ServerInfo::setName(std::string line)
{
	if (line.find(" ") != std::string::npos)
		this->_name = &line[line.find(" ")];
}

void	ServerInfo::setClientSize(std::string line)
{
	if (line.find(" ") != std::string::npos)
		this->_clientSize = atoi(&line[line.find(" ")]);
}

void	ServerInfo::setAutoIndex(int autoIndex)
{
	this->_autoIndex = autoIndex;
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

void	ServerInfo::setLoc(std::string uri, std::string root, std::string index, std::string allow)
{
	Location *tmp = new Location;
	if (uri.find(" ") != std::string::npos)
	{
		tmp->uri = &uri[uri.find(" ") + 1];
		tmp->uri[tmp->uri.find(" ")] = '\0';
		tmp->uri[tmp->uri.find("{")] = '\0';
	}
	if (root.find(" ") != std::string::npos)
		tmp->root = &root[root.find(" ") + 1];
	if (index.find(" ") != std::string::npos)
		tmp->index = &index[index.find(" ") + 1];
	tmp->allow[0] = 0;
	tmp->allow[1] = 0;
	tmp->allow[2] = 0;
	tmp->allow[3] = 0;
	if (allow.find("GET") != std::string::npos)
			tmp->allow[0] = 1;
	if (allow.find("POST") != std::string::npos)
			tmp->allow[1] = 1;
	if (allow.find("DELETE") != std::string::npos)
			tmp->allow[2] = 1;
}

std::string ServerInfo::getIp()
{
	return (this->_ip);
}

std::string ServerInfo::getName()
{
	return(this->_name);
}

long int	ServerInfo::getClientSize()
{
	return (this->_clientSize);
}

int	ServerInfo::getAutoIndex()
{
	return(this->_autoIndex);
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

int	ServerInfo::sizeLoc()
{
	int	i = 0;
	Location	*tmp = this->_loc;
	while(tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

ServerInfo::~ServerInfo()
{

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
	si.setLoc("	location *.bla {", "		root YoupiBanane/", "		index youpi.bad_extension", "		allow_methods POST");
	si.setLoc("	location *.bla {", "		root YoupiBanane/", "		index youpi.bad_extension", "		allow_methods POST");
	std::cout << "Size loc : " << si.sizeLoc() << std::endl;
	//size loc
	//getloc
	//getlocallow
	return (0);
}
