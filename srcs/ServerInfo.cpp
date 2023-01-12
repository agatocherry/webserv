#include "../includes/webserv.hpp"

ServerInfo::ServerInfo(void)
{
	// Default constructor arbitrary values set
	this->_ip = "0.0.0.0";
	// this->_serverName = "localhost";
	this->_clientSize = 1000; 
	this->_autoIndex = 0; 
	this->_allow[0] = 0;
	this->_allow[1] = 0;
	this->_allow[2] = 0;
	// this->_loc = NULL;
}

int	ServerInfo::setServerName(std::string line)
{
	std::string	serverName = line;

	if (serverName.find(" ") != std::string::npos) {
		serverName.erase(0, serverName.find(" "));
		while (serverName.find(" ")) {

		}
		//this->_serverName = &line[line.find(" ") + 1];
	}
	return 0;
}

int	ServerInfo::setIp(std::string line)
{
	if (line.find("localhost") != std::string::npos)
		this->_ip = "127.0.0.1";
	else
		if (line.find(" ") != std::string::npos)
			this->_ip = &line[line.find(" ") + 1];
}

int	ServerInfo::setClientSize(std::string line)
{
	if (line.find(" ") != std::string::npos)
		this->_clientSize = atoi(&line[line.find(" ")]);
}

// int	ServerInfo::setAutoIndex(int autoIndex)
// {
// 	this->_autoIndex = autoIndex;
// }

int	ServerInfo::setAllow(std::string line)
// GET POST DELETE : 0 si interdit, 1 si autorise
{
	if (line.find("GET") != std::string::npos)
			this->_allow[0] = 1;
	if (line.find("POST") != std::string::npos)
			this->_allow[1] = 1;
	if (line.find("DELETE") != std::string::npos)
			this->_allow[2] = 1;
}

int	ServerInfo::setLoc(Location& loc)
{
	this->_loc.push_back(loc);
}

// std::string ServerInfo::getServerName()
// {
// 	return(this->_serverName);
// }

std::string ServerInfo::getIp()
{
	return (this->_ip);
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

ServerInfo::~ServerInfo()
{
	this->_loc.clear();
}

std::ostream	&operator<<(std::ostream &x, std::vector<Location> loc)
{
	int	i = 0;
	while (i < loc.size())
	{
		Location	tmp = loc.at(i);
		x << "Location at[" << i << "] : ";
		x << tmp.uri << ", ";
		x << tmp.root << ", ";
		x << tmp.index;
		if (tmp.allow[0] != 0)
		{
			x << ", ";
			x << "GET ";
		}
		if (tmp.allow[1] != 0)
		{
			x << ", ";
			x << "POST ";
		}
		if (tmp.allow[2] != 0)
		{
			x << ", ";
			x << "DELETE ";
		}
		if (i < loc.size() - 1)
			x << std::endl;
		i++;
	}
	return (x);
}

std::ostream	&operator<<(std::ostream &x, ServerInfo inf)
{
	x << "**** ServerInfo ****" << std::endl;
	// x << inf.getServerName() << ", ";
	x << inf.getIp() << ", ";
	x << inf.getClientSize() << ", ";
	x << inf.getAutoIndex();
	if (inf._allow[0] != 0)
	{
		x << ", ";
		x << "GET ";
	}
	if (inf._allow[1] != 0)
	{
		x << ", ";
		x << "POST ";
	}
	if (inf._allow[2] != 0)
	{
		x << ", ";
		x << "DELETE ";
	}
	x << std::endl;
	x << inf._loc;
	return (x);
}
