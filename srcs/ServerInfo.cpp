

#include "Server.hpp"
#include "ServerInfo.hpp"

ServerInfo::ServerInfo(void)
{
	// Default constructor
	this->ip = 0;
	this->server_name = "localhost";
	this->_loc = proute; ////////
	this->clientSize = NULL;
	this->autoindex = 0; //1 ?
}
