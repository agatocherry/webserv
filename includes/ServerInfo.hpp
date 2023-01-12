#ifndef SERVERINFO_HPP
#define SERVERINFO_HPP

#pragma once

#include "webserv.hpp"

class ServerInfo {
	public:
		int	_allow[3]; // GET POST DELETE : 0 si interdit, 1 si autorise
		std::vector<Location>	_loc;
		ServerInfo();
		int	setServerName(std::string name);
		int	setIp(std::string line);
		int	setClientSize(std::string line);
		int	setAutoIndex(int autoIndex);
		int	setAllow(std::string line);
		int	setLoc(Location& loc);
		std::string	getServerName();
		std::string	getIp();
		long	getClientSize();
		int	getAutoIndex();
		int	getAllow(std::string allow);
		~ServerInfo();
	private:
		std::vector<std::string>	_serverName;
		std::string	_ip;
		std::string	_root;
		std::string	_index;
		long	_clientSize;
		int	_autoIndex; //0 si off, 1 si on
};

std::ostream	&operator<<(std::ostream &x, std::vector<Location> _loc);
std::ostream	&operator<<(std::ostream &x, ServerInfo inf);

#endif
