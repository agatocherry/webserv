#ifndef SERVERINFO_HPP
#define SERVERINFO_HPP

#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <unistd.h>

#include "Server.hpp"
#include "File.hpp"

class	Server;

struct Location
{
	std::string	*uri;
	std::string	*root;
	std::string	*index;
	int		allow[3]; // GET POST DELETE : 0 si interdit, 1 si autorise
};


class ServerInfo {

	public:
		ServerInfo(void);

		// Getters
		std::string	getIp(void);
		std::string	getServerName(void);
		long		getClientSize(void);
		// Setters
		void	setIp(std::string ip);
		void	setServerName(std::string name);
		void	setLocation(File arg);
		void	setClientSize(long x);
		void	setAllow(File arg);
		void	setAutoIndex(int x);


		std::vector<Location>		_loc;
		int				allow[3];
		int				nb_location;

	protected:
		std::string			ip;
		std::string			server_name;
		long				client_body_buffer_size;
		int				autoindex; //0 si off, 1 si on

};

std::ostream	&operator<<(std::ostream &x, ServerInfo inf);

#endif
