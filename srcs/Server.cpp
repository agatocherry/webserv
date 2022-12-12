#include "Server.hpp"
#include "WebServer.hpp"
#include "ServerInfo.hpp"

#include "../includes/WebServer.hpp"
#include "../includes/Server.hpp"
#include "../includes/ServerInfo.hpp"

Server::Server(ServerInfo infos, int port)
{
//	struct sockaddr_in 		address;
    
	// Generating socket file descriptor
	// DOMAIN	= Ipv4 Internet protocol
	// TYPE		= Non-blocking socket descriptor
	// 		  (prevent usage of fcntl()
	// PROTOCOL	= Default (unspecified)
//	port = 80;
	if ((this->_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Error socket");
        	return ;
    	}
        this->_addr.sin_family = AF_INET;
	this->_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    	this->_addr.sin_port = htons(port); //PORT = 80, always
   // 	address.sin_addr.s_addr = SO_REUSEADDR;
    //	address.sin_addr.s_addr = SOCK_STREAM;
   // 	address.sin_addr.s_addr = SOCK_NONBLOCK;
	memset(this->_addr.sin_zero, '\0', sizeof(this->_addr.sin_zero));
	////////////////////////////////////
        
	// Binding the socket to the
	// socket-address struct parameters
	// +
	// Start listening on the socket
	if (bind(this->_socket, (struct sockaddr *)&(this->_addr), sizeof(this->_addr)) < 0)
	{
		perror("Error bind");
        	return ;
	}
	if (listen(this->_socket, 10) < 0)
	{
		//Max nb of queuing requests = 10,
		//too low to survive siege (come back later)
		perror("Error listen");
        	return ;
	}
	////////////////////////////////////
	// Setting the Default ServerInfo
	// data here, (come back later : DONE)
	this->_default = &infos;
	////////////////////////////////////
	this->_infos.push_back(infos);
	this->_size = this->_infos.size();
}


Server::Server(Server& copy)
{
	// Dup the socket fd of parameter into
	// own socket fd.
	// The rest is similar to normal construction.
	this->_socket = dup(copy.getSocket());
	this->_default = copy._default;
	this->_infos = copy._infos;
	this->_size = this->_infos.size();

/*	struct sockaddr_in 			address;
	
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
	this->_infos = copy.getAllInfos;	//Using getters now
	this->_default = copy.getDefaultInfos;	//IMPOSSIBLE
	this->size = this->_infos.size();	//IMPOSSIBLE
*/
}


Server::~Server(void)
{
	// Default destructor, closes the
	// socket descriptor generated at
	// construction.
	close(this->_socket);
}


int	Server::getSocket(void)
{
	// Simple getter : socket descriptor
	return (this->_socket);
}

void	Server::setSocket(int socket_descriptor)
{
	// Simple setter : socket descriptor
	this->_socket = socket_descriptor;
}

void	Server::addNewInfo(ServerInfo& new_infos)
{
	// Adds a new ServerInfo into the current
	// Server's vector (of infos),
	// modifying vector size accordingly.
	this->_infos.push_back(new_infos);
	this->_size++;
}

/*
ServerInfo	Server::getDefaultInfos(void)
{
	// Simple getter : default infos
	return (this->_default);
}

std::vector<ServerInfo>	Server::getAllInfos(void)
{
	// Simple getter : vector of infos
	return (this->_infos);
}
*/

std::ostream	&operator<<(std::ostream &x, Server serv)
{
	x << serv.getSocket();
	std::cout << " | ";
	serv.setSocket(15);
	x << serv.getSocket();
	std::cout << " | ";
	x << serv._default;
	return (x);
}


int	Server::accept() {
	int	new_socket;

	new_socket = ::accept(_socket, (struct sockaddr *)&_addr, (socklen_t *)&(_addr));
//	new_socket = ::accept(_socket, (struct sockaddr *)&_addr, (socklen_t *)&(sizeof(_addr)));
	if (new_socket == -1)
		std::cerr << "Problem with accept()" << std::endl;
	return new_socket;
}

void	Server::close_socket() {
	if (_socket > 0)
		::close(_socket);
}

int	Server::parseRequest() {
	int	ret;
	char	buffer[30000] = {0};

	ret = read(_socket, buffer, 30000);
	printf("From: %u\n", ntohl(_addr.sin_addr.s_addr));
	printf("%s\n", buffer);
	return 0;
}

int	Server::sendResponse() {
	write(_socket, "Message Received", 16);
	return (0); //forgot return, temporary return 0
}
