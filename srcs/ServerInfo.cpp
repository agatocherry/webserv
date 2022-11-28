

#include "Server.hpp"
#include "ServerInfo.hpp"

ServerInfo::ServerInfo(void)
{
	// Default constructor
	this->ip = 0;
	this->server_name = "localhost";
	{
		this->_loc.uri = "http://localhost";	//??
		this->_loc.root = "/root/"; 		//??
		this->_loc.index = "/index.html";	//??
	}
	this->clientSize = 0;
	this->autoindex = 0; //1 ?
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
