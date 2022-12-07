#include "../includes/Server.hpp"

int	Server::accept() {
	int	new_socket;

	new_socket = ::accept(_socket, (struct sockaddr *)&_addr, (socklen_t *)&(sizeof(_addr)));
	if (new_socket == -1)
		std::cerr << "Problem with accept()" << std::endl;
	return new_socket;
}

void	Server::close() {
	if (_socket > 0)
		::close(_socket);
}

int	Server::parseRequest() {
	int	ret;
	char	buffer[30000] = {0};

	ret = read(_socket, buffer, 30000);
	printf("From: %ld\n", ntohl(_addr.sin_addr.s_addr));
	printf("%s\n", buffer);
	return 0;
}

int	Server::sendResponse() {
	write(_socket, "Message Received", 16);
}