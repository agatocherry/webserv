#ifndef SERVER_HPP
#define SERVER_HPP

#pragma once

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "ServerInfo.hpp"
#include "File.hpp"

class ServerInfo;

class Server {

	public:
		Server(ServerInfo infos, int port = 80);
		Server(Server& copy);
		~Server(void);

		Server&	operator=(Server& copy);

		int	accept();
		int			getSocket();
//		ServerInfo		getDefaultInfos(void);
//		std::vector<ServerInfo>	getAllInfos(void);

		void	addNewInfo(ServerInfo& new_infos);
		void	setSocket(int socket_descriptor);

		ServerInfo		*_default;	//what if ?
	//	ServerInfo		_default;	//no more a pointer
		std::vector<ServerInfo>	_infos;

		void	close();
		int		parseRequest();
		int		sendResponse();

	private:
		ServerInfo			*_default;
		struct sockaddr_in	_addr;
		std::vector<ServerInfo>	_infos;
		int			_socket;
		int			_size;
};

std::ostream	&operator<<(std::ostream &x, Server serv);

#endif
