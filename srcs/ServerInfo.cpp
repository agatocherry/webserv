
#include "ServerInfo.hpp"
#include "../includes/ServerInfo.hpp"

ServerInfo::ServerInfo(void)
{
	// Default constructor
	// Arbitrary values set,
	//					come back later
	this->_ip = "0.0.0.80";			//Variable
	this->_server_name = "localhost";	//Variable
	this->_clientSize = 0; 			//Variable
	this->_autoIndex = 0; 			//Variable
}

		///////////////////////
		//
		//	SETTERS
		//
		///////////////////////

std::ostream	&operator<<(std::ostream &x, ServerInfo inf)
{
	x << inf.getIp();
	std::cout << " | ";
	x << inf.getServerName();
	std::cout << " | ";
	x << inf.getClientSize();
	return (x);
}

void	ServerInfo::setIp(std::string line)
{
	if (line.find("localhost") != std::string::npos)
		this->_ip = "127.0.0.1";
	else
		if (line.find(" ") != std::string::npos)
			this->_ip = &line[line.find(" ")];
}

//void	ServerInfo::setName(std::string line)
void	ServerInfo::setServerName(std::string line)
{
	if (line.find(" ") != std::string::npos)
		this->_server_name = &line[line.find(" ")];
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
	Location *newNode = new Location;
	if (uri.find(" ") != std::string::npos)
	{
		newNode->uri = &uri[uri.find(" ") + 1];
		newNode->uri[newNode->uri.find(" ")] = '\0';
		newNode->uri[newNode->uri.find("{")] = '\0';
	}
	if (root.find(" ") != std::string::npos)
		newNode->root = &root[root.find(" ") + 1];
	if (index.find(" ") != std::string::npos)
		newNode->index = &index[index.find(" ") + 1];
	newNode->allow[0] = 0;
	newNode->allow[1] = 0;
	newNode->allow[2] = 0;
	if (allow.find("GET") != std::string::npos)
			newNode->allow[0] = 1;
	if (allow.find("POST") != std::string::npos)
			newNode->allow[1] = 1;
	if (allow.find("DELETE") != std::string::npos)
			newNode->allow[2] = 1;
	newNode->next = NULL;
	if(this->_loc == NULL)
		this->_loc = newNode;
	else
	{
		Location *tmp = this->_loc;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newNode;
	}
}

		/////////////////////////
		//	GETTER		/
		////////////////////////	


std::string ServerInfo::getIp()
{
	return (this->_ip);
}

std::string ServerInfo::getServerName()
{
	return(this->_server_name);
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
	while(this->_loc)
	{
		Location *tmp = this->_loc;
		this->_loc = this->_loc->next;
		delete(tmp);
	}
}


