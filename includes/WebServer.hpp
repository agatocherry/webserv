#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <iostream>
#include <map>

#include "Server.hpp"
#include "ConfigInfo.hpp"

class WebServer {

	public:

		WebServer(void);
		WebServer(WebServer& copy);
		~WebServer(void);

		WebServer&	operator=(WebServer& copy);

		int	parsefile(char *filename);
		int	launch();
		int	clean();

	private:
		ConfigInfo				_config;
		std::map<int, Server>	_servers;
		fd_set					_sockets;
		int						_max_fd;
};

#endif