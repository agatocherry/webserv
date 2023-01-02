#include "../includes/webserv.hpp"

Server::Server(ServerInfo infos, int port)
{

	// Generating socket file descriptor
	// DOMAIN	= Ipv4 Internet protocol
	// TYPE		= Non-blocking socket descriptor
	// 		  (prevent usage of fcntl()
	// PROTOCOL	= Default (unspecified)
	// port = 80;
	
	if ((this->_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Error socket");
        return ;
    }
    
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->_addr.sin_port = htons(port); 
	
	// ioctl() a voir

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

	if (listen(this->_socket, MAX_FD) < 0)
	{
		perror("Error listen");
        return ;
	}
	this->_error = "";
	this->_default = &infos;
	this->_infos.push_back(infos);
	this->_size = this->_infos.size();
	this->_status = 200;
}


Server::Server(Server& copy, int new_socket)
{
	this->_socket = new_socket;
	this->_default = copy._default;
	this->_infos = copy._infos;
	this->_size = this->_infos.size();
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


int	Server::accept_fd() {
	
	int	new_socket;
	int	size = sizeof(_addr);

	new_socket = accept(_socket, (struct sockaddr *)&_addr, (socklen_t *)&(size));

	if (new_socket == -1)
		std::cerr << "Error: accept()" << std::endl;
	return new_socket;
}

void	Server::close_socket() {
	if (_socket > 0)
		close(_socket);
}

// int	Server::parseRequest() {
// 	int		ret;
// 	char	buffer[REQUEST_SIZE] = {0};

// 	ret = read(_socket, buffer, REQUEST_SIZE - 1);

// 	if (ret <= 0) {
// 		this->close_socket();
// 		free(buffer);
// 		std::cerr << "Error : Could not read from the socket.\n" << std::endl;
// 		return -1;
// 	}

// 	_request += std::string(buffer);
// 	if (_request.find("Transfer-Encoding: chunked") != std::string::npos) {
// 		if (this->chunkedRequest())
// 			return 1;
// 		else
// 			parseChunked();
// 	}

// 	ServerInfo	clientInfo = requestInfos();
// 	ClientRequest	client(clientInfo, _request);

// 	_file_request = client.getFile();
// 	_status = client.getStatus();

// 	return 0;
// }

int	Server::chunkedRequest() {
	if (_request.find("0\r\n\r\n") != std::string::npos)
		return 0;
	return 1;
}

// void	Server::parseChunked() {
// 	std::string		header;
// 	std::string		received;
// 	std::string		body = "";
// 	int				size = 0;
// 	int				i;

// 	header = _request.substr(0, _request.find("\r\n\r\n") + 4);
// 	received = _request.substr(_request.find("\r\n\r\n") + 4);

// 	while (received.size()) {
		// i = _received.find("\r\n") + 2;
// 		size = stoi(_received.substr(0, i - 2), 0, 16);
// 		body += received.substr(i, i + size);
// 		received = received.substr(i + size + 2);
// 	}

// 	_request = header + body + "\r\n";
// }

// int	Server::sendResponse(std::map<int, std::string> errors) {
	
// 	HttpResponse	response(_file_request, _status, requestInfos().getAutoIndex(), errors);
// 	std::string		message = response.getResponse();
// 	int	ret;

// 	ret = write(_socket, message, message.size());
// 	if (ret < 0) {
// 		// Verifier si 0 succes ou erreur
// 		// Gestion d'erreur
// 	}

// 	this->close_socket();
// 	_request.erase();
// 	_file_request.erase();

// 	return (0);
// }

ServerInfo	Server::requestInfos() {
	if (_infos.size() == 1)
		return *(_infos.begin());

	// determiner par server_name


	return *_default;
}

std::string	Server::getError(){
	return _error;
}

std::ostream	&operator<<(std::ostream &x, Server serv)
{
	x << "**** Server ****" << std::endl;
	// x << serv.getSocket();
	std::cout << " | ";
	serv.setSocket(15);
	// x << serv.getSocket();
	std::cout << " | ";
	x << serv._default;
	return (x);
}
