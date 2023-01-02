#ifndef CONFIGINFO_HPP
#define CONFIGINFO_HPP

#pragma once

#include "webserv.hpp"

class Server;

class ConfigInfo {
	public:
		ConfigInfo(void);
		ConfigInfo(ConfigInfo& copy);
		~ConfigInfo(void);
		ConfigInfo&	operator=(ConfigInfo& copy);
		std::map<int, Server>	parse(char *filename);
		void	setErrorFiles();
		void	setSize(int size);
		std::string getError();
		int	getSize();
		int	getMaxFd();
		std::map<int, std::string>	getErrors();
	private:
		std::string	_error;
		std::map<int, std::string>	_errorFiles;
		std::map<int, Server>	_servers;
		int	_maxFd;
		int	_size;
};

std::ostream	&operator<<(std::ostream &x, ConfigInfo inf);

#endif
