#ifndef SERVERINFO_HPP
#define SERVERINFO_HPP


#pragma once

#include <unistd.h>
#include <stdlib.h>

#include "WebServer.hpp"
#include "webserv.hpp"
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
		int		getAllow(std::string allow);
		std::string	getServerName(void);
		long		getClientSize(void);
		int		getAutoIndex(void);
		// Setters
		void	setServerName(std::string name);
		void	setClientSize(long x);


	//	std::vector<Location>		_loc;
		int				allow[3];
		int				nb_location;

		void				setIp(std::string line);
		void				setAutoIndex(int autoIndex);
		void				setAllow(std::string line);
		void				setLoc(std::string uri, std::string root, std::string index, std::string allow);
		void				setClientSize(std::string line);
		int					sizeLoc();
		~ServerInfo(void);
    
	    int					_allow[3]; // GET POST DELETE :
							   // 0 si interdit, 1 si autorise
	    Location				*_loc;
	private:
	    std::string				_ip;
	    std::string				_server_name;
	    long				_clientSize;
	    int					_autoIndex; //0 si off, 1 si on
		
};

std::ostream	&operator<<(std::ostream &x, ServerInfo inf);

#endif
