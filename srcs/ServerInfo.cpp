

#include "Server.hpp"
#include "ServerInfo.hpp"

ServerInfo::ServerInfo(void)
{
	// Default constructor
	this->ip = "0.0.0.80";			//Variable
	this->server_name = "localhost";	//Variable
	this->client_body_buffer_size = 0; 	//Variable
	this->autoindex = 0; 			//Variable
}

ServerInfo::setIp(std::string ip)
{
	// Simple setter : IP
	this->ip = ip;
}


ServerInfo::setServerName(std::string name)
{
	// Simple setter : server_name
	this->server_name = name;
}
