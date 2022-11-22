#ifndef CONFIGINFO_HPP
#define CONFIGINFO_HPP

#include <iostream>
#include <map>

#include "Server.hpp"
#include "ServerInfo.hpp"

class ConfigInfo {

	public:
		ConfigInfo(void);
		ConfigInfo(ConfigInfo& copy);
		~ConfigInfo(void);

		ConfigInfo&	operator=(ConfigInfo& copy);

		std::map<int, Server>	parse(char *filename);
		
		int	getMaxFd();

	private:
		std::map<int, Server>	_servers;
		int						_max_fd;
		int						_size;
};

#endif