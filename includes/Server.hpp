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
#include "ClientRequest.hpp"
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

		void	close_socket(void);//close -> close_socket
		void	parseChunked();
		int		parseRequest();
		int		sendResponse();
		int		chunkedRequest();

		ServerInfo	requestInfos();

	private:
		struct sockaddr_in	_addr;
		std::string	_file_request;
		std::string	_request;
		int			_socket;
		int			_status;
		int			_size;
};

std::ostream	&operator<<(std::ostream &x, Server serv);

#endif
