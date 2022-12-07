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

	std::string		rot[4] = {"\\ ", "| ", "/ ", "--"};
	int				i = 0;
	
	while (1) {

		fd_set			readfds;
		fd_set			writefds;
		struct timeval	timeout;
		int				pending;
		int				ret;
		
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		pending = 0;
		ret = 0;
		while (pending == 0) {

			memcpy(&readfds, &_sockets, sizeof(_sockets));
			FD_ZERO(&_writefds);

			for (std::map<int, Server>::iterator it = _writablefds.begin(); it != _writablefds.end(); it++) {
				FD_SET(it->second.getSocket(), &writefds);
			}

			std::cout << "\rWaiting" << rot[i++] << std::flush;
			if (i == 4)
				i = 0;

			pending = select(_max_fd + 1, &readfds, &writefds, NULL, &timeout);
			if (pending < 0) {
				std::cerr << "select() failed" << std::endl;
				this->reset();
				i = 0;
			}
		}

		for (std::map<int, Server>::iterator it = _writablefds.begin(); pending && it != _writablefds.end(); it++) {
			int	fd = it->second.getSocket();

			if (FD_ISSET(fd, &writefds)) {
				std::map<int, Server>::iterator tmp;
				it->second.sendResponse();

				tmp = it++;
				_writablefds.erase(tmp);
				pending--;
			}
		}


		for (std::map<int, Server>::iterator it = _acceptfds.begin(); pending && it != _acceptfds.end(); it++) {
			int	fd = it->second.getSocket();

			if (FD_ISSET(fd, &readfds)) {
				std::map<int, Server>::iterator tmp;
				it->second.parseRequest();

				_writablefds.insert(it);
				FD_CLR(fd, &_sockets);
				FD_CLR(fd, &readfds);
				tmp = it++;
				_acceptfds.erase(tmp);
				pending--;
			}
		}

		for (std::map<int, Server>::iterator it = _servers.begin(); pending && it != _servers.end(); it++) {
			int	fd = it->second.getSocket();

			if (FD_ISSET(fd, &readfds)) {
				 int	new_socket = it->second.accept();
				 
				if (new_socket > 0) {
				 	Server	new_fd(it->second);
					
					FD_SET(new_socket, &_sockets);
					if (new_socket > _max_fd)
						_max_fd = new_socket;
					
					_acceptfds.insert(std::make_pair(it->first, new_fd));
					_acceptfds[it->first].setSocket(new_socket);
					pending--;
				}
			}

		}
	}
}

void	WebServer::reset(void) {
	for (std::map<int, Server>::iterator it = _acceptfds.begin(); it != _acceptfds.end(); it++)
		it->second.close();
	_acceptfds.clear();
	_writablefds.clear();
	FD_ZERO(&_sockets);
	for (std::map<int, Server>::iterator it = _servers.begin(); it != _servers.end(); it++) {
		FD_SET(it->second.getSocket(), &_sockets);
	}
}

int	WebServer::clean(void) {
	for (std::map<int, Server>::iterator it = _servers.begin(); it != _servers.end(); it++)
		it->second.close();
}
