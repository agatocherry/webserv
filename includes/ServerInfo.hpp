#ifndef SERVERINFO_HPP
#define SERVERINFO_HPP


#pragma once

#include <unistd.h>
#include "webserver.hpp"
#include "Server.hpp"
#include "File.hpp"

class	Server;

struct Location
{
	std::string	uri; 
	std::string	root;
	std::string	index;
	int					allow[3]; // GET POST DELETE : 0 si interdit, 1 si autorise
	Location		*next;
};

class ServerInfo 
{
	public:

		ServerInfo(void);

		// Getters
		std::string	getIp(void);
		std::string	getServerName(void);
		long		getClientSize(void);
		// Setters
		void	setServerName(std::string name);
		void	setClientSize(long x);
		void	setAutoIndex(int x);


	//	std::vector<Location>		_loc;
		int				allow[3];
		int				nb_location;

		ServerInfo();
		void				setIp(std::string line);
		void				setAutoIndex(int autoIndex);
		void				setAllow(std::string line);
		void				setLoc(std::string uri, std::string root, std::string index, std::string allow);
		int					sizeLoc();
		~ServerInfo();
    
    int					_allow[3]; // GET POST DELETE : 0 si interdit, 1 si autorise
    Location		*_loc;
	private:
		std::string	_ip;
		std::string	_name;
		long				_clientSize;
		int					_autoIndex; //0 si off, 1 si on
		
};

std::ostream	&operator<<(std::ostream &x, ServerInfo inf);

#endif
