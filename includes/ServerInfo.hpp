#ifndef SERVERINFO_HPP
#define SERVERINFO_HPP

#pragma once

#include "webserv.hpp"

class ServerInfo {
	
	public:
		
		ServerInfo();
		~ServerInfo();
		
		void	setServerName(std::string name);
		void	setIp(std::string line);
		void	setClientSize(std::string line);
		void	setAutoIndex(int autoIndex);
		void	setAllow(std::string line);
		void	setLoc(std::string uri, std::string root, std::string index, std::string allow);
		
		std::string	getServerName();
		std::string	getIp();
		long		getClientSize();
		int			getAutoIndex();
		int			getAllow(std::string allow);
		
		std::vector<Location>		_loc;
	
	private:
		
		std::string	_ip;
		std::string	_serverName;
		
		long		_clientSize;
		int			_allow[3]; // GET POST DELETE : 0 si interdit, 1 si autorise
		int			_autoIndex; //0 si off, 1 si on
};

std::ostream	&operator<<(std::ostream &x, std::vector<Location> _loc);
std::ostream	&operator<<(std::ostream &x, ServerInfo inf);

#endif
