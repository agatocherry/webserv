

#include "Server.cpp"

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
        	return (-1)
    	}
        address.sin_family = AF_INET;
    	address.sin_addr.s_addr = SOCK_NONBLOCK;
    	address.sin_port = htons(80);
	memset(address.sin_zero, '\0', sizeof address.sin_zero);
	////////////////////////////////////
        
	// Binding the socket to the
	// socket-address struct parameters
	// +
	// Start listening on the socket
	if (bind(this->socket, (struct sockaddr *)&address, sizeof(address))<0)
	{
		std::cout << "Error in binding\n";
        	return (-1)
	}
	if (listen(this->socket, 10) < 0) //Max nb of queuing requests = 10 for now
	{
		std::cout << "Error in listening\n";
        	return (-1)
	}
	////////////////////////////////////
	this->_infos.push_back(infos);
}
