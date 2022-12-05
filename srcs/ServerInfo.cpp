
#include "ServerInfo.hpp"

ServerInfo::ServerInfo(void)
{
	// Default constructor
	// Arbitrary values set,
	//					come back later
	this->ip = "0.0.0.80";			//Variable
	this->server_name = "localhost";	//Variable
	this->client_body_buffer_size = 0; 	//Variable
	this->autoindex = 0; 			//Variable
}
		///////////////////////
		//
		//	GETTERS		
		//
		///////////////////////

std::string	ServerInfo::getIp(void)
{
	// Simple getter : IP
	return (this->ip);
}

std::string	ServerInfo::getServerName(void)
{
	// Simple getter : ServName
	return (this->server_name);
}

long		ServerInfo::getClientSize(void)
{
	// Simple getter : ClientSize
	return (this->client_body_buffer_size);
}


		///////////////////////
		//
		//	SETTERS
		//
		///////////////////////

void	ServerInfo::setIp(std::string ip)
{
	// Simple setter : IP
	this->ip = ip;
}


void	ServerInfo::setServerName(std::string name)
{
	// Simple setter : server_name
	this->server_name = name;
}

void	ServerInfo::setLocation(File arg)
{
	// Complicated, come back later
	
	// See if adding 1 Location BRACKET (Multiline ?)
	// at a time is better, or adding all at once.
	//
	// Reader function/getLine() might be handy
	// SET URI
	// SET ROOT
	// SET INDEX
	// SET ALLOW (?)
	
	int	i = 0;
//	int	location_bracket = 0;
	std::vector<std::string>::iterator it = arg.content.begin();
	while (it != arg.content.end())
	{
		if (arg.content[i].find("listen") != std::string::npos)
			this->ip = arg.content[i].rfind(" "); //OK?
		it++;
		i++;
	}
	return ;
}

void	ServerInfo::setAllow(File arg)
{
	// Complicated, come back later
	
	// Must decipher the line, and add the
	// corresponding permission accordingly.
	// order : GET POST DELETE
	// 0 = forbidden
	// 1 = allowed
	
	//Find() might be handy, and split tool too
	(void)arg;
	return ;
}

void	ServerInfo::setClientSize(long x)
{
	// Simple setter : client_body_buffer_size
	this->client_body_buffer_size = x;
}

void	ServerInfo::setAutoIndex(int x)
{
	// Simple setter : auto index
	this->autoindex = x; 
}

std::ostream	&operator<<(std::ostream &x, ServerInfo inf)
{
	x << inf.getIp() << std::endl;
	x << inf.getServerName() << std::endl;
	x << inf.getClientSize() << std::endl;
	return (x);
}
