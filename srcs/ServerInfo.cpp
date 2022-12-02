

#include "Server.hpp"
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

void	ServerInfo::setLocation(std::string line)
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
	return ;
}

void	ServerInfo::setAllow(std::string line)
{
	// Complicated, come back later
	
	// Must decipher the line, and add the
	// corresponding permission accordingly.
	// order : GET POST DELETE
	// 0 = forbidden
	// 1 = allowed
	
	//Find() might be handy, and split tool too
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
