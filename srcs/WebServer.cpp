#include "../includes/WebServer.hpp"

WebServer::WebServer(void) {
	return ;
}

WebServer::WebServer(WebServer& copy) {
	*this = copy;
}

WebServer::~WebServer(void) {
	return ;
}

WebServer&	WebServer::operator=(WebServer& copy) {
	if (this != &copy) {
		this->_config = copy._config;
		this->_servers = copy._servers;
		this->_sockets = copy._sockets;
		this->_max_fd = copy._max_fd;
	}
	return *this;
}

int	WebServer::parsefile(char *filename) {
	
	_servers = _config.parse(filename);
	_max_fd = _config.getMaxFd();

	// Mettre toutes les sockets des servers dans _sockets
	FD_ZERO(&_sockets);
	for (std::map<int, Server>::iterator it = _servers.begin(); it != _servers.end(); it++) {
		FD_SET(it->second.getSocket(), &_sockets);
	}

	return 0;
}

int	WebServer::launch(void) {
	// select()
}

int	WebServer::clean(void) {

}
