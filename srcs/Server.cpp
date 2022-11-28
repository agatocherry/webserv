

#include "Server.hpp"
#include "ServerInfo.hpp"


Server::Server(ServerInfo infos, int port = 80)
{
	struct sockaddr_in 			address;
    
	// Generating socket file descriptor
	// DOMAIN	= Ipv4 Internet protocol
	// TYPE		= Non-blocking socket descriptor
	// 		  (prevent usage of fcntl()
	// PROTOCOL	= Default (unspecified)
	if ((this->socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cout << "Error in socket generation\n";
        	return ;
    	}
        address.sin_family = AF_INET;
    	address.sin_addr.s_addr = SOCK_NONBLOCK;
    	address.sin_port = htons(port); //PORT = 80, always
	memset(address.sin_zero, '\0', sizeof address.sin_zero);
	////////////////////////////////////
        
	// Binding the socket to the
	// socket-address struct parameters
	// +
	// Start listening on the socket
	if (bind(this->socket, (struct sockaddr *)&address, sizeof(address))<0)
	{
		std::cout << "Error in binding\n";
        	return ;
	}
	if (listen(this->socket, 10) < 0) //Max nb of queuing requests = 10 for now
	{
		std::cout << "Error in listening\n";
        	return ;
	}
	////////////////////////////////////
	// Setting the Default ServerInfo
	// data here, (come back later)
/*	this->default->ip = 
	this->default->server_name = 
	this->default->_loc = 
	this->default->allow = 
	this->default->clientSize = 
	this->default->autoindex = 
*/	////////////////////////////////////
	this->_infos.push_back(infos);
	this->size = this->_infos.size();
}


Server::Server(Server& copy)
{
	struct sockaddr_in 			address;
    
	// Dup the socket fd of parameter into
	// own socket fd.
	// The rest is similar to normal construction.
	this->socket = dup(copy.socket);
	if (this->socket == -1)
	{
		std::cout << "Error in socket generation\n";
        	return ;
    	}
        address.sin_family = AF_INET;
    	address.sin_addr.s_addr = SOCK_NONBLOCK;
    	address.sin_port = htons(port);
	memset(address.sin_zero, '\0', sizeof address.sin_zero);
	if (bind(this->socket, (struct sockaddr *)&address, sizeof(address))<0)
	{
		std::cout << "Error in binding\n";
        	return ;
	}
	if (listen(this->socket, 10) < 0)
	{
		std::cout << "Error in listening\n";
        	return ;
	}
	this->_infos = copy._infos;		//IMPOSSIBLE (private attribute)
	this->_default = copy._default;		//IMPOSSIBLE
	this->_infos = copy._infos;		//IMPOSSIBLE
	this->size = this->_infos.size();	//IMPOSSIBLE
}


Server::~Server(void)
{
	// Default destructor, closes the
	// socket descriptor generated at
	// construction.
	close(this->socket);
}


int	Server::getSocket(void)
{
	// Simple getter : socket descriptor
	return (this->socket);
}


int	Server::addNewInfo(ServerInfo& new_infos)
{
	// Adds a new ServerInfo into the current
	// Server's vector (of infos),
	// modifying vector size accordingly.
	this->_infos.push_back(new_infos);
	this->size++;
}

ServerInfo	Server::getDefaultInfos(void)
{
	// Simple getter : default infos
	return (this->_default);
}

ServerInfo	*Server::getAllInfos(void);
{
	// Simple getter : vector of infos
	return (this->this->_infos;
}
